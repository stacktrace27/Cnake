cmake_minimum_required(VERSION 3.10)
project(Cnake)

set(CMAKE_CXX_STANDARD 17)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

if (NOT SDL2_IMAGE_FOUND)
    set(SDL2_IMAGE_INCLUDE_DIRS /usr/include/SDL2) 
    set(SDL2_IMAGE_LIBRARIES /usr/lib/x86_64-linux-gnu/libSDL2_image.so)
endif()

if (NOT SDL2_TTF_FOUND)
    set(SDL2_TTF_INCLUDE_DIRS /usr/include/SDL2)
    set(SDL2_TTF_LIBRARIES /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so)
endif()

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} core assets)

add_executable(CnakeGame
    main.cpp
    core/Game.cpp
    core/Snake.cpp
    core/Food.cpp
)

target_link_libraries(CnakeGame
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}  # Link SDL2_ttf library
)
