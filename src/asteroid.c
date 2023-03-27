#ifndef ASTEROID_
#define ASTEROID_
#include "../include/blasteroids.h"
#endif

extern Global * global;

void draw_asteroid()
{
	int res = 3;
	int size = res * 50;
	float thickness = 3.0f * res;
	if (global->AsteroidBitmap == NULL)
	{
		//Asteroid bitmap
		global->AsteroidBitmap = al_create_bitmap(size, size);
		int offset = size / 2;
		ALLEGRO_COLOR color = al_map_rgb(255,255,255);
		al_set_target_bitmap(global->AsteroidBitmap);

		al_draw_line(res * -20 + offset, res * 20  + offset, res * -25 + offset, res * 5   + offset, color, thickness);
		al_draw_line(res * -25 + offset, res * 5   + offset, res * -25 + offset, res * -10 + offset, color, thickness);
		al_draw_line(res * -25 + offset, res * -10 + offset, res * -5  + offset, res * -10 + offset, color, thickness);
		al_draw_line(res * -5  + offset, res * -10 + offset, res * -10 + offset, res * -20 + offset, color, thickness);
		al_draw_line(res * -10 + offset, res * -20 + offset, res * 5   + offset, res * -20 + offset, color, thickness);
		al_draw_line(res * 5   + offset, res * -20 + offset, res * 20  + offset, res * -10 + offset, color, thickness);
		al_draw_line(res * 20  + offset, res * -10 + offset, res * 20  + offset, res * -5  + offset, color, thickness);
		al_draw_line(res * 20  + offset, res * -5  + offset, res * 0   + offset, res * 0   + offset, color, thickness);
		al_draw_line(res * 0   + offset, res * 0   + offset, res * 20  + offset, res * 10  + offset, color, thickness);
		al_draw_line(res * 20  + offset, res * 10  + offset, res * 10  + offset, res * 20  + offset, color, thickness);
		al_draw_line(res * 10  + offset, res * 20  + offset, res * 0   + offset, res * 15  + offset, color, thickness);
		al_draw_line(res * 0   + offset, res * 15  + offset, res * -20 + offset, res * 20  + offset, color, thickness);

		al_set_target_bitmap(al_get_backbuffer(global->disp));
		LOG(1,"Asteroid Bitmap Created\n");
	}

	LOG(2, "Draw Asteroids Function Call\n");
	for (short i = 0; i < global->asteroids_max_count; i++)
	{
		LOG(3, "Drawing Asteroid %d\t is_dead: %d\n",i, global->asteroids[i].dead);
		global->asteroids[i].image = global->AsteroidBitmap;

		if (!global->asteroids[i].dead)
		{
			float s = global->asteroids[i].s = global->asteroids[i].scale * size;
			ALLEGRO_TRANSFORM transform;
			al_identity_transform(&transform);
			al_rotate_transform(&transform, global->asteroids[i].twist); //We rotate it
			al_translate_transform(&transform,global->asteroids[i].sx, global->asteroids[i].sy); //We move it to an initial position
			al_use_transform(&transform);
			al_draw_tinted_scaled_bitmap(
					global->asteroids[i].image,
					global->asteroids[i].color,
					0, 0,
					size, size,
					-s/2, -s/2,
					s, s,
					0);
		}
		LOG(2, "Drew Asteroid\n");
	}

	update_asteroid();
}

void spawn_asteroid(int wave)
{
    short dead_asteroids = 0;

    for (short i = 0; i < global->asteroids_max_count; i++)
    {
        if (global->asteroids[i].dead)
        {
            dead_asteroids++;
        }
    }
	// Check that the sum of dead and alive asteroids is equal to global->asteroids_max_count
	LOG(1, "Dead Asteroids %d\tAlive Asteroids %d",dead_asteroids, global->asteroids_alive);
    if (dead_asteroids + global->asteroids_alive != global->asteroids_max_count){
		LOG(1, "dead: %d, alive: %d, max: %d\n", dead_asteroids, global->asteroids_alive, global->asteroids_max_count);
        error("Error: Sum of dead and alive asteroids is not equal to global->asteroids_max_count\n");
	}

    if (global->asteroids_alive > global->asteroids_max_count)
        error("Error: More asteroids alive than the max count\n");


    if (dead_asteroids == global->asteroids_max_count)
    {
        global->asteroids_max_count++;
		Realloc_Asteroid();
        short new_asteroids_count = global->asteroids_max_count;
        for (short i = 0; i < global->asteroids_max_count && new_asteroids_count > 0; i++)
        {
            if (global->asteroids[i].dead)
            {
                int x_initial = rand() % 2 ?
                    (rand() % (DISPLAY_WIDTH / 2 - DISPLAY_WIDTH / 5)) :
                    DISPLAY_WIDTH - rand() % (DISPLAY_WIDTH / 2 - DISPLAY_WIDTH / 5);

                int y_initial = rand() % 2 ?
                    (rand() % (DISPLAY_HEIGHT / 2 - DISPLAY_HEIGHT / 5)) :
                    DISPLAY_HEIGHT - rand() % (DISPLAY_HEIGHT / 2 - DISPLAY_HEIGHT / 5);

                float heading_initial = (float)rand() / (float)RAND_MAX * (2 * PI);
                float twist_initial = (float)rand() / (float)RAND_MAX * (2 * PI);
                float speed_initial = (float)rand() / (float)RAND_MAX + 1;
                float rot_velocity_initial = (float)rand() / (float)RAND_MAX * 10;
                float scale_initial = 1.0;               

				global->asteroids[i].sx = x_initial;
				global->asteroids[i].sy = y_initial;
				global->asteroids[i].heading = heading_initial;
				global->asteroids[i].twist = twist_initial;
				global->asteroids[i].speed = speed_initial;
				global->asteroids[i].rot_velocity = rot_velocity_initial;
				global->asteroids[i].scale = scale_initial;
				global->asteroids[i].color = al_map_rgba_f(0.211, 0.368, 0.639, 1);

                global->asteroids_alive++;
                new_asteroids_count--;
				global->asteroids[i].dead = false;

                LOG(1, "Asteroid Spawned\n");
            }
        }
    }
}


void update_asteroid()
{
	for (short i = 0; i < global->asteroids_max_count; i++)
	{
		if (!global->asteroids[i].dead)
		{
  	  		LOG(2, "A%d: %d\t",i, global->asteroids[i].dead);
			if (global->event.timer.source == global->asteroid_rotation_timer)
				global->asteroids[i].twist += global->asteroids[i].rot_velocity * PI /180;

			if (global->asteroids[i].twist > 2 * PI)
				global->asteroids[i].twist = 0;

			if (global->asteroids[i].twist <  0)
				global->asteroids[i].twist = 2 * PI;

			global->asteroids[i].sx += global->asteroids[i].speed * cos(global->asteroids[i].heading);
			global->asteroids[i].sy += global->asteroids[i].speed * sin(global->asteroids[i].heading);

			teleport(&global->asteroids[i].sx, &global->asteroids[i].sy);
		}
	}
	LOG(2, "Asteroids alive after Update: %d\n", global->asteroids_alive);
}

void Split(short j)
{
    if (global->asteroids[j].scale > 0.5)
        global->asteroids[j].scale -= global->asteroids[j].scale / 3;
    else
    {
        global->asteroids[j].dead = true;
        global->asteroids_alive--;
        LOG(2, "Killed Asteroid");
    }
}

/*
 * if an asteroid is hit by a blast from the spaceship's cannon
 * it immediately splits into two
 * Each of these parts will be half the size of the original asteroid.
 * Once an asteroid has been split 2 times, it's dead.
 * The player score increases by 100 with each hit
 *
 * Use linked lists for sets of asteroid
 * or arrays
*/
