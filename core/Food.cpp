#include "Food.hpp"
#include "food_sprite.h" // Contains the apple_png byte array
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <ctime>

Food::Food()
{
  std::srand(std::time(nullptr));
  texture = nullptr;
}

void Food::placeRandom()
{
  position.x = std::rand() % (640 / TILE_SIZE);
  position.y = std::rand() % (480 / TILE_SIZE);
}

void Food::render(SDL_Renderer *renderer)
{
  // Create a rectangle where the texture will be rendered
  SDL_Rect rect = {position.x * TILE_SIZE, position.y * TILE_SIZE, TILE_SIZE,
                   TILE_SIZE};

  // If the texture is loaded, render it
  if (texture)
  {
    // Render the texture
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
  }
  else
  {
    // If the texture is not loaded, render a fallback red rectangle
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
  }
}

SDL_Point Food::getPosition() const { return position; }

void Food::loadTexture(SDL_Renderer *renderer)
{
  // Initialize SDL_image if not done already
  if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
  {
    SDL_Log("SDL_image could not initialize! SDL_image Error: %s",
            IMG_GetError());
    return;
  }

  // Create an SDL_RWops object from the byte array in food_sprite.h
  SDL_RWops *rw = SDL_RWFromMem(apple_png, sizeof(apple_png));

  // Load the PNG image from the byte array into an SDL_Surface
  SDL_Surface *surface = IMG_LoadPNG_RW(rw);
  if (surface == nullptr)
  {
    SDL_Log("Failed to load PNG from memory: %s", IMG_GetError());
    return;
  }

  // Create a texture from the surface
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  if (texture == nullptr)
  {
    SDL_Log("Failed to create texture: %s", SDL_GetError());
  }
}

Food::~Food()
{
  // Free texture if it was created
  if (texture)
  {
    SDL_DestroyTexture(texture);
  }

  // Quit IMG if necessary (only if you initialize IMG in this class)
  IMG_Quit();
}
