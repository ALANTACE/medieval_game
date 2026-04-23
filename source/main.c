#include "error.h"
#include "player.h"
#include "game.h"
#include "main.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char* argv[]) {
    /* INITIALIZATIONS */
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *bitmapTex = NULL;
    SDL_Surface *bitmapSurface = NULL;
    bool running = true;
    const char name[MAX_NAME_LENGTH] = "Bob"; // TODO: implement a method of getting the player name

    // SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow(WINDOW_TITLE, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, NULL);

    // Player
    Player player = player_init(name);

    // Time
    uint64_t last_time = SDL_GetTicksNS();
    uint64_t current_time = 0;
    double delta_time = 0;


    /* MAIN LOOP */
    while (running) {
        ErrorType error = NONE;

        current_time = SDL_GetTicksNS();
        delta_time = (double)(current_time - last_time) / 1000000000.0f;
        last_time = current_time;

        // TODO:
        // INPUT

        error = update(player, delta_time);

        // RENDER

        if (error == FATAL_ERROR) {
            perror("Fatal error.");
            break;
        }

        // Caps the frame rate to MAX_REFRESH_RATE for lower CPU usage
        SDL_DelayPrecise(SDL_NS_TO_MS(1000000000 / MAX_REFRESH_RATE));
    }

    return 0;
}