#ifndef RENDERER_H
#define RENDERER_H

/* INCLUDES */
#include "SDL3/SDL_render.h"

/* FUNCTIONS */
int renderer_init(SDL_Window **window, SDL_Renderer **renderer);
void renderer_render(SDL_Renderer *renderer, SDL_Texture *texture);

#endif