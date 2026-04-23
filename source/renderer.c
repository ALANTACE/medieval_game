#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "macros.h"
#include "player.h"
#include "renderer.h"

#include <SDL3_image/SDL_image.h>

inline int renderer_init(SDL_Window **window, SDL_Renderer **renderer) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    // Initialize SDL's variables for the renderer
    *window = SDL_CreateWindow(WINDOW_TITLE, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    *renderer = SDL_CreateRenderer(*window, NULL);

    // After renderer is initialized, set the player texture
    player.texture = IMG_LoadTexture(*renderer, "../../assets/images/rick_and_morty.png");

    return 0;
}

inline void renderer_render(SDL_Renderer *renderer, SDL_Texture *texture) {
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, player.texture, NULL, &player.rect);
    SDL_RenderPresent(renderer);
}