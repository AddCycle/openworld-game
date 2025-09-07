#pragma once

#include "common.hh"
#include "../entity/entity.hh"

extern "C"
{
  void SDL_AppQuit(void *appstate, SDL_AppResult result);
}

void EXIT_PROGRAM_CLEAN(void *appstate);