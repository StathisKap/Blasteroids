#ifndef COLLISIONS_
#define COLLISIONS_
#include "../include/blasteroids.h"
#endif

extern Global *global;

bool Box_Collision_Ship()
{
    for (int i = 0; i < global->asteroids_max_count * 2; i++)
    {
        if (!global->asteroids[i].dead)
        {
            if (global->ship.sx - 10 * global->ship.scale > global->asteroids[i].sx + 12.5 * 6 * global->asteroids[i].scale || // Left
                global->ship.sx + 10 * global->ship.scale < global->asteroids[i].sx - 12.5 * 6 * global->asteroids[i].scale || // Right
                global->ship.sy - 10 * global->ship.scale > global->asteroids[i].sy + 12.5 * 6 * global->asteroids[i].scale || // Up
                global->ship.sy + 10 * global->ship.scale < global->asteroids[i].sy - 12.5 * 6 * global->asteroids[i].scale)   // Down
                continue;
            else
            {
                global->ship.live = false;
                global->Player_Lives--;
			          al_play_sample(global->death_sound, 0.7, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                return true;
            }
        }
    }
    return false;
}

bool Box_Collision_Bullets()
{
    for (short i = 0; i < BULLET_COUNT; i++)
    {
        if (global->bullets[i].live == false)
            continue;
        for (short j = 0; j < global->asteroids_max_count * 2; j++)
        {
            if (global->asteroids[j].dead)
                continue;
            if (global->bullets[i].sx > global->asteroids[j].sx + 12.5 * 6 * global->asteroids[j].scale ||
                global->bullets[i].sx < global->asteroids[j].sx - 12.5 * 6 * global->asteroids[j].scale ||
                global->bullets[i].sy > global->asteroids[j].sy + 12.5 * 6 * global->asteroids[j].scale ||
                global->bullets[i].sy < global->asteroids[j].sy - 12.5 * 6 * global->asteroids[j].scale)
                continue;
            else
            {
                global->bullets[i].live = false;
                Split(j);
                return true;
            }
        }
    }
    return false;
}
