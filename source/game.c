#include "SDL3/SDL_events.h"
#include "error.h"
#include "player.h"
#include "game.h"

#include <stdio.h>

/* GLOBAL VARIABLES */
uint64_t dash_cooldown = 0;

/* FUNCTIONS */
void game_input(InputState *input) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            input->quit = true;
        }
    }

    const bool *keyboard = SDL_GetKeyboardState(NULL);

    input->move_up = keyboard[SDL_SCANCODE_W];
    input->move_down = keyboard[SDL_SCANCODE_S];
    input->move_left = keyboard[SDL_SCANCODE_A];
    input->move_right = keyboard[SDL_SCANCODE_D];
    input->run = keyboard[SDL_SCANCODE_LSHIFT];

    if ((dash_cooldown == 200000000) && (!keyboard[SDL_SCANCODE_SPACE])) {

        dash_cooldown = 0;
    } else if (dash_cooldown == 0) {
        input->dash = keyboard[SDL_SCANCODE_SPACE];
    }
}

void game_update(InputState *input, const uint64_t delta_time, const uint64_t FPS) {
    // Update cooldowns
    update_cooldowns(input, delta_time);

    // Update player velocity
    update_player_velocity(*input, delta_time);

    // Update player position
    player.pos.x += player.velocity.dx * ((float)delta_time / 1000000000.0f);
    player.pos.y += player.velocity.dy * ((float)delta_time / 1000000000.0f);

    // Update player rectangle
    player.rect.x = player.pos.x;
    player.rect.y = player.pos.y;
}

/* STATIC FUNCTIONS */
static void update_player_velocity(const InputState input, const uint64_t delta_time)
{
    float diagonal_coefficient = 1.0f;
    float step = PLAYER_WALKING_SPEED;

    // Check for dash/run before updating dx/dy
    if (input.dash) {
        step = PLAYER_DASH_SPEED;
        player.status = DASHING;
    }
    else if (input.run) {
        step = PLAYER_RUNNING_SPEED;
        player.status = RUNNING;
    }
    else if ((player.velocity.dx != 0) || (player.velocity.dy != 0)) {
        player.status = WALKING;
    }
    else {
        player.status = IDLE;
    }

    // Update dx
    if ((input.move_left) && (input.move_right) ||  // If both OR neither AD keys are pressed STOP moving
        (!input.move_left) && (!input.move_right)) {
        if (player.velocity.dx == 0) {

        } else if (player.velocity.dx > 0) {
            player.velocity.dx -= PLAYER_DECELERATION * ((float)delta_time / 1000000000.0f);
            if (player.velocity.dx < 0) { player.velocity.dx = 0;}
        } else if (player.velocity.dx < 0) {
            player.velocity.dx += PLAYER_DECELERATION * ((float)delta_time / 1000000000.0f);
            if (player.velocity.dx > 0) { player.velocity.dx = 0;}
        }
    } else if (input.move_left) { // Only the A key is pressed
        // If the player is moving diagonally reduce speed by sqrt(2)
        if (((input.move_up) && (!input.move_down)) || ((!input.move_up) && (input.move_down))) {
            diagonal_coefficient = 1.414f;
        }

        player.velocity.dx -= PLAYER_ACCELERATION * ((float)delta_time / 1000000000.0f) / diagonal_coefficient;
        if (player.velocity.dx < (-step) / diagonal_coefficient) { player.velocity.dx = (-step) / diagonal_coefficient; }
    } else  { // Only the D key is pressed
        // If the player is moving diagonally reduce speed by sqrt(2)
        if (((input.move_up) && (!input.move_down)) || ((!input.move_up) && (input.move_down))) {
            diagonal_coefficient = 1.414f;
        }

        player.velocity.dx += PLAYER_ACCELERATION * ((float)delta_time / 1000000000.0f) / diagonal_coefficient;
        if (player.velocity.dx > step / diagonal_coefficient) { player.velocity.dx = step / diagonal_coefficient; }
    }

    // Update dy
    if ((input.move_up) && (input.move_down) ||  // If both OR neither SW keys are pressed STOP moving
        (!input.move_up) && (!input.move_down)) {
        if (player.velocity.dy == 0) {

        } else if (player.velocity.dy > 0) {
            player.velocity.dy -= PLAYER_DECELERATION * ((float)delta_time / 1000000000.0f);
            if (player.velocity.dy < 0) { player.velocity.dy = 0; }
        } else if (player.velocity.dy < 0) {
            player.velocity.dy += PLAYER_DECELERATION * ((float)delta_time / 1000000000.0f);
            if (player.velocity.dy > 0) { player.velocity.dy = 0; }
        }
    } else if (input.move_up) { // Only the W key is pressed
        // If the player is moving diagonally reduce speed by sqrt(2)
        if (((input.move_left) && (!input.move_right)) || ((!input.move_left) && (input.move_right))) {
            diagonal_coefficient = 1.414f;
        }

        player.velocity.dy -= PLAYER_ACCELERATION * ((float)delta_time / 1000000000.0f) / diagonal_coefficient;
        if (player.velocity.dy < (-step) / diagonal_coefficient) { player.velocity.dy = (-step) / diagonal_coefficient; }
    } else  { // Only the S key is pressed
        // If the player is moving diagonally reduce speed by sqrt(2)
        if (((input.move_left) && (!input.move_right)) || ((!input.move_left) && (input.move_right))) {
            diagonal_coefficient = 1.414f;
        }

        player.velocity.dy += PLAYER_ACCELERATION * ((float)delta_time / 1000000000.0f) / diagonal_coefficient;
        if (player.velocity.dy > step / diagonal_coefficient) { player.velocity.dy = step / diagonal_coefficient; }
    }
}

static void update_cooldowns(InputState *input, const uint64_t delta_time) {
    // Handle player dashing
    if (input->dash) {
        // If dash was inactive, activate the cooldown
        if (dash_cooldown == 0) { dash_cooldown = 200000000; }
        dash_cooldown -= delta_time;

        // If dash duration expires, deactivate the dash and set the cooldown to a ghost state
        //
        // I set dash_cooldown = 200000000, because it can never have that value except when the
        // dash ends (and i set it manually). So when the user keeps space pressed, the player dashes
        // only once and waits for the release of thet space bar. After the release the dash_cooldown
        // is set to 0, and on press the cooldown starts again.
        if ((int64_t)dash_cooldown <= 0) {
            input->dash = false;
            dash_cooldown = 200000000;
        }
    }
}