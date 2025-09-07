#include "update.hh"

void app_update(void *appstate)
{
  AppState *state = (AppState *)appstate;
  state->last_tick = state->current_tick;
  state->current_tick = SDL_GetTicks();
  state->delta_time = (state->current_tick - state->last_tick) / 1000.0f;

  UPDATE_ENTITIES(entities, entities_count, state->delta_time);
}
