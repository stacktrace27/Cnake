#pragma once

#include "Food.hpp"
#include "Renderer.hpp"
#include "Snake.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> // For image loading
#include <SDL2/SDL_ttf.h>   // For font rendering
#include <string>
#include <utility> // For std::pair
#include <vector>

// Comparison operator for SDL_Point
inline bool operator==(const SDL_Point &p1, const SDL_Point &p2)
{
  return p1.x == p2.x && p1.y == p2.y;
}

class Game
{
public:
  Game();
  ~Game();
  void run();

  // Getter for score
  int getScore() const { return score; }

private:
  // Private member functions
  void processEvents();
  void update();
  void render();
  void reset();
  void renderText(
      const std::string &text,
      SDL_Color color); // Function to render text (e.g., for pause screen)
  void
  renderTextLines(const std::vector<std::pair<std::string, SDL_Color>> &lines);

  // SDL-related members
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool running;

  // Game-specific members
  Snake snake;
  Food food;
  Renderer gameRenderer;

  // Window dimensions
  const int WIDTH = 640;
  const int HEIGHT = 480;

  // Score and game state
  int score = 0;
  bool paused = false;
  bool over = false; // Game over state

  // Timing-related variables
  Uint32 lastMoveTime = 0;
  const int moveDelay = 100; // Delay between snake movements in milliseconds

  // Font-related member variable
  TTF_Font *font; // Font pointer for text rendering
};
