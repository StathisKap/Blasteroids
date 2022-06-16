#ifndef SHIP_
#define SHIP_
#include "../include/blasteroids.h"
#endif

extern Global *global;

void draw_ship()
{
	int BitmapScale = 20;
	float thickness = 2.5f; // just a variable to control the thickness in case we wanna vary it;
	int xoffset = BitmapScale * global->ship.scale / 2 , yoffset = BitmapScale * global->ship.scale / 2;

	if(global->SpaceShipBitmapCreated == false)
	{
		global->ship.image = al_create_bitmap(BitmapScale*global->ship.scale,BitmapScale*global->ship.scale);
 	   	al_set_target_bitmap(global->ship.image);
	 	al_draw_line(-8*global->ship.scale + xoffset, 9*global->ship.scale + yoffset, 0*global->ship.scale + xoffset, -11*global->ship.scale + yoffset, global->ship.color, thickness ); //We draw the lines
		al_draw_line(0*global->ship.scale  + xoffset, -11*global->ship.scale + yoffset, 8*global->ship.scale + xoffset, 9*global->ship.scale + yoffset, global->ship.color, thickness);  //We draw the lines
		al_draw_line(-6*global->ship.scale + xoffset, 4*global->ship.scale + yoffset, -1*global->ship.scale + xoffset, 4*global->ship.scale + yoffset, global->ship.color, thickness); //We draw the lines
		al_draw_line(6*global->ship.scale  + xoffset, 4*global->ship.scale + yoffset, 1*global->ship.scale + xoffset, 4*global->ship.scale + yoffset, global->ship.color, thickness); //We draw the lines
		al_set_target_bitmap(al_get_backbuffer(global->disp));
		global->SpaceShipBitmapCreated = true;
	}

	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, global->ship.heading + PI / 2); //We rotate it
	al_translate_transform(&transform, global->ship.sx, global->ship.sy); //We move it to an initial position
	al_use_transform(&transform);
	al_draw_bitmap(global->ship.image,BitmapScale*global->ship.scale/2 - BitmapScale, BitmapScale*global->ship.scale/2 - BitmapScale, 0);
	teleport(&global->ship.sx, &global->ship.sy);
}

void draw_flame() //Draws the flame when it goes forward
{
	float thickness = 2.5f; // just a variable to control the thickness in case we wanna vary it;
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, global->ship.heading + PI / 2); //We rotate it
	al_translate_transform(&transform, global->ship.sx, global->ship.sy); //We move it to an initial position
	al_use_transform(&transform);
	al_draw_line(6*global->ship.scale, 4*global->ship.scale, -1*global->ship.scale, 20*global->ship.scale, al_map_rgb(222, 136, 44), thickness); //We draw the lines
	al_draw_line(-6*global->ship.scale, 4*global->ship.scale, 1*global->ship.scale, 20*global->ship.scale, al_map_rgb(222, 136, 44), thickness); //We draw the lines
}

void ReadKeysForSpaceship()
{
		if (global->event.type == ALLEGRO_EVENT_KEY_DOWN ) {  //If you detect any key stroke
			switch(global->event.keyboard.keycode) { //Do something with them

			case ALLEGRO_KEY_UP:
				global->Keys[UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				global->Keys[DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				global->Keys[LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				global->Keys[RIGHT] = true;
				break;

			case ALLEGRO_KEY_SPACE:
				global->Keys[SPACE] = true;
				break;
			}
		}
		else if (global->event.type == ALLEGRO_EVENT_KEY_UP){ //If a key is released
			switch(global->event.keyboard.keycode) { //Do something with them

			case ALLEGRO_KEY_UP:
				global->Keys[UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				global->Keys[DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				global->Keys[LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				global->Keys[RIGHT] = false;
				break;

			case ALLEGRO_KEY_SPACE:
				global->Keys[SPACE] = false;
				break;

			}
		}

}

void UseKeysForSpaceship() //uses the booleans from ReadKeysForSpaceglobal->ship to perform certain actions
{																						//This way we get smooth movement, sliding, etc
	if (global->Keys[SPACE])
	{
		fire_bullet();
	}
	if (global->Keys[LEFT])
		global->ship.heading -= ROT_SPEED;
	if (global->Keys[RIGHT])
		global->ship.heading += ROT_SPEED;
	if (global->Keys[UP]){
		global->ship.speed += SPACESHIP_SPEED;
		global->ship.drift = global->ship.heading;
		draw_flame();
	}
	if (global->Keys[DOWN])
		global->ship.speed -= DRAG * 10;

	if (global->ship.heading > 2*PI)
		global->ship.heading = 0;
	else if (global->ship.heading < 0)
		global->ship.heading = 2*PI;

	//Drift of the global->ship
	global->ship.sx += global->ship.speed * cos(global->ship.drift);
	global->ship.sy += global->ship.speed * sin(global->ship.drift);

	// global->ship decelaration due to "drag"
	global->ship.speed = global->ship.speed > 0 ? global->ship.speed - DRAG : 0;
	if(global->ship.speed > SPACESHIP_SPEED_MAX) //Not exceeding max speed
		global->ship.speed = SPACESHIP_SPEED_MAX;
}

/* Collisions
 * If the spaceglobal->ship collides with a rock, it dies immediately and the player
 * loses a life. For the first 5 seconds after a new global->ship is created, it
 * doesn't check for collisions. The new global->ship should appear in the center of
 * the screen
 */
