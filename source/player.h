#ifndef PLAYER_H
#define PLAYER_H

/* INCLUDES */
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"

/* DEFINES */
#define MAX_NAME_LENGTH 32

/* STRUCTS */
typedef struct {
    float x;
    float y;
} Position;

typedef struct {
    float dx;
    float dy;
} Velocity;

typedef struct {
    float width;
    float height;
} Dimensions;

typedef struct {
    char name[MAX_NAME_LENGTH];
    Position pos;
    Velocity velocity;
    Dimensions dimensions;

    // Player module
    SDL_FRect rect;
    SDL_Texture *texture;

    int health;
    float speed; // Use speed to affect velocity
    float direction; // Angle measured in degrees (360)
} Player;

extern Player player;

/* FUNCTIONS */
void player_init(const char name[MAX_NAME_LENGTH]);

#endif