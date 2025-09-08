#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include "../entity/entity.hh"
#include "../camera/camera.hh"

static Animation walkAnim;

typedef struct
{
  float x, y;
} Position;

void init_player(SDL_Renderer *renderer);

void updateAnimation(Animation *animation);

extern Position player_position;