#ifndef PLAYER_H
#define PLAYER_H

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

    int health;
    float speed; // Use speed to assign it to velocity
} Player;

/* FUNCTIONS */
Player player_init(const char name[MAX_NAME_LENGTH]);

#endif