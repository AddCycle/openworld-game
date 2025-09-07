#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "../entity/entity.hh"
#include "../external/cute_tiled.hh"

typedef struct Texture
{
  SDL_Texture *texture;
  int firstgid;
  int tilecount;
  int tileset_width;
  int tileset_height;
  struct Texture *next;
} Texture;

Entity init_map(SDL_Renderer *renderer);