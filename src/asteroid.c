#ifndef ASTEROID_
#define ASTEROID_
#include "../include/blasteroids.h"
#endif

extern Asteroid *asteroids;
extern Spaceship ship;
extern ALLEGRO_EVENT_QUEUE *queue;
extern ALLEGRO_EVENT event;
extern ALLEGRO_DISPLAY *disp;
ALLEGRO_TIMER* asteroid_rotation_timer;
ALLEGRO_BITMAP *AsteroidBitmap;

void draw_asteroid()
{
		int BitmapScale = 50;

		//Asteroid bitmap
		AsteroidBitmap = al_create_bitmap(BitmapScale, BitmapScale);
		int xoffset = BitmapScale / 2, yoffset = BitmapScale / 2;
		al_set_target_bitmap(AsteroidBitmap);

		// al_clear_to_color(al_map_rgba_f(.9, 0, 0, .5)); //Testing

		al_draw_line(-20 + xoffset, 20  + yoffset, -25 + xoffset, 5   + yoffset, al_map_rgb(255,255,255), 2.0f);
		al_draw_line(-25 + xoffset, 5   + yoffset, -25 + xoffset, -10 + yoffset, al_map_rgb(255,255,255), 2.0f);
		al_draw_line(-25 + xoffset, -10 + yoffset, -5  + xoffset, -10 + yoffset, al_map_rgb(255,255,255), 2.0f);
		al_draw_line(-5  + xoffset, -10 + yoffset, -10 + xoffset, -20 + yoffset,al_map_rgb(255,255,255), 2.0f);
		al_draw_line(-10 + xoffset, -20 + yoffset, 5   + xoffset, -20 + yoffset, al_map_rgb(255,255,255), 2.0f);
		al_draw_line(5   + xoffset, -20 + yoffset, 20  + xoffset, -10 + yoffset, al_map_rgb(255,255,255), 2.0f);
		al_draw_line(20  + xoffset, -10 + yoffset, 20  + xoffset, -5  + yoffset, al_map_rgb(255,255,255), 2.0f);
		al_draw_line(20  + xoffset, -5  + yoffset, 0   + xoffset, 0   + yoffset,al_map_rgb(255,255,255), 2.0f);
		al_draw_line(0   + xoffset, 0   + yoffset, 20  + xoffset, 10  + yoffset, al_map_rgb(255,255,255), 2.0f);
		al_draw_line(20  + xoffset, 10  + yoffset, 10  + xoffset, 20  + yoffset, al_map_rgb(255,255,255), 2.0f);
		al_draw_line(10  + xoffset, 20  + yoffset, 0   + xoffset, 15  + yoffset, al_map_rgb(255,255,255), 2.0f);
		al_draw_line(0   + xoffset, 15  + yoffset, -20 + xoffset, 20  + yoffset, al_map_rgb(255,255,255), 2.0f);

		al_set_target_bitmap(al_get_backbuffer(disp));
	
	for (size_t i = 0; i < MAX_BIG_ASTEROIDS; i++)
	{
		
		asteroids[i].image = AsteroidBitmap;

		if (!asteroids[i].gone)
		{
			ALLEGRO_TRANSFORM transform; 
			al_identity_transform(&transform);
			al_rotate_transform(&transform, asteroids[i].twist); //We rotate it
			al_translate_transform(&transform,asteroids[i].sy, asteroids[i].sx); //We move it to an initial position
			al_use_transform(&transform);
			al_draw_tinted_bitmap(asteroids[i].image, asteroids[i].color, -(BitmapScale/2), -(BitmapScale/2), 0);
		}
	}

	update_asteroid();	
}

void spawn_asteroid()
{
	int x_initial = rand() * rand() % DISPLAY_WIDTH;
	int y_initial = rand() * rand() % DISPLAY_HEIGHT;

	float heading_initial = (rand() % (int)(2 * PI));
	float twist_initial = (rand() % (int)(2 * PI));
	float speed_initial = rand() % 2 + 1;
	float rot_velocity_initial = rand() % 10;
	float scale_initial = rand() % 4 + 1;

	for (size_t i = 0; i < MAX_BIG_ASTEROIDS; i++)
	{
		
		if (asteroids[i].gone) //If it is true then
		{
			asteroids[i].sx = x_initial;
			asteroids[i].sy = y_initial;
			asteroids[i].heading = heading_initial;
			asteroids[i].twist = twist_initial;
			asteroids[i].speed = speed_initial;
			asteroids[i].rot_velocity = rot_velocity_initial;
			asteroids[i].scale = scale_initial;
			asteroids[i].gone = false; // It turns it to false 
			asteroids[i].color = al_map_rgba_f(0.211, 0.368, 0.639, 1);
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