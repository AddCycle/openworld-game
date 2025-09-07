#pragma once

#include <SDL3/SDL.h>
#include "../entity/entity.hh"

typedef struct AppState
{
  SDL_Window *window;
  SDL_Renderer *renderer;
  float last_tick;
  float current_tick;
  float delta_time;
} AppState;