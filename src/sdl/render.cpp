#include "render.hh"
#include "../font/font.hh"

void app_render(void *appstate)
{
  AppState *state = (AppState *)appstate;
  SDL_RenderClear(state->renderer);

  // render entities on the screen
  RENDER_ENTITIES(entities, entities_count, state->renderer);

  // rendering text
  render_centered_text(state->renderer, "openworld_prototype", "PressStart2P", 12, 320 / 2, 20);

  SDL_RenderPresent(state->renderer);
}