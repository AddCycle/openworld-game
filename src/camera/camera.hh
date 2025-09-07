#pragma once

#include "../entity/entity.hh"
#include "../player/player.hh"

typedef struct
{
  float x, y, w, h;
} Camera;

extern Camera camera;
void init_camera(SDL_Renderer *renderer);