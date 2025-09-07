#pragma once

#include "common.hh"

extern "C"
{
  SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event);
}