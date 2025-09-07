#include "cleanup.hh"

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
  SDL_Log("Exiting program with freeing all the memory");
  EXIT_PROGRAM_CLEAN(appstate);
}

void EXIT_PROGRAM_CLEAN(void *appstate)
{
  SDL_Log("freeing...");
  AppState *state = (AppState *)appstate;
  CLEAN_ENTITIES(entities, entities_count);
  SDL_DestroyRenderer(state->renderer);
  SDL_DestroyWindow(state->window);
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
}