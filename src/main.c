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

#include "raylib.h"

int main(void) {
    const int screen_width = 640;
    const int screen_height = 480;

    InitWindow(screen_width, screen_height, "Sonic Demo");

    Texture2D sonic = LoadTexture("./img/running.png");

    Vector2 pos = { 0, 444 };
    Rectangle frame_size = { 0.0, 0.0, sonic.width/4, sonic.height };
    
    int current_frame = 0;
    int frame_counter = 0;
    int frame_speed = 15;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        ++frame_counter;
        pos.x += 4;

        if (pos.x >= 640)
            pos.x = -31;

        if (frame_counter >= 60 / frame_speed) {
            frame_counter = 0;
            ++current_frame;

            if (current_frame > 3)
                current_frame = 0;

            frame_size.x = current_frame * sonic.width/4;
        }

        BeginDrawing();
        
        ClearBackground(BLUE);

        DrawTextureRec(sonic, frame_size, pos, WHITE);

        EndDrawing();
    }

    UnloadTexture(sonic);
    CloseWindow();

    return 0;
}
