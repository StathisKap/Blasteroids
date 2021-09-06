#ifndef SHIP_
#define SHIP_
#include "../include/blasteroids.h"
#endif

extern Bullet *bullets;
extern bool *Keys;
extern Spaceship ship;
extern ALLEGRO_DISPLAY *disp;
bool SpaceShipBitmapCreated = false;

void draw_ship()
{
	int BitmapScale = 20;
	float thickness = 2.5f; // just a variable to control the thickness in case we wanna vary it;
	int xoffset = BitmapScale * ship.scale / 2 , yoffset = BitmapScale * ship.scale / 2;
	
	if(SpaceShipBitmapCreated == false)
	{
		ship.image = al_create_bitmap(BitmapScale*ship.scale,BitmapScale*ship.scale);
 	   	al_set_target_bitmap(ship.image);
	 	al_draw_line(-8*ship.scale + xoffset, 9*ship.scale + yoffset, 0*ship.scale + xoffset, -11*ship.scale + yoffset, ship.color, thickness ); //We draw the lines
		al_draw_line(0*ship.scale  + xoffset, -11*ship.scale + yoffset, 8*ship.scale + xoffset, 9*ship.scale + yoffset, ship.color, thickness);  //We draw the lines
		al_draw_line(-6*ship.scale + xoffset, 4*ship.scale + yoffset, -1*ship.scale + xoffset, 4*ship.scale + yoffset, ship.color, thickness); //We draw the lines
		al_draw_line(6*ship.scale  + xoffset, 4*ship.scale + yoffset, 1*ship.scale + xoffset, 4*ship.scale + yoffset, ship.color, thickness); //We draw the lines
		al_set_target_bitmap(al_get_backbuffer(disp));
		SpaceShipBitmapCreated = true;
	}

	ALLEGRO_TRANSFORM transform; 
	al_identity_transform(&transform);
	al_rotate_transform(&transform, ship.heading + PI / 2); //We rotate it
	al_translate_transform(&transform, ship.sx, ship.sy); //We move it to an initial position
	al_use_transform(&transform);
	al_draw_bitmap(ship.image,BitmapScale*ship.scale/2 - BitmapScale, BitmapScale*ship.scale/2 - BitmapScale, 0);
	teleport(&ship.sx, &ship.sy);
}

void draw_flame() //Draws the flame when it goes forward
{
	float thickness = 2.5f; // just a variable to control the thickness in case we wanna vary it;
	ALLEGRO_TRANSFORM transform; 
	al_identity_transform(&transform);
	al_rotate_transform(&transform, ship.heading + PI / 2); //We rotate it
	al_translate_transform(&transform, ship.sx, ship.sy); //We move it to an initial position
	al_use_transform(&transform);
	al_draw_line(6*ship.scale, 4*ship.scale, -1*ship.scale, 20*ship.scale, al_map_rgb(222, 136, 44), thickness); //We draw the lines
	al_draw_line(-6*ship.scale, 4*ship.scale, 1*ship.scale, 20*ship.scale, al_map_rgb(222, 136, 44), thickness); //We draw the lines
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
		draw_flame();
	}
	if (Keys[DOWN])
		ship.speed -= DRAG * 10;

	if (ship.heading > 2*PI)
		ship.heading = 0;
	else if (ship.heading < 0) 
		ship.heading = 2*PI;

	//Drift of the ship
	ship.sx += ship.speed * cos(ship.drift);
	ship.sy += ship.speed * sin(ship.drift);

	// Ship decelaration due to "drag"
	ship.speed = ship.speed > 0 ? ship.speed - DRAG : 0;
	if(ship.speed > SPACESHIP_SPEED_MAX) //Not exceeding max speed
		ship.speed = SPACESHIP_SPEED_MAX;
}
	
/* Collisions
 * If the spaceship collides with a rock, it dies immediately and the player
 * loses a life. For the first 5 seconds after a new ship is created, it
 * doesn't check for collisions. The new ship should appear in the center of
 * the screen
 */