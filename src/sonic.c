#include <math.h>
#include "../inc/sonic.h"

void sonic_update(Player *sonic) {
    switch (sonic->state) {
    case NORMAL:
        if (IsKeyDown(KEY_SPACE)) {
            sonic->state = AIRBORNE;
            sonic->speed.x -= JUMP_FORCE * sinf(sonic->ground_angle);
            sonic->speed.y -= JUMP_FORCE * cosf(sonic->ground_angle);
            break;
        }

        if (IsKeyDown(KEY_LEFT)) {
            if (sonic->ground_speed > 0) {
                sonic->ground_speed -= 0.5;
                if (sonic->ground_speed <= 0)
                    sonic->ground_speed = -0.5;
            } else if (sonic->ground_speed > -TOP_SPEED) {
                sonic->ground_speed -= ACCELERATION;
                if (sonic->ground_speed <= -TOP_SPEED)
                    sonic->ground_speed = -TOP_SPEED;
            }
        }

        if (IsKeyDown(KEY_RIGHT)) {
            if (sonic->ground_speed < 0) {
                sonic->ground_speed += 0.5;
                if (sonic->ground_speed >= 0)
                    sonic->ground_speed = 0.5;
            } else if (sonic->ground_speed < TOP_SPEED) {
                sonic->ground_speed += ACCELERATION;
                if (sonic->ground_speed >= TOP_SPEED)
                    sonic->ground_speed = TOP_SPEED;
            }
        }

        if (IsKeyUp(KEY_RIGHT) && IsKeyUp(KEY_LEFT))
            sonic->ground_speed -= copysign(fminf(fabsf(sonic->ground_speed), ACCELERATION), sonic->ground_speed);

        // Atualiza velocidade
        sonic->speed.x = sonic->ground_speed * cosf(sonic->ground_angle);
        sonic->speed.y = sonic->ground_speed * (-sinf(sonic->ground_angle));
        
        // Atualiza posição
        sonic->pos.x += sonic->speed.x;
        sonic->pos.y += sonic->speed.y;

        break;

    case AIRBORNE:
        if (IsKeyUp(KEY_SPACE) && sonic->speed.y < -4)
            sonic->speed.y = -4;

        if (IsKeyDown(KEY_LEFT)) {
            sonic->speed.x -= AIR_ACCELERATION;
            if (sonic->speed.x < -TOP_SPEED)
                sonic->speed.x = -TOP_SPEED;
        }

        if (IsKeyDown(KEY_RIGHT)) {
            sonic->speed.x += AIR_ACCELERATION;
            if (sonic->speed.x > TOP_SPEED)
                sonic->speed.x = TOP_SPEED;
        }

        if (sonic->speed.y < 0 && sonic->speed.y > -4)
            sonic->speed.x -= (sonic->speed.x / 0.125) / 256;

        sonic->pos.x += sonic->speed.x;
        sonic->pos.y += sonic->speed.y;

        sonic->speed.y += GRAVITY_FORCE;

        if (sonic->pos.y > 359) {
            sonic->state = NORMAL;
            sonic->pos.y = 359;
            sonic->speed.y = 0;
            sonic->ground_speed = sonic->speed.x;
            sonic->ground_angle = 0;
        }
    }

}
