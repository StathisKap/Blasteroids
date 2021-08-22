#ifndef ASTEROID_
#define ASTEROID_
#include "../include/blasteroids.h"
#endif

extern Asteroid *asteroids;
extern Spaceship ship;
extern ALLEGRO_EVENT_QUEUE *queue;
extern ALLEGRO_EVENT event;
ALLEGRO_TIMER* asteroid_rotation_timer;

void draw_asteroid()
{
	for (size_t i = 0; i < MAX_BIG_ASTEROIDS; i++)
	{
		if (!asteroids[i].gone)
		{
			ALLEGRO_TRANSFORM transform; 
			al_identity_transform(&transform);
			al_rotate_transform(&transform, asteroids[i].twist); //We rotate it
			al_translate_transform(&transform,asteroids[i].sy, asteroids[i].sx); //We move it to an initial position
			al_use_transform(&transform);
 			al_draw_line(-20, 20, -25, 5, asteroids[i].color, 2.0f);
 			al_draw_line(-25, 5, -25, -10, asteroids[i].color, 2.0f);
 			al_draw_line(-25, -10, -5, -10, asteroids[i].color, 2.0f);
 			al_draw_line(-5, -10, -10, -20, asteroids[i].color, 2.0f);
 			al_draw_line(-10, -20, 5, -20, asteroids[i].color, 2.0f);
 			al_draw_line(5, -20, 20, -10, asteroids[i].color, 2.0f);
 			al_draw_line(20, -10, 20, -5, asteroids[i].color, 2.0f);
 			al_draw_line(20, -5, 0, 0, asteroids[i].color, 2.0f);
 			al_draw_line(0, 0, 20, 10, asteroids[i].color, 2.0f);
 			al_draw_line(20, 10, 10, 20, asteroids[i].color, 2.0f);
 			al_draw_line(10, 20, 0, 15, asteroids[i].color, 2.0f);
			al_draw_line(0, 15, -20, 20, asteroids[i].color, 2.0f);
		}
		
	}

	update_asteroid();	
}

void spawn_asteroid()
{
	int x_initial = ((rand() % 2) - 1) + rand() % DISPLAY_WIDTH;
	int y_initial = ((rand() % 2) - 1) + rand() % DISPLAY_HEIGHT;
	int heading_initial = (rand() % (int)(2 * PI));
	int twist_initial = (rand() % (int)(2 * PI));
	int speed_initial = rand() % 2 + 1;
	int rot_velocity_initial = rand() % 10;
	int scale_initial = rand() % 4 + 1;

	for (size_t i = 0; i < MAX_BIG_ASTEROIDS; i++)
	{
		
		if (asteroids[i].gone) //If it is true then
		{
			asteroids[i].sx = x_initial; // It sets the starting position to where the ship is
			asteroids[i].sy = y_initial;
			asteroids[i].heading = heading_initial; // It sets the heading equal to wherever the ship was looking
			asteroids[i].twist = twist_initial;
			asteroids[i].speed = speed_initial;
			asteroids[i].rot_velocity = rot_velocity_initial;
			asteroids[i].scale = scale_initial;
			asteroids[i].gone = false; // It turns it to false 
			asteroids[i].color = al_map_rgb(54, 94, 163);
			break;
		}
		
	}
	
}

void update_asteroid()
{
	for (size_t i = 0; i < MAX_BIG_ASTEROIDS; i++)
	{

		if (event.timer.source == asteroid_rotation_timer)
			asteroids[i].twist += asteroids[i].rot_velocity * PI /180;
		
		if (asteroids[i].twist > 2 * PI)
			asteroids[i].twist = 0;
		
		if (asteroids[i].twist <  0)
			asteroids[i].twist = 2 * PI;
	
		asteroids[i].sx += asteroids[i].speed * cos(asteroids[i].heading);
		asteroids[i].sy += asteroids[i].speed * sin(asteroids[i].heading);
		
		teleport(&asteroids[i].sx, &asteroids[i].sy);
	}
}

/*
 * if an asteroid is hit by a blast from the spaceship's cannon
 * it immediately splits into two
 * Each of these parts will be half the size of the original asteroid.
 * Once an asteroid has been split 2 times, it's gone.
 * The player score increases by 100 with each hit
 *
 * Use linked lists for sets of asteroid
 * or arrays
*/