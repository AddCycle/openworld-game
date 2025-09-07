#include "camera.hh"

Camera camera = {0, 0, 320, 180};

static void update(float delta_time)
{
  camera.x = player_position.x - camera.w / 2;
  camera.y = player_position.y - camera.h / 2;

  if (camera.x < 0)
    camera.x = 0;
  if (camera.y < 0)
    camera.y = 0;

  if (camera.x + camera.w > 480)
    camera.x = 480 - camera.w;
  if (camera.y + camera.h > 300 + 16)
    camera.y = 300 + 16 - camera.h;
}

void init_camera(SDL_Renderer *renderer)
{
  Entity camera = {.update = update};

  create_entity(camera);
}