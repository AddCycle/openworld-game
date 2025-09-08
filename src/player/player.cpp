#include "player.hh"
#include "../entity/entity.hh"

static int scale = 1;
static int speed = 300;
static SDL_Texture *player_texture;
static SDL_FRect player_sprite = {17, 16, 16, 16};

Position player_position = {player_sprite.w, player_sprite.h};

static void cleanup()
{
  if (player_texture)
  {
    SDL_DestroyTexture(player_texture);
  }
}

static void handle_events(SDL_Event *events)
{
}

static bool check_map_bounds_horizontally(int x, int width)
{
  return x - player_sprite.w / 2 >= 0 && x + player_sprite.w / 2 <= width;
}

static bool check_map_bounds_vertically(int y, int height)
{
  return y - player_sprite.w / 2 >= 0 && y + player_sprite.h / 2 <= height;
}

static void update(float delta_time)
{
  bool isMoving = false;
  const bool *keyboard_state = SDL_GetKeyboardState(NULL);
  float new_x = player_position.x;
  float new_y = player_position.y;

  if ((keyboard_state[SDL_SCANCODE_W] || keyboard_state[SDL_SCANCODE_UP]))
  {
    new_y -= speed * delta_time;
    walkAnim.row = 3;
    isMoving = true;
  }
  if ((keyboard_state[SDL_SCANCODE_S] || keyboard_state[SDL_SCANCODE_DOWN]))
  {
    new_y += speed * delta_time;
    walkAnim.row = 0;
    isMoving = true;
  }
  if ((keyboard_state[SDL_SCANCODE_D] || keyboard_state[SDL_SCANCODE_RIGHT]))
  {
    new_x += speed * delta_time;
    walkAnim.row = 2;
    isMoving = true;
  }
  if ((keyboard_state[SDL_SCANCODE_A] || keyboard_state[SDL_SCANCODE_LEFT]))
  {
    new_x -= speed * delta_time;
    walkAnim.row = 1;
    isMoving = true;
  }

  if (check_map_bounds_horizontally(new_x, 480)) // mapX
  {
    player_position.x = new_x;
  }

  if (check_map_bounds_vertically(new_y, 300 + 16)) // mapY
  {
    player_position.y = new_y;
  }

  if (isMoving)
  {
    updateAnimation(&walkAnim);
  }
  else
  {
    walkAnim.frame = 0; // idle frame
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

  if (camera.x + camera.w >= 480)
    final_x = player_position.x - (480 - camera.w) - player_sprite.w / 2;
  if (camera.y + camera.h >= 300 + 16)
    final_y = player_position.y - (300 + 16 - camera.h) - player_sprite.h / 2;

  // --- Animation frame rect ---
  SDL_FRect dst = {final_x, final_y,
                   (float)(walkAnim.frameWidth * scale),
                   (float)(walkAnim.frameHeight * scale)};

  SDL_FRect src = {(float)(walkAnim.frame * walkAnim.frameWidth + walkAnim.offsetX),
                   (float)(walkAnim.offsetY + walkAnim.row * walkAnim.frameHeight),
                   (float)(walkAnim.frameWidth), (float)(walkAnim.frameHeight)};

  SDL_RenderTexture(renderer, player_texture, &src, &dst);
  // SDL_FRect player_pos = {final_x, final_y, player_sprite.w * scale, player_sprite.h * scale};
  // SDL_RenderTexture(renderer, player_texture, &player_sprite, &player_pos);
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

  Entity player = {"PLAYER", cleanup, handle_events, render, update};

  walkAnim = (Animation){
      .frame = 0,
      .frameCount = 6, // frames in the sheet
      .frameWidth = (int)(player_sprite.w),
      .frameHeight = (int)(player_sprite.h),
      .frameDuration = 100, // ms
      .lastFrameTime = 0,
      .offsetX = (int)(player_sprite.x),
      .offsetY = (int)(player_sprite.y),
      .row = 0};

  create_entity(player);
}

void updateAnimation(Animation *anim)
{
  Uint32 now = SDL_GetTicks();
  if (now - anim->lastFrameTime > anim->frameDuration)
  {
    anim->frame = (anim->frame + 1) % anim->frameCount;
    anim->lastFrameTime = now;
  }
}