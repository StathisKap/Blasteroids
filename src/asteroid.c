#ifndef ASTEROID_
#define ASTEROID_
#include "../include/blasteroids.h"
#endif

extern Asteroid *asteroids;
extern Spaceship ship;

void draw_asteroid()
{
	for (size_t i = 0; i < MAX_BIG_ASTEROIDS; i++)
		asteroids[i] = (Asteroid){DISPLAY_HEIGHT / 2, DISPLAY_WIDTH / 2, 0, 0, 0, 0, 1, false, al_map_rgb(255,0,0)};
	 
	for (size_t i = 0; i < MAX_BIG_ASTEROIDS; i++)
	{
		if (!asteroids[i].gone)
		{
			ALLEGRO_TRANSFORM transform; 
			al_identity_transform(&transform);
			al_rotate_transform(&transform, 0); //We rotate it
			al_translate_transform(&transform,DISPLAY_HEIGHT / 2, DISPLAY_WIDTH / 2); //We move it to an initial position
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
	
}
void fire_asteroid()
{
	for (size_t i = 0; i < MAX_BIG_ASTEROIDS; i++)
	{
		if (!asteroids[i].gone) //If it is false then
		{
			asteroids[i].gone = true; // It turns it to true
			asteroids[i].heading = ship.heading; // It sets the heading equal to wherever the ship was looking
			asteroids[i].sx = ship.sx; // It sets the starting position to where the ship is
			asteroids[i].sy = ship.sy;
			break;
		}
		
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