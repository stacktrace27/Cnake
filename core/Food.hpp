#pragma once
#include <SDL2/SDL.h>

class Food
{
public:
  Food();
  ~Food();
  void placeRandom();
  SDL_Point getPosition() const;
  void render(SDL_Renderer *renderer);
  void loadTexture(SDL_Renderer *renderer);

private:
  SDL_Point position;
  SDL_Texture *texture;
  const int TILE_SIZE = 20;
};
