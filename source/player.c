#include "player.h"

#include <string.h>

Player player_init(const char name[MAX_NAME_LENGTH]) {
    Player player;

    strncpy(player.name, name, MAX_NAME_LENGTH - 1);
    player.name[MAX_NAME_LENGTH - 1] = '\0';
    player.pos.x = 0.0f;
    player.pos.y = 0.0f;
    player.velocity.dx = 0.0f;
    player.velocity.dy = 0.0f;
    player.dimensions.width = 10.0f;
    player.dimensions.height = 10.0f;
    player.health = 100;
    player.speed = 0.0f;

    return player;
}
