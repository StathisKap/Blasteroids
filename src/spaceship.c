#ifndef SHIP_
#define SHIP_
#include "../include/blasteroids.h"
#endif

bool init = false;
extern Bullet *bullets;
extern bool *Keys;
extern Spaceship ship;

void draw_ship()
{
	float thickness = 2.5f; // just a variable to control the thickness in case we wanna vary it;
	ALLEGRO_TRANSFORM transform; 
	al_identity_transform(&transform);
	al_rotate_transform(&transform, ship.heading + PI / 2); //We rotate it
	al_translate_transform(&transform, ship.sx, ship.sy); //We move it to an initial position
	al_use_transform(&transform);
	al_draw_line(-8*ship.scale, 9*ship.scale, 0*ship.scale, -11*ship.scale, ship.color, thickness ); //We draw the lines
	al_draw_line(0*ship.scale, -11*ship.scale, 8*ship.scale, 9*ship.scale, ship.color, thickness);  //We draw the lines
	al_draw_line(-6*ship.scale, 4*ship.scale, -1*ship.scale, 4*ship.scale, ship.color, thickness); //We draw the lines
	al_draw_line(6*ship.scale, 4*ship.scale, 1*ship.scale, 4*ship.scale, ship.color, thickness); //We draw the lines
}
void ReadKeysForSpaceship(ALLEGRO_EVENT *Ev)
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
			case ALLEGRO_KEY_A:
				fire_asteroid();
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

void UseKeysForSpaceship() //uses the booleans from ReadKeysForSpaceship to perform certain actions
{																						//This way we get smooth movement, sliding, etc
	if (Keys[SPACE])
	{
		fire_bullet();
	}		
	if (Keys[LEFT])
		ship.heading -= ROT_SPEED;
	if (Keys[RIGHT])
		ship.heading += ROT_SPEED;
	if (Keys[UP]){
		ship.speed += SPACESHIP_SPEED;
		ship.drift = ship.heading;
	}
	if (Keys[DOWN])
		ship.speed -= DRAG * 10;

	if (ship.heading > 2*PI)
		ship.heading = 0;
	else if (ship.heading < 0) 
		ship.heading = 2*PI;

	if (!init)
	{
		init = true;
	}

	ship.sx += ship.speed * cos(ship.drift);
	ship.sy += ship.speed * sin(ship.drift);

	ship.speed = ship.speed > 0 ? ship.speed - DRAG : 0;
	if(ship.speed > SPACESHIP_SPEED_MAX)
		ship.speed = SPACESHIP_SPEED_MAX;
}
	
/* Collisions
 * If the spaceship collides with a rock, it dies immediately and the player
 * loses a life. For the first 5 seconds after a new ship is created, it
 * doesn't check for collisions. The new ship should appear in the center of
 * the screen
 */

