#include "cleanup.hh"

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
  AppState *state = (AppState *)appstate;
  CLEAN_ENTITIES(entities, entities_count);
  SDL_DestroyRenderer(state->renderer);
  SDL_DestroyWindow(state->window);
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
}