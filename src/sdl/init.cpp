#include "init.hh"

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
  AppState *state = (AppState *)SDL_malloc(sizeof(AppState));
  *appstate = state;
  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_Log("error initializing SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  state->window = SDL_CreateWindow(
      "SDL3 Game",
      800,
      600,
      NULL);

  if (!state->window)
  {
    SDL_Log("Error creating window: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  state->renderer = SDL_CreateRenderer(state->window, NULL);

  if (!state->renderer)
  {
    SDL_Log("Error creating renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // initializing the map
  entities[entities_count++] = init_map(state->renderer);

  // initializing the player
  entities[entities_count++] = init_player(state->renderer);

  return SDL_APP_CONTINUE;
}
