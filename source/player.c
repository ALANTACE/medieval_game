#include "player.h"

#include <string.h>

inline void player_init(const char name[MAX_NAME_LENGTH]) {
    strncpy(player.name, name, MAX_NAME_LENGTH - 1);
    player.name[MAX_NAME_LENGTH - 1] = '\0';

    player.pos.x = 0.0f;
    player.pos.y = 0.0f;

    player.velocity.dx = 0.0f;
    player.velocity.dy = 0.0f;

    player.dimensions.width = 256.0f;
    player.dimensions.height = 256.0f;

    player.health = 100;
    player.speed = 1.0f;
    player.direction = 0.0f;

    player.rect.x = 0.0f;
    player.rect.y = 0.0f;
    player.rect.w = 256.0f;
    player.rect.h = 256.0f;
}
