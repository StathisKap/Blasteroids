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
		printf("Asteroid Bitmap Created\n");
	}

	for (size_t i = 0; i <= MAX_BIG_ASTEROIDS; i++)
	{
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
					0,
					0,
					size,
					size,
					-s/2,
					-s/2,
					s,
					s,
					0);
		}
	}

	update_asteroid();
}

void spawn_asteroid()
{
	int x_initial = arc4random() * arc4random() % DISPLAY_WIDTH;
	int y_initial = arc4random() * arc4random() % DISPLAY_HEIGHT;

	float heading_initial = (arc4random() % (int)(2 * PI));
	float twist_initial = (arc4random() % (int)(2 * PI));
	float speed_initial = arc4random() % 2 + 1;
	float rot_velocity_initial = arc4random() % 10;
	float scale_initial = 1.0;

	for (size_t i = 0; i < MAX_BIG_ASTEROIDS; i++)
	{

		if (global->asteroids[i].dead) //If it is true then
		{
			global->asteroids[i].sx = x_initial;
			global->asteroids[i].sy = y_initial;
			global->asteroids[i].heading = heading_initial;
			global->asteroids[i].twist = twist_initial;
			global->asteroids[i].speed = speed_initial;
			global->asteroids[i].rot_velocity = rot_velocity_initial;
			global->asteroids[i].scale = scale_initial;
			global->asteroids[i].color = al_map_rgba_f(0.211, 0.368, 0.639, 1);
			global->asteroids[i].dead = false; // It turns it to false
			break;
		}
	}
}

void update_asteroid()
{
	for (size_t i = 0; i <= MAX_BIG_ASTEROIDS; i++)
	{

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
