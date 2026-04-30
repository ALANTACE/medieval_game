#include "player.h"

#include <string.h>

inline void player_init(const char name[MAX_NAME_LENGTH]) {
    // Player info
    strncpy(player.name, name, MAX_NAME_LENGTH - 1);
    player.name[MAX_NAME_LENGTH - 1] = '\0';

    // Player position
    player.pos.x = 0.0f;
    player.pos.y = 0.0f;
    player.rect.x = player.pos.x;
    player.rect.y = player.pos.y;

    // Player velocity
    player.velocity.dx = 0.0f;
    player.velocity.dy = 0.0f;
    player.status = IDLE;

    // Player dimensions
    player.dimensions.width = 256.0f;
    player.dimensions.height = 256.0f;
    player.rect.w = player.dimensions.width;
    player.rect.h = player.dimensions.height;

    // Player stats
    player.health = 100;
    player.damage = 10.0f;
}
