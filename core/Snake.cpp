#include "Snake.hpp"

Snake::Snake() { reset(); }

void Snake::setDirection(SDL_Point dir)
{
  // Prevent reversing directly
  if ((dir.x == -direction.x && dir.x != 0) ||
      (dir.y == -direction.y && dir.y != 0))
    return;
  direction = dir;
}

void Snake::move()
{
  SDL_Point newHead = {body.front().x + direction.x,
                       body.front().y + direction.y};

  // Wrap around
  int maxX = 640 / TILE_SIZE;
  int maxY = 480 / TILE_SIZE;
  newHead.x = (newHead.x + maxX) % maxX;
  newHead.y = (newHead.y + maxY) % maxY;

  body.push_front(newHead);
  body.pop_back();

  renderX = newHead.x * TILE_SIZE;
  renderY = newHead.y * TILE_SIZE;
}

void Snake::grow()
{
  SDL_Point newHead = {body.front().x + direction.x,
                       body.front().y + direction.y};
  body.push_front(newHead);
}

SDL_Point Snake::getHead() const { return body.front(); }

bool Snake::checkCollision() const
{
  const SDL_Point &head = body.front();
  for (size_t i = 1; i < body.size(); ++i)
    if (body[i].x == head.x && body[i].y == head.y)
      return true;
  return false;
}

void Snake::render(SDL_Renderer *renderer)
{
  // HEAD
  SDL_Rect headRect = {static_cast<int>(renderX), static_cast<int>(renderY),
                       TILE_SIZE, TILE_SIZE};
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  SDL_RenderFillRect(renderer, &headRect);

  // BODY
  for (size_t i = 1; i < body.size(); ++i)
  {
    SDL_Rect rect = {body[i].x * TILE_SIZE, body[i].y * TILE_SIZE, TILE_SIZE,
                     TILE_SIZE};
    SDL_SetRenderDrawColor(renderer, 0, 180, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
  }
}

void Snake::reset()
{
  // Set the snake's body to start at the center of the screen
  body.clear();
  body.push_back(
      {WIDTH / 2, HEIGHT / 2}); // Start position at the center of the screen

  // Set the initial direction (e.g., moving right)
  direction = {1, 0}; // Snake starts moving to the right

  // Reset any other state, such as score, length, etc.
}
