#ifndef COLLISIONS_
#define COLLISIONS_
#include "../include/blasteroids.h"
#endif

extern Global * global;

bool Box_Collision()
{
    al_identity_transform(&global->ship.transform);
    al_use_transform(&global->ship.transform);
    al_draw_rectangle(
            global->ship.sx + 10 * global->ship.scale,
            global->ship.sy + 10 * global->ship.scale,
            global->ship.sx - 10 * global->ship.scale,
            global->ship.sy - 10 * global->ship.scale,
            al_map_rgb(255,0,0),
            4);


    for (int i = 0; i < MAX_BIG_ASTEROIDS; i++)
    {
        al_draw_rectangle(
                global->asteroids[i].sx + 10 * 6 * global->asteroids[i].scale,
                global->asteroids[i].sy + 10 * 6 * global->asteroids[i].scale,
                global->asteroids[i].sx - 10 * 6 * global->asteroids[i].scale,
                global->asteroids[i].sy - 10 * 6 * global->asteroids[i].scale,
                al_map_rgb(255,0,0),
                4);

        if (global->ship.sx - 10 * global->ship.scale > global->asteroids[i].sx + 10 * 6 * global->asteroids[i].scale || // Left
            global->ship.sx + 10 * global->ship.scale < global->asteroids[i].sx - 10 * 6 * global->asteroids[i].scale || // Right
            global->ship.sy - 10 * global->ship.scale > global->asteroids[i].sy + 10 * 6 * global->asteroids[i].scale || // Up
            global->ship.sy + 10 * global->ship.scale < global->asteroids[i].sy - 10 * 6 * global->asteroids[i].scale) // Down
            {
		    	      global->asteroids[i].color = al_map_rgba_f(0.211, 0.368, 0.639, 1);
            }
        else
            global->asteroids[i].color = al_map_rgb(255,255,255);
    }
    return false;
}

bool Distance_Colission()
{

    return false;
}
