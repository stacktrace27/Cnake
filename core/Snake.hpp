#pragma once
#include "Constants.hpp"
#include <SDL2/SDL.h>
#include <deque>

class Snake
{
public:
  Snake();
  void move();
  void grow();
  bool checkCollision() const;
  void render(SDL_Renderer *renderer);
  void setDirection(SDL_Point dir);
  SDL_Point getHead() const;
  void reset();

private:
  std::deque<SDL_Point> body;
  SDL_Point direction;
  const int TILE_SIZE = 20;
  float renderX = 0.0f, renderY = 0.0f;
};
