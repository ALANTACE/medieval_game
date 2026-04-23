#ifndef GAME_H
#define GAME_H

/* INCLUDES */
#include <stdbool.h>

/* STRUCTS */
typedef struct {
    bool move_up;
    bool move_down;
    bool move_left;
    bool move_right;
    bool quit;
} InputState;

/* FUNCTIONS */
void game_input(InputState *input);
void game_update(InputState input, float delta_time);
#endif