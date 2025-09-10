#define CUTE_TILED_IMPLEMENTATION
#include "map.hh"
#include "../utils/utils.hh"
#include <string>

static cute_tiled_map_t *map;
static cute_tiled_layer_t *layer;
static cute_tiled_layer_t *collision_layer;
static cute_tiled_tileset_t *tileset;
static Texture *texture;
static float scale = 1.f; // zooming in-out not working because needs to wire it to all objects
static const char *current_map;

// FIXME : fix the zooming logic that is broken for now
static void update(float)
{
  const bool *keyboard_state = SDL_GetKeyboardState(NULL);
  if (keyboard_state[SDL_SCANCODE_Z])
  {
    scale += 0.1f;
  }
  if (keyboard_state[SDL_SCANCODE_X])
  {
    scale -= 0.1f;
  }
}
static void noop_events(SDL_Event *) {}

// free all the memory
static void cleanup()
{
  if (texture)
  {
    Texture *current_texture = texture;

    while (current_texture)
    {
      Texture *next_texture = current_texture->next;

      if (current_texture->texture)
      {
        SDL_DestroyTexture(current_texture->texture);
      }

      SDL_free(current_texture);
      current_texture = next_texture;
    }

    texture = nullptr;
  }

  if (map)
  {
    cute_tiled_free_map(map);
    map = nullptr;
  }
}

static void render(SDL_Renderer *renderer)
{
  if (!map)
    return;
  cute_tiled_layer_t *temp_layer = layer;

  while (temp_layer)
  {
    if (!temp_layer->data)
    {
      temp_layer = temp_layer->next;
      continue;
    }

    int tileW = map->tilewidth;
    int tileH = map->tileheight;

    int startX = SDL_max(0, (int)camera.x / tileW);
    int startY = SDL_max(0, (int)camera.y / tileH);
    int endX = SDL_min(map->width, (int)(camera.x + camera.w / scale) / tileW + 1);
    int endY = SDL_min(map->height, (int)(camera.y + camera.h / scale) / tileH + 1);

    for (int i = startY; i < endY; i++)
    {
      for (int j = startX; j < endX; j++)
      {
        int tile_id = temp_layer->data[i * map->width + j];
        if (tile_id == 0)
        {
          continue;
        }

        Texture *temp_texture = texture;
        Texture *texture_to_use = NULL;

        while (temp_texture)
        {
          if (tile_id >= temp_texture->firstgid &&
              tile_id <= temp_texture->firstgid + temp_texture->tilecount - 1)
          {
            texture_to_use = temp_texture;
            break;
          }
          temp_texture = temp_texture->next;
        }

        if (!texture_to_use)
        {
          continue;
        }

        int tileset_columns = texture_to_use->tileset_width / map->tilewidth;

        SDL_FRect srect = {
            (float)((tile_id - texture_to_use->firstgid) % tileset_columns * map->tilewidth),
            (float)((tile_id - texture_to_use->firstgid) / tileset_columns * map->tileheight),
            (float)(map->tilewidth),
            (float)(map->tileheight)};

        SDL_FRect drect = {
            (float)(j * map->tilewidth - camera.x) * scale,
            (float)(i * map->tileheight - camera.y) * scale,
            (float)(map->tilewidth) * scale,
            (float)(map->tileheight) * scale};

        SDL_RenderTexture(renderer, texture_to_use->texture, &srect, &drect);
      }
    }

    temp_layer = temp_layer->next;
  }
}

void init_map(SDL_Renderer *renderer, const char *map_name)
{
  std::string full_path = get_path("tiled/" + std::string(map_name) + ".json");

  const char *map_path = full_path.c_str();
  map = cute_tiled_load_map_from_file(map_path, NULL);
  SDL_Log("map loading from : %s", map_path);

  if (!map)
  {
    SDL_Log("Failed to load map: %s", SDL_GetError());
    SDL_Log("Tried path: %s", map_path);
    return;
  }
  SDL_Log("Map loaded successfully");

  layer = map->layers;
  tileset = map->tilesets;

  // Checking collisions
  collision_layer = nullptr;
  cute_tiled_layer_t *tmp = map->layers;
  while (tmp)
  {
    // tmp->type and tmp->name are cute_tiled_string_t unions; check ptr first
    const char *t = tmp->type.ptr;
    const char *n = tmp->name.ptr;
    if (t && n)
    {
      if (strcmp(t, "tilelayer") == 0 && strcmp(n, "collision") == 0)
      {
        collision_layer = tmp;
        SDL_Log("Found collision layer: %s", n);
        break;
      }
    }
    tmp = tmp->next;
  }

  if (!collision_layer)
  {
    SDL_Log("Warning: no 'Collisions' tile layer found in map");
  }

  texture = (Texture *)SDL_malloc(sizeof(Texture));

  Texture *current_texture = texture;

  while (tileset)
  {
    std::string texture_path = get_path(tileset->image.ptr);

    current_texture->texture = IMG_LoadTexture(renderer, texture_path.c_str());

    if (!current_texture->texture)
    {
      SDL_Log("Error loading texture for tileset: %s", texture_path.c_str());
      continue;
    }

    SDL_Log("Texture loaded successfully: %s", texture_path.c_str());
    SDL_SetTextureScaleMode(current_texture->texture, SDL_SCALEMODE_NEAREST);

    current_texture->firstgid = tileset->firstgid;
    current_texture->tilecount = tileset->tilecount;
    current_texture->tileset_width = tileset->imagewidth;
    current_texture->tileset_height = tileset->imageheight;

    tileset = tileset->next;

    if (tileset)
    {
      current_texture->next = (Texture *)SDL_malloc(sizeof(Texture));
      current_texture = current_texture->next;
    }
    else
    {
      current_texture->next = NULL;
    }
  }

  Entity map_e = {map_name, cleanup, noop_events, render, update};

  create_entity(map_e);
  current_map = map_name;
}

void init_map(SDL_Renderer *renderer, std::string map_name)
{
  init_map(renderer, map_name.c_str());
}

void change_map(const char *old_map_name, const char *new_map_name, SDL_Renderer *renderer)
{
  delete_entity(find_entity(old_map_name));

  init_map(renderer, new_map_name);

  swap_entities(find_entity("PLAYER"), find_entity(new_map_name));

  current_map = new_map_name;

  display_entities(entities);
}

void change_map(std::string old_map_name, std::string new_map_name, SDL_Renderer *renderer)
{
  change_map(old_map_name.c_str(), new_map_name.c_str(), renderer);
}

bool is_tile_solid(int x, int y)
{
  if (!collision_layer || !collision_layer->data)
    return false;
  if (x < 0 || y < 0 || x >= map->width || y >= map->height)
    return true; // out of bounds = solid

  int tile_id = collision_layer->data[y * map->width + x];
  return tile_id != 0;
}