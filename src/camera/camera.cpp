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

/*
  A little debugging rendering function to see if the tiles are computed correctly
*/
/*static void render(SDL_Renderer *renderer)
{
  SDL_FRect cameraRect = {
      (float)-camera.x, // top-left corner in world space relative to debug view
      (float)-camera.y,
      (float)camera.w, // width of your camera
      (float)camera.h  // height of your camera
  };

  // set debug color
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  // draw outline (not filled)
  SDL_RenderRect(renderer, &cameraRect);
}*/

void init_camera(SDL_Renderer *renderer)
{
  // Entity camera = {.name = "CAMERA", .update = update, .render = render};
  Entity camera = {.name = "CAMERA", .update = update};

  create_entity(camera);
}