#include "player.hh"
#include "../entity/entity.hh"

static int scale = 1;
static int speed = 50;
static SDL_Texture *player_texture;
static SDL_FRect player_sprite = {17, 14, 15, 18};

Position player_position = {0, 0};

static void cleanup()
{
}

static void handle_events(SDL_Event *events)
{
}

static void update(float delta_time)
{
  const bool *keyboard_state = SDL_GetKeyboardState(NULL);

  if (keyboard_state[SDL_SCANCODE_W] || keyboard_state[SDL_SCANCODE_UP])
  {
    player_position.y -= speed * delta_time;
  }
  if (keyboard_state[SDL_SCANCODE_S] || keyboard_state[SDL_SCANCODE_DOWN])
  {
    player_position.y += speed * delta_time;
  }
  if (keyboard_state[SDL_SCANCODE_D] || keyboard_state[SDL_SCANCODE_RIGHT])
  {
    player_position.x += speed * delta_time;
  }
  if (keyboard_state[SDL_SCANCODE_A] || keyboard_state[SDL_SCANCODE_LEFT])
  {
    player_position.x -= speed * delta_time;
  }
  if (keyboard_state[SDL_SCANCODE_ESCAPE])
  {
    exit(0);
  }
}

static void render(SDL_Renderer *renderer)
{
  float final_x = camera.w / 2 - player_sprite.w / 2;
  float final_y = camera.h / 2 - player_sprite.h / 2;

  if (camera.x <= 0)
    final_x = player_position.x - player_sprite.w / 2;
  if (camera.y <= 0)
    final_y = player_position.y - player_sprite.h / 2;

  if (camera.x + camera.w >= 420)
    final_x = player_position.x - (420 - camera.w) - player_sprite.w / 2;
  if (camera.y + camera.h >= 240)
    final_y = player_position.y - (240 - camera.h) - player_sprite.h / 2;

  SDL_FRect player_pos = {final_x, final_y, player_sprite.w * scale, player_sprite.h * scale};
  SDL_RenderTexture(renderer, player_texture, &player_sprite, &player_pos);
}

void init_player(SDL_Renderer *renderer)
{
  const char *base_path = SDL_GetBasePath(); // folder containing the exe
  if (!base_path)
  {
    SDL_Log("SDL_GetBasePath failed: %s", SDL_GetError());
    return;
  }

  // Make sure to add a slash if SDL_GetBasePath doesn't have one
  std::string full_path = std::string(base_path) + "assets/Char_Sprites/char_spritesheet.png";
  // SDL_free(base_path);

  // Convert backslashes to forward slashes (Windows safe)
  for (auto &c : full_path)
    if (c == '\\')
      c = '/';

  SDL_Log("player texture init");
  player_texture = IMG_LoadTexture(renderer, full_path.c_str());
  SDL_SetTextureScaleMode(player_texture, SDL_SCALEMODE_NEAREST);

  if (!player_texture)
  {
    SDL_Log("Failed to load texture: %s", SDL_GetError());
    SDL_Log("Tried path: %s", full_path.c_str());
  }

  Entity player = {cleanup, handle_events, render, update};

  create_entity(player);
}