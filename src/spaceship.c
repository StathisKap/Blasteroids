#ifndef SHIP_
#define SHIP_
#include "../include/blasteroids.h"
#endif

bool init = false;
extern Bullet *bullets;
extern bool *Keys;
extern Spaceship ship;

void draw_ship(Spaceship* s)
{
	float thickness = 2.5f; // just a variable to control the thickness in case we wanna vary it;
	ALLEGRO_TRANSFORM transform; 
	al_identity_transform(&transform);
	al_rotate_transform(&transform, s->heading + PI / 2); //We rotate it
	al_translate_transform(&transform, s->sx, s->sy); //We move it to an initial position
	al_use_transform(&transform);
	al_draw_line(-8*s->scale, 9*s->scale, 0*s->scale, -11*s->scale, s->color, thickness ); //We draw the lines
	al_draw_line(0*s->scale, -11*s->scale, 8*s->scale, 9*s->scale, s->color, thickness);  //We draw the lines
	al_draw_line(-6*s->scale, 4*s->scale, -1*s->scale, 4*s->scale, s->color, thickness); //We draw the lines
	al_draw_line(6*s->scale, 4*s->scale, 1*s->scale, 4*s->scale, s->color, thickness); //We draw the lines
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
//			case ALLEGRO_KEY_A:
//				fire_asteroid();
//				break;
		
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

/* Collisions
 * If the spaceship collides with a rock, it dies immediately and the player
 * loses a life. For the first 5 seconds after a new ship is created, it
 * doesn't check for collisions. The new ship should appear in the center of
 * the screen
 */

