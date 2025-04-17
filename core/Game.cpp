#include "Game.hpp"
#include "font_data.h" // Contains the font data byte array
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

Game::Game()
    : running(true), window(nullptr), renderer(nullptr), gameRenderer(),
      snake(), food(), paused(false), score(0), font(nullptr), lastMoveTime(0),
      moveDelay(100)
{
  // Default move delay in milliseconds
  // Initialize SDL and subsystems
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
    running = false;
    return;
  }
  if (IMG_Init(IMG_INIT_PNG) == 0)
  {
    SDL_Log("IMG_Init could not initialize! IMG_Error: %s", IMG_GetError());
    running = false;
    return;
  }
  if (TTF_Init() == -1)
  {
    SDL_Log("TTF_Init could not initialize! TTF_Error: %s", TTF_GetError());
    running = false;
    return;
  }

  // Create window
  window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  if (!window)
  {
    SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
    running = false;
    return;
  }

  // Create renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer)
  {
    SDL_Log("Renderer could not be created! SDL_Error: %s", SDL_GetError());
    running = false;
    return;
  }

  // Initialize game renderer
  gameRenderer.init(renderer);

  // Load food texture
  food.loadTexture(renderer);
  food.placeRandom();

  SDL_RWops *rw =
      SDL_RWFromMem(WinkyRough_Medium_ttf, WinkyRough_Medium_ttf_len);
  font = TTF_OpenFontRW(rw, 1, 24);
  // if (!font) {
  //     std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
  // }

  // Load font
  // font = TTF_OpenFont("path_to_your_font.ttf", 24);  // Custom font
  if (!font)
  {
    // Fallback to default font if custom font fails
    font = TTF_OpenFont(NULL, 24);
    if (!font)
    {
      SDL_Log("Failed to load default font: %s", TTF_GetError());
      running = false;
      return;
    }
  }
}

Game::~Game()
{
  if (font)
  {
    TTF_CloseFont(font);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}

void Game::run()
{
  while (running)
  {
    processEvents();
    update();
    render();
    SDL_Delay(1000 / 60); // 60 FPS
  }
}

void Game::processEvents()
{
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      running = false;
    }
    else if (e.type == SDL_KEYDOWN)
    {
      switch (e.key.keysym.sym)
      {
      case SDLK_UP:
        snake.setDirection({0, -1});
        break;
      case SDLK_DOWN:
        snake.setDirection({0, 1});
        break;
      case SDLK_LEFT:
        snake.setDirection({-1, 0});
        break;
      case SDLK_RIGHT:
        snake.setDirection({1, 0});
        break;
      case SDLK_p:
        paused = !paused;
        break;
      case SDLK_r:
        reset();
        break;
      }
    }
  }
}

void Game::reset()
{
  snake.reset();
  food.placeRandom();
  score = 0;
  paused = false;
  over = false; // Reset game over state
}

void Game::update()
{
  if (!paused && !over)
  { // Only update if the game is not paused or over
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastMoveTime >= moveDelay)
    {
      snake.move();
      lastMoveTime = currentTime;

      if (snake.getHead() == food.getPosition())
      {
        snake.grow();
        food.placeRandom();
        score += 10;
      }

      if (snake.checkCollision())
      {
        renderText("GAME OVER", {255, 0, 0});
        // paused = true;  // Pause the game
        over = true; // Game over
                     // running = false;  // Game over
      }
    }
  }
}

void Game::render()
{
  // Get renderer from gameRenderer
  SDL_Renderer *renderer = gameRenderer.get();

  // Clear the screen with dark gray color
  SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
  SDL_RenderClear(renderer);

  // Render food and snake
  food.render(renderer);
  snake.render(renderer);

  // If the game is paused, render the "PAUSED" text
  if (paused)
  {
    renderText("PAUSED", {255, 255, 255});
  }

  if (over)
  {
    std::vector<std::pair<std::string, SDL_Color>> messages = {
        {"Game Over", {255, 0, 0, 255}},
        {"Press R to Restart", {0, 255, 0, 255}}};
    renderTextLines(messages);
    // renderText("Press R to Restart", {255, 255, 255});
  }

  // Present the rendered frame
  SDL_RenderPresent(renderer);
}

void Game::renderText(const std::string &text, SDL_Color color)
{
  // Render the text surface using the font
  SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
  if (!textSurface)
  {
    SDL_Log("Unable to render text surface! SDL_ttf Error: %s", TTF_GetError());
    return;
  }

  // Create a texture from the text surface
  SDL_Texture *textTexture =
      SDL_CreateTextureFromSurface(renderer, textSurface);
  if (!textTexture)
  {
    SDL_Log("Unable to create texture from text surface! SDL_Error: %s",
            SDL_GetError());
    SDL_FreeSurface(textSurface);
    return;
  }

  // Set the text position to center it on the screen
  SDL_Rect textRect = {WIDTH / 2 - textSurface->w / 2,
                       HEIGHT / 2 - textSurface->h / 2, textSurface->w,
                       textSurface->h};

  // Copy the texture to the renderer
  SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

  // Clean up
  SDL_DestroyTexture(textTexture);
  SDL_FreeSurface(textSurface);
}

void Game::renderTextLines(
    const std::vector<std::pair<std::string, SDL_Color>> &lines)
{
  std::vector<SDL_Texture *> textures;
  std::vector<SDL_Rect> rects;

  int totalHeight = 0;

  // First pass: Create textures and calculate total height
  for (const auto &[text, color] : lines)
  {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface)
    {
      SDL_Log("Failed to render text surface: %s", TTF_GetError());
      continue;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
      SDL_Log("Failed to create text texture: %s", SDL_GetError());
      SDL_FreeSurface(surface);
      continue;
    }

    SDL_Rect rect;
    rect.w = surface->w;
    rect.h = surface->h;
    totalHeight += rect.h;

    textures.push_back(texture);
    rects.push_back(rect);

    SDL_FreeSurface(surface);
  }

  // Calculate starting Y to vertically center the block
  int startY = HEIGHT / 2 - totalHeight / 2;

  // Second pass: Position and render each texture
  for (size_t i = 0; i < textures.size(); ++i)
  {
    SDL_Rect &rect = rects[i];
    rect.x = WIDTH / 2 - rect.w / 2;
    rect.y = startY;

    SDL_RenderCopy(renderer, textures[i], nullptr, &rect);
    startY += rect.h;

    SDL_DestroyTexture(textures[i]);
  }
}
