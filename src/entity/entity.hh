#pragma once

#include <SDL3/SDL.h>

#define MAX_ENTITIES 100

typedef struct
{
  void (*cleanup)(void);
  void (*handle_events)(SDL_Event *);
  void (*render)(SDL_Renderer *);
  void (*update)(float);
} Entity;

#define RENDER_ENTITIES(entities, entities_count, renderer) \
  for (int i = 0; i < entities_count; i++)                  \
  {                                                         \
    entities[i].render(renderer);                           \
  }

#define UPDATE_ENTITIES(entities, entities_count, delta_time) \
  for (int i = 0; i < entities_count; i++)                    \
  {                                                           \
    entities[i].update(delta_time);                           \
  }

#define CLEAN_ENTITIES(entities, entities_count) \
  for (int i = 0; i < entities_count; i++)       \
  {                                              \
    entities[i].cleanup();                       \
  }

#define HANDLE_EVENTS_ENTITIES(entities, entities_count, event) \
  for (int i = 0; i < entities_count; i++)                      \
  {                                                             \
    entities[i].handle_events(event);                           \
  }

void create_entity(Entity entity);

void delete_entity(int index);

void swap_entities(int index1, int index2);

extern Entity entities[MAX_ENTITIES];
extern int entities_count;