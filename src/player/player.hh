#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include "../entity/entity.hh"
#include "../camera/camera.hh"

typedef struct
{
  float x, y;
} Position;

void init_player(SDL_Renderer *renderer);

extern Position player_position;