/* -----------------------------------------------------------------------------
 * ### main.c (sonic-raylib)
 * By: anachan01h
 *
 * Copyright (C) 2024 Ana C. Hernandes
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * -------------------------------------------------------------------------- */

#include <math.h>
#include "raylib.h"

#define ACCELERATION 0.046875
#define TOP_SPEED 6

typedef struct Player {
    Vector2 pos;
    Vector2 speed;
    float ground_speed;
    float ground_angle;
    int width_radius;
    int height_radius;
} Player;

int main(void) {
    const int screen_width = 640;
    const int screen_height = 480;
    Player sonic = { 0 };

    InitWindow(screen_width, screen_height, "Sonic Demo");

    sonic.pos = (Vector2) {20, 359};
    sonic.speed = (Vector2) {0, 0};
    sonic.width_radius = 20;
    sonic.height_radius = 20;
    sonic.ground_speed = 0;
    sonic.ground_angle = 0;

    Rectangle floor1 = {0, 380 , 640, 100};

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_LEFT)) {
            if (sonic.ground_speed > 0) {
                sonic.ground_speed -= 0.5;
                if (sonic.ground_speed <= 0)
                    sonic.ground_speed = -0.5;
            } else if (sonic.ground_speed > -TOP_SPEED) {
                sonic.ground_speed -= ACCELERATION;
                if (sonic.ground_speed <= -TOP_SPEED)
                    sonic.ground_speed = -TOP_SPEED;
            }
        }

        if (IsKeyDown(KEY_RIGHT)) {
            if (sonic.ground_speed < 0) {
                sonic.ground_speed += 0.5;
                if (sonic.ground_speed >= 0)
                    sonic.ground_speed = 0.5;
            } else if (sonic.ground_speed < TOP_SPEED) {
                sonic.ground_speed += ACCELERATION;
                if (sonic.ground_speed >= TOP_SPEED)
                    sonic.ground_speed = TOP_SPEED;
            }
        }

        if (IsKeyUp(KEY_RIGHT) && IsKeyUp(KEY_LEFT))
            sonic.ground_speed -= copysign(fminf(fabsf(sonic.ground_speed), ACCELERATION), sonic.ground_speed);
        
        // Atualiza velocidade
        sonic.speed.x = sonic.ground_speed * cosf(sonic.ground_angle);
        sonic.speed.y = sonic.ground_speed * (-sinf(sonic.ground_angle));
        
        // Atualiza posição
        sonic.pos.x += sonic.speed.x;
        sonic.pos.y += sonic.speed.y;
        
        BeginDrawing();
        
        ClearBackground(DARKGRAY);

        DrawRectangleRec(floor1, DARKGREEN);

        Rectangle player_rect = {
            sonic.pos.x - sonic.width_radius,
            sonic.pos.y - sonic.height_radius,
            2 * sonic.width_radius + 1,
            2 * sonic.height_radius + 1,
        };
        DrawRectangleRec(player_rect, BLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
