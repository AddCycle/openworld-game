#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "../entity/entity.hh"
#include "../external/cute_tiled.hh"
#include "../camera/camera.hh"

typedef struct Texture
{
  SDL_Texture *texture;
  int firstgid;
  int tilecount;
  int tileset_width;
  int tileset_height;
  struct Texture *next;
} Texture;

typedef struct
{
  int x, y, w, h;
} Map;

void init_map(SDL_Renderer *renderer, const char *map_name);
void init_map(SDL_Renderer *renderer, std::string map_name);

void change_map(const char *old_map_name, const char *new_map_name, SDL_Renderer *renderer);
void change_map(std::string old_map_name, std::string new_map_name, SDL_Renderer *renderer);

extern const char *current_map;

// enum class MAPS
// {
//   OVERWORLD,
//   DUNGEON,
//   OVERWORLD2,
//   NONE
// };