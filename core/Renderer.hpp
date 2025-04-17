#pragma once
#include <SDL2/SDL.h>

class Renderer
{
public:
  // Constructor
  Renderer() : renderer(nullptr) {}

  // Initialize with an SDL_Renderer object
  void init(SDL_Renderer *r) { renderer = r; }

  // Get the SDL_Renderer object
  SDL_Renderer *get() const { return renderer; }

  // Set draw color (RGBA)
  void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
  {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
  }

  // Clear the screen
  void clear() { SDL_RenderClear(renderer); }

  // Present the rendered content
  void present() { SDL_RenderPresent(renderer); }

  // Draw a rectangle (used for the snake and food)
  void drawRect(SDL_Rect *rect) { SDL_RenderFillRect(renderer, rect); }

private:
  SDL_Renderer *renderer;
};
