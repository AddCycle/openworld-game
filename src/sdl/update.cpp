#include "update.hh"
#include "cleanup.hh"

void app_update(void *appstate)
{
  const bool *keyboard_state = SDL_GetKeyboardState(NULL);
  AppState *state = (AppState *)appstate;
  state->last_tick = state->current_tick;
  state->current_tick = SDL_GetTicks();
  state->delta_time = (state->current_tick - state->last_tick) / 1000.0f;

  // FPS count
  if (state->delta_time > 0.0f)
  {
    float fps = 1.0f / state->delta_time;
    SDL_Log("FPS: %.2f", fps);
  }

  UPDATE_ENTITIES(entities, entities_count, state->delta_time);

  if (keyboard_state[SDL_SCANCODE_ESCAPE])
  {
    EXIT_PROGRAM_CLEAN(appstate);
  }
}