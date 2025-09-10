#include "font.hh"

void render_text(SDL_Renderer *renderer, const std::string &text,
                 const std::string &font_file, int font_size,
                 int x, int y)
{
  std::string full_path = get_path("assets/fonts/" + font_file + ".ttf");
  if (full_path.empty())
    return;

  TTF_Font *font = TTF_OpenFont(full_path.c_str(), font_size);

  if (!font)
  {
    SDL_Log("Failed to load font: %s", SDL_GetError());
    return;
  }

  SDL_Color white = {255, 255, 255, 255};
  SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), text.length(), white);

  if (!surface)
  {
    SDL_Log("Failed to create text surface: %s", SDL_GetError());
    TTF_CloseFont(font);
    return;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_DestroySurface(surface);

  if (!texture)
  {
    SDL_Log("Failed to create texture: %s", SDL_GetError());
    TTF_CloseFont(font);
    return;
  }

  float w, h;
  if (!SDL_GetTextureSize(texture, &w, &h))
  {
    SDL_Log("Failed to get texture size: %s", SDL_GetError());
    w = h = 0; // fallback
  }

  SDL_FRect dst = {(float)x, (float)y, w, h};

  SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
  SDL_RenderTexture(renderer, texture, NULL, &dst);

  SDL_DestroyTexture(texture);
  TTF_CloseFont(font);
}

void render_centered_text(SDL_Renderer *renderer, const std::string &text,
                          const std::string &font_file, int font_size,
                          int x, int y)
{
  std::string full_path = get_path("assets/fonts/" + font_file + ".ttf");
  if (full_path.empty())
    return;

  TTF_Font *font = TTF_OpenFont(full_path.c_str(), font_size);
  if (!font)
  {
    SDL_Log("Failed to load font: %s", SDL_GetError());
    return;
  }

  int text_width = 0, text_height = 0;
  if (!TTF_GetStringSize(font, text.c_str(), 0, &text_width, &text_height))
  {
    SDL_Log("Failed to get text size: %s", SDL_GetError());
    TTF_CloseFont(font);
    return;
  }

  // Subtract half the text width from the target x
  int centered_x = x - text_width / 2;
  int centered_y = y - text_height; // optional: center vertically too

  TTF_CloseFont(font);

  // Call your original render_text with the corrected coordinates
  render_text(renderer, text, font_file, font_size, centered_x, centered_y);
}