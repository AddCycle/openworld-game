#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

#include "../utils/utils.hh"

void render_text(SDL_Renderer *renderer, const std::string &text,
                 const std::string &font_file, int font_size,
                 int x, int y);

void render_centered_text(SDL_Renderer *renderer, const std::string &text,
                          const std::string &font_file, int font_size,
                          int x, int y);