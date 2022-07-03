#ifndef COLLISIONS_
#define COLLISIONS_
#include "../include/blasteroids.h"
#endif

extern Global * global;

bool Box_Collision_Ship()
{
    for (int i = 0; i < MAX_BIG_ASTEROIDS; i++)
    {
        if (global->ship.sx - 10 * global->ship.scale > global->asteroids[i].sx + 12.5 * 6 * global->asteroids[i].scale || // Left
            global->ship.sx + 10 * global->ship.scale < global->asteroids[i].sx - 12.5 * 6 * global->asteroids[i].scale || // Right
            global->ship.sy - 10 * global->ship.scale > global->asteroids[i].sy + 12.5 * 6 * global->asteroids[i].scale || // Up
            global->ship.sy + 10 * global->ship.scale < global->asteroids[i].sy - 12.5 * 6 * global->asteroids[i].scale) // Down
		            continue;
        else
            return true;
    }
    return false;
}

bool Box_Collision_Bullets()
{
    for (int i = 0; i < BULLET_COUNT; i++)
    {
        if (global->bullets[i].live == false)
            continue;
            for (int j = 0; j < MAX_BIG_ASTEROIDS; j++)
            {
                if (global->bullets[i].sx > global->asteroids[j].sx + 12.5 * 6 * global->asteroids[j].scale ||
                    global->bullets[i].sx < global->asteroids[j].sx - 12.5 * 6 * global->asteroids[j].scale ||
                    global->bullets[i].sy > global->asteroids[j].sy + 12.5 * 6 * global->asteroids[j].scale ||
                    global->bullets[i].sy < global->asteroids[j].sy - 12.5 * 6 * global->asteroids[j].scale)
		            	      continue;
                else
                    return true;
            }
    }
    return false;
}

void Check_For_Collisions()
{
    if (Box_Collision_Bullets())
        printf("Bullet Collision\n");
    if (Box_Collision_Ship())
        printf("Ship Collision\n");
}
