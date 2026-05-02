#ifndef GAME_H
#define GAME_H

/* INCLUDES */
#include <stdbool.h>

/* STRUCTS */
typedef struct {
    // Player-based inputs
    bool move_up;
    bool move_down;
    bool move_left;
    bool move_right;
    bool run;
    bool dash;
    bool quit;

    // Camera-based inputs
    bool camera_up;
    bool camera_down;
    bool camera_left;
    bool camera_right;
} InputState;

/* FUNCTIONS */
void game_input(InputState *input);
void game_update(InputState *input, uint64_t delta_time, uint64_t FPS);

/* STATIC FUNCTIONS */
static void update_player_velocity(InputState input, uint64_t delta_time);
static void update_cooldowns(InputState *input, uint64_t delta_time);
static void update_camera_position(const InputState input, const uint64_t delta_time);
#endif