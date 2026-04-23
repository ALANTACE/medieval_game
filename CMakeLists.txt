# Cmake project config
cmake_minimum_required(VERSION 4.2)
project(medieval_game C)
set(CMAKE_C_STANDARD 11)

# SDL3 options config
set(SDL_SHARED ON CACHE BOOL "Build shared library")
set(SDL_STATIC OFF CACHE BOOL "Build static library")
set(SDL_TEST OFF CACHE BOOL "Disable SDL tests")

# Add the SDL3 library
add_subdirectory(deps/SDL)

# Game executable
add_executable(game
        source/main.c
        source/main.h
        source/renderer.c
        source/renderer.h
        source/player.c
        source/player.h
        source/game.c
        source/game.h
        source/error.h)

# Link SDL3 to the game
target_link_libraries(game PRIVATE SDL3::SDL3-shared)
