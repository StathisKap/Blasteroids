#ifndef	BLAST_ 
#define BLAST_
#include "../include/blasteroids.h"
#endif

extern Bullet *bullets;
extern Spaceship ship;

void fire_bullet()
{
	for (size_t i = 0; i < BULLET_COUNT; i++) //goes through each bullet
	{
		if (!bullets[i].live) //If it is false then
		{
			bullets[i].live = true; // It turns it to true
			bullets[i].heading = ship.heading; // It sets the heading equal to wherever the ship was looking
			bullets[i].sx = ship.sx; // It sets the starting position to where the ship is
			bullets[i].sy = ship.sy;
			break;
		}
		
	}
	
}

void draw_bullet()
{
	for (size_t i = 0; i < BULLET_COUNT; i++)
	{
		if (bullets[i].live)
		{
			ALLEGRO_TRANSFORM transform; 
			al_identity_transform(&transform);
			al_use_transform(&transform);
			al_draw_filled_circle(bullets[i].sx, bullets[i].sy, 2, al_map_rgb(255,0,0)); // Draws a red dot
		}
		
	}
	
}

void update_bullet()
{
	for (size_t i = 0; i < BULLET_COUNT; i++)
	{
		if (bullets[i].live)
		{
			bullets[i].sx += BULLET_SPEED * cos(bullets[i].heading);
			bullets[i].sy += BULLET_SPEED * sin(bullets[i].heading);
				
			if (bullets[i].sx < 0)
				bullets[i].live = false;
			if (bullets[i].sx > DISPLAY_WIDTH)
				bullets[i].live = false;
			if (bullets[i].sy < 0)
				bullets[i].live = false;
			if (bullets[i].sy > DISPLAY_HEIGHT)
				bullets[i].live = false;
			
			
		}
		
	}
	
}


/*
 * Unlike the other objects, blasts that disappear off the screen won't
 * reappear.
 * Blasts are always fired in the direction of the ship
 * They always travel in a straight line and constant speed
 * If a blast collides with an asteroid, the asteroid will divide into two
 */
