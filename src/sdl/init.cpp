#include "init.hh"
#include "../font/font.hh"

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
  AppState *state = (AppState *)SDL_malloc(sizeof(AppState));
  *appstate = state;
  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_Log("error initializing SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  int scale = 1; // rescale it to monitor size
  state->window = SDL_CreateWindow(
      "OpenWorld Prototype",
      1280 * scale,
      720 * scale,
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
  init_map(state->renderer, "overworld");

  // initializing the player
  init_player(state->renderer);

  // initializing the camera following player
  init_camera(state->renderer);

  display_entities(entities);

  // 320x180 || 640x320
  SDL_SetRenderLogicalPresentation(state->renderer, 320, 180, SDL_LOGICAL_PRESENTATION_LETTERBOX);

  TTF_Init();

  return SDL_APP_CONTINUE;
}