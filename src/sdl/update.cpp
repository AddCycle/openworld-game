#include "update.hh"
#include "cleanup.hh"
#include "../map/map.hh"

static bool changed = false;

void app_update(void *appstate)
{
  const bool *keyboard_state = SDL_GetKeyboardState(NULL);
  AppState *state = (AppState *)appstate;
  state->last_tick = state->current_tick;
  state->current_tick = SDL_GetTicks();
  state->delta_time = (state->current_tick - state->last_tick) / 1000.0f;

  if (keyboard_state[SDL_SCANCODE_SPACE])
  {
    if (!changed)
    {
      if (current_map == "overworld")
      {
        change_map(current_map, "dungeon", state->renderer);
      }
      else if (current_map == "dungeon")
      {
        change_map(current_map, "overworld2", state->renderer);
      }
      else if (current_map == "overworld2")
      {
        change_map(current_map, "overworld", state->renderer);
      }
      changed = true;
    }
  }
  else
  {
    changed = false;
  }

  // FPS count
  // if (state->delta_time > 0.0f)
  // {
  //   float fps = 1.0f / state->delta_time;
  //   SDL_Log("FPS: %.2f", fps);
  // }

  UPDATE_ENTITIES(entities, entities_count, state->delta_time);

  if (keyboard_state[SDL_SCANCODE_ESCAPE])
  {
    EXIT_PROGRAM_CLEAN(appstate);
    exit(0);
  }
}