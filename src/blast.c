#ifndef	BLAST_
#define BLAST_
#include "../include/blasteroids.h"
#endif

extern Global * global;

void spawn_bullet()
{
	for (size_t i = 0; i < BULLET_COUNT; i++) //goes through each bullet
	{
		if (!global->bullets[i].live) //If it is false then
		{
			global->bullets[i].live = true; // It turns it to true
			global->bullets[i].heading = global->ship.heading; // It sets the heading equal to wherever the ship was looking
			global->bullets[i].sx = global->ship.sx + 10 * sin(global->ship.heading + PI / 2) * global->ship.scale; // It sets the starting position to where the ship is
			global->bullets[i].sy = global->ship.sy - 10 * cos(global->ship.heading  + PI / 2) * global->ship.scale;
			global->bullets[i].size = 5;
			break;
		}
	}
}

void fire_bullet()
{
	if (!al_get_timer_started(global->fire_rate_timer))
	{
  	al_start_timer(global->fire_rate_timer);
		spawn_bullet();
	}

	if (global->event.type == ALLEGRO_EVENT_TIMER)
		if (global->event.timer.source == global->fire_rate_timer)
			spawn_bullet();
}

void draw_bullet()
{
	for (size_t i = 0; i < BULLET_COUNT; i++)
	{
		if (global->bullets[i].live)
		{
			al_identity_transform(&global->bullets[i].transform);
			al_use_transform(&global->bullets[i].transform);
			al_draw_filled_circle(global->bullets[i].sx, global->bullets[i].sy, global->bullets[i].size, al_map_rgb(255,0,0)); // Draws a red dot
		}
	}
	update_bullet();
}

void update_bullet()
{
	for (size_t i = 0; i < BULLET_COUNT; i++)
	{
		if (global->bullets[i].live)
		{
			global->bullets[i].sx += BULLET_SPEED * cos(global->bullets[i].heading);
			global->bullets[i].sy += BULLET_SPEED * sin(global->bullets[i].heading);

			if (global->bullets[i].sx < 0)
				global->bullets[i].live = false;
			if (global->bullets[i].sx > DISPLAY_WIDTH)
				global->bullets[i].live = false;
			if (global->bullets[i].sy < 0)
				global->bullets[i].live = false;
			if (global->bullets[i].sy > DISPLAY_HEIGHT)
				global->bullets[i].live = false;
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
