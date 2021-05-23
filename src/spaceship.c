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

void UseKeysForSpaceship(Spaceship *s, bool Keys[SPACESHIP_KEYS_NUM])
{
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

	float Pos_Neg = (s->drift >= 0 && s->drift < PI ? SPACESHIP_SPEED : -SPACESHIP_SPEED);
	s->sx += s->speed * cos(s->drift); //: sin(s->drift); 
	s->sy += s->speed * sin(s->drift); //: cos(s->drift);

	s->speed = s->speed > 0 ? s->speed - DRAG : 0;
	if(s->speed > SPACESHIP_SPEED_MAX)
		s->speed = SPACESHIP_SPEED_MAX;
	printf("speed:%f\tdrift:%f\theading:%f\tsx:%f\tsy:%f\t\n",s->speed, s->drift, s->heading, s->sx, s->sy);
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

