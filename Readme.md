# Cnake <span style='font-size: 0.5em'>Snake Game (SDL2)</span>

This is a classic snake game implemented using **C++** with **SDL2**, **SDL2_image**, and **SDL2_ttf**.

## Features
- Snake grows when eating food
- Pause functionality
<!-- - Basic scoring -->
- Displays text using embedded TTF font
- Uses an embedded PNG image for food

## Dependencies
Ensure the following libraries are installed:
- SDL2
- SDL2_image
- SDL2_ttf

On Ubuntu/Debian-based systems:
```bash
sudo apt update
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```

## Building the Project
Use CMake to configure and build the project.

```bash
mkdir build
cd build
cmake ..
make
```

The binary `SnakeGame` will be generated in the `build` directory.

## Embedding Assets
To include assets like fonts and images directly into the binary using `xxd`, run the following commands:

```bash
xxd -i apple.png > food_sprite.h
xxd -i WinkyRough-Medium.ttf > font_data.h
```

- Include `food_sprite.h` to use `apple_png` byte array for rendering food sprite.
- Include `font_data.h` to use `WinkyRough_Medium_ttf` for rendering text.

These files are linked into the game using SDL_RWFromMem.

## Running the Game
```bash
./SnakeGame
```

Use arrow keys to control the snake.
- Press `P` to pause/resume
- Press `R` to reset after game over

## Folder Structure
```
snake/
├── assets/
│   ├── apple.png
│   ├── food_sprite.h
│   ├── WinkyRough-Medium.ttf
│   └── font_data.h
├── core/
│   ├── Game.cpp
│   ├── Game.hpp
│   ├── Snake.cpp
│   ├── Snake.hpp
│   ├── Food.cpp
│   └── Food.hpp
├── CMakeLists.txt
└── main.cpp
```

## Output

[Game](./misc/game.gif)

## Notes
- Ensure `SDL2_ttf` and `SDL2_image` are linked properly in your `CMakeLists.txt`.
- Handle text and image rendering via SDL_RWFromMem for the embedded data.

## License
MIT License

