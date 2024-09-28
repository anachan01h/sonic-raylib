#pragma once

#include "raylib.h"

#define ACCELERATION 0.046875
#define TOP_SPEED 6
#define JUMP_FORCE 6.5
#define GRAVITY_FORCE 0.21875
#define AIR_ACCELERATION 0.09375

typedef enum State {
    NORMAL,
    AIRBORNE,
} State;

typedef struct Player {
    Vector2 pos;
    Vector2 speed;
    float ground_speed;
    float ground_angle;
    int width_radius;
    int height_radius;
    State state;
} Player;

void sonic_update(Player *sonic);
