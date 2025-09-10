#pragma once

#include <string.h>

#include <SDL3/SDL.h>

#define MAX_ENTITIES 100
#define MAX_NAME_LENGTH 64

typedef struct
{
  const char *name;
  void (*cleanup)(void);
  void (*handle_events)(SDL_Event *);
  void (*render)(SDL_Renderer *);
  void (*update)(float);
} Entity;

typedef struct
{
  int frame;
  int frameCount;
  int frameWidth;
  int frameHeight;
  Uint32 frameDuration; // in ms
  Uint32 lastFrameTime;
  int offsetX;
  int offsetY;
  int row;
} Animation;

#define RENDER_ENTITIES(entities, entities_count, renderer) \
  for (int i = 0; i < entities_count; i++)                  \
  {                                                         \
    if (entities[i].render)                                 \
      entities[i].render(renderer);                         \
  }

#define UPDATE_ENTITIES(entities, entities_count, delta_time) \
  for (int i = 0; i < entities_count; i++)                    \
  {                                                           \
    if (entities[i].update)                                   \
      entities[i].update(delta_time);                         \
  }

#define CLEAN_ENTITIES(entities, entities_count) \
  for (int i = 0; i < entities_count; i++)       \
  {                                              \
    if (entities[i].cleanup)                     \
      entities[i].cleanup();                     \
  }

#define HANDLE_EVENTS_ENTITIES(entities, entities_count, event) \
  for (int i = 0; i < entities_count; i++)                      \
  {                                                             \
    if (entities[i].handle_events)                              \
      entities[i].handle_events(event);                         \
  }

void create_entity(Entity entity);

void delete_entity(int index);

void swap_entities(int index1, int index2);

int find_entity(const char *name);

void display_entities(Entity entities[]);

extern Entity entities[MAX_ENTITIES];
extern int entities_count;