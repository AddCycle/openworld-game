#define CUTE_TILED_IMPLEMENTATION
#include "map.hh"
#include <string>

static cute_tiled_map_t *map;
static cute_tiled_layer_t *layer;
static cute_tiled_tileset_t *tileset;
static Texture *texture;

// FIXME : change all the dummy functions
static void noop_update(float) {}
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
  cute_tiled_layer_t *temp_layer = layer;

  while (temp_layer)
  {
    if (!temp_layer->data)
    {
      temp_layer = temp_layer->next;
      continue;
    }

    for (int i = 0; i < map->height; i++)
    {
      for (int j = 0; j < map->width; j++)
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
            (float)(j * map->tilewidth - camera.x),
            (float)(i * map->tileheight - camera.y),
            (float)(map->tilewidth),
            (float)(map->tileheight)};

        SDL_RenderTexture(renderer, texture_to_use->texture, &srect, &drect);
      }
    }

    temp_layer = temp_layer->next;
  }
}

void init_map(SDL_Renderer *renderer)
{
  const char *base_path = SDL_GetBasePath(); // folder containing the exe
  if (!base_path)
  {
    SDL_Log("SDL_GetBasePath failed: %s", SDL_GetError());
    return;
  }

  // Make sure to add a slash if SDL_GetBasePath doesn't have one
  std::string full_path = std::string(base_path) + "tiled/overworld.json";
  // SDL_free(base_path);

  // Convert backslashes to forward slashes (Windows safe)
  for (auto &c : full_path)
    if (c == '\\')
      c = '/';

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

  texture = (Texture *)SDL_malloc(sizeof(Texture));

  Texture *current_texture = texture;

  while (tileset)
  {
    std::string texture_path = std::string(base_path) + tileset->image.ptr;
    // Convert backslashes to forward slashes
    for (auto &c : texture_path)
      if (c == '\\')
        c = '/';

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

  Entity map_e = {.name = "MAP", cleanup, noop_events, render, noop_update}; // FIXME : free the memory... someones pc is going to crash

  create_entity(map_e);
}