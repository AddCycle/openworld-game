#pragma once

#include "common.hh"
#include "update.hh"
#include "render.hh"

extern "C"
{
  SDL_AppResult SDL_AppIterate(void *appstate);
}