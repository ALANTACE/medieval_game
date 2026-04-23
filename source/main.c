#include "macros.h"
#include "error.h"
#include "player.h"
#include "renderer.h"
#include "game.h"
#include "main.h"

#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// Global player variable
Player player;

int main(int argc, char* argv[]) {
    /* INITIALIZATIONS */
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (renderer_init(&window, &renderer) != 0) { return 1; }

    // Player
    const char name[MAX_NAME_LENGTH] = "Bob"; // TODO: implement a method of getting the player name
    player_init(name);

    // Time variables
    uint64_t last_time = SDL_GetTicksNS();
    uint64_t current_time = 0;
    float delta_time = 0;

    // Event handling variables
    SDL_Event event;
    InputState input = {false};

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    /* MAIN LOOP */
    while (!input.quit) {
        // Calculate delta time
        current_time = SDL_GetTicksNS();
        delta_time = (float)(current_time - last_time) / 1000000000.0f;
        last_time = current_time;

        // Get input information
        game_input(&input);

        // Update the game
        game_update(input, delta_time);

        // RENDER
        renderer_render(renderer, player.texture);

        // Caps the frame rate to MAX_REFRESH_RATE for lower CPU usage
        SDL_DelayPrecise(SDL_NS_TO_MS(1000000000 / MAX_REFRESH_RATE));
    }

    return 0;
}