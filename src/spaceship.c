#ifndef HEADER_
#define HEADER_
#include "../include/blasteroids_header.h"
#endif

bool init = false;

void draw_ship(Spaceship* s)
{
	float thickness = 2.5f;
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, s->heading + PI / 2);
	al_translate_transform(&transform, s->sx, s->sy);
	al_use_transform(&transform);
	al_draw_line(-8*s->scale, 9*s->scale, 0*s->scale, -11*s->scale, s->color, thickness );
	al_draw_line(0*s->scale, -11*s->scale, 8*s->scale, 9*s->scale, s->color, thickness);
	al_draw_line(-6*s->scale, 4*s->scale, -1*s->scale, 4*s->scale, s->color, thickness);
	al_draw_line(6*s->scale, 4*s->scale, 1*s->scale, 4*s->scale, s->color, thickness);
}
void ReadKeysForSpaceship(ALLEGRO_EVENT *Ev, bool Keys[SPACESHIP_KEYS_NUM])
{
		if (Ev->type == ALLEGRO_EVENT_KEY_DOWN ) {  //If you detect any key stroke
			switch(Ev->keyboard.keycode) { //Do something with them

			case ALLEGRO_KEY_UP:
				Keys[UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				Keys[DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				Keys[LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				Keys[RIGHT] = true;
				break;

			case ALLEGRO_KEY_SPACE:
				Keys[SPACE] = true;
				break;
		
			}
		}
		else if (Ev->type == ALLEGRO_EVENT_KEY_UP){ //If a key is released
			switch(Ev->keyboard.keycode) { //Do something with them

			case ALLEGRO_KEY_UP:
				Keys[UP] = false;
				break;
			
			case ALLEGRO_KEY_DOWN:
				Keys[DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				Keys[LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				Keys[RIGHT] = false;
				break;

			case ALLEGRO_KEY_SPACE:
				Keys[SPACE] = false;
				break;
		
			}
		}

}

void UseKeysForSpaceship(Spaceship *s, bool Keys[SPACESHIP_KEYS_NUM], Bullet bullets[])
{	
	if (Keys[SPACE])
	{
		fire_bullet(bullets,s);
	}		
	if (Keys[LEFT])
		s->heading -= ROT_SPEED;
	if (Keys[RIGHT])
		s->heading += ROT_SPEED;
	if (Keys[UP]){
		s->speed += SPACESHIP_SPEED;
		s->drift = s->heading;
	}
	if (Keys[DOWN])
		s->speed -= DRAG * 10;

	if (s->heading > 2*PI)
		s->heading = 0;
	else if (s->heading < 0) 
		s->heading = 2*PI;

	if (!init)
	{
		init = true;
	}

	s->sx += s->speed * cos(s->drift);
	s->sy += s->speed * sin(s->drift);

	s->speed = s->speed > 0 ? s->speed - DRAG : 0;
	if(s->speed > SPACESHIP_SPEED_MAX)
		s->speed = SPACESHIP_SPEED_MAX;
	// printf("speed:%f\tdrift:%f\theading:%f\tsx:%f\tsy:%f\t\n",s->speed, s->drift, s->heading, s->sx, s->sy);
}

void init_bullet(Bullet bullets[])
{
	for (size_t i = 0; i < BULLET_COUNT; i++)
	{
		bullets[i].live = false;
	}
	
}

void fire_bullet(Bullet bullets[], Spaceship *s)
{
	for (size_t i = 0; i < BULLET_COUNT; i++)
	{
		if (!bullets[i].live)
		{
			bullets[i].live = true;
			bullets[i].heading = s->heading;
			bullets[i].sx = s->sx;
			bullets[i].sy = s->sy;
			printf("%ld:\tBh %.3f Sh %.3f Bx %.3f Sx %.3f\n",i,bullets[i].heading,s->heading,bullets[i].sx, s->sx);
			break;
		}
		
	}
	
}

void draw_bullet(Bullet bullets[])
{
	for (size_t i = 0; i < BULLET_COUNT; i++)
	{
		if (bullets[i].live)
		{
			al_draw_filled_circle(bullets[i].sx, bullets[i].sy, 2, al_map_rgb(255,0,0));
		}
		
	}
	
}

void update_bullet(Bullet bullets[])
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
/* Spaceship behaviour
 * The spaceship starts stationary in the center of the screen.
 * "Up" goes forward. "Right" and "Left" rotate. "Space" fires
 */

/* Collisions
 * If the spaceship collides with a rock, it dies immediately and the player
 * loses a life. For the first 5 seconds after a new ship is created, it
 * doesn't check for collisions. The new ship should appear in the center of
 * the screen
 */

