#ifndef SHIP_
#define SHIP_
#include "../include/blasteroids.h"
#endif

extern Global *global;

void draw_ship()
{
		int xoffset = global->ship.BitmapScale * global->ship.scale / 2 , yoffset = global->ship.BitmapScale * global->ship.scale / 2; // Half the Bitmap scale * ship scale

	if(global->SpaceShipBitmapCreated == false)
	{
		float thickness = 2.5f; // just a variable to control the thickness in case we wanna vary it;
		thickness += global->ship.scale - 1;
		global->ship.image = al_create_bitmap(global->ship.BitmapScale * global->ship.scale, global->ship.BitmapScale * global->ship.scale);
 	   	al_set_target_bitmap(global->ship.image);
	 	al_draw_line(-8 * global->ship.scale + xoffset, 10 * global->ship.scale + yoffset, 0 * global->ship.scale + xoffset, -10 * global->ship.scale + yoffset, global->ship.color, thickness ); //We draw the lines
		al_draw_line(0 * global->ship.scale  + xoffset, -10 * global->ship.scale + yoffset, 8 * global->ship.scale + xoffset, 10 * global->ship.scale + yoffset, global->ship.color, thickness);  //We draw the lines
		al_draw_line(-6 * global->ship.scale + xoffset, 4 * global->ship.scale + yoffset, -1 * global->ship.scale + xoffset, 4 * global->ship.scale + yoffset, global->ship.color, thickness); //We draw the lines
		al_draw_line(6 * global->ship.scale  + xoffset, 4 * global->ship.scale + yoffset, 1 * global->ship.scale + xoffset, 4 * global->ship.scale + yoffset, global->ship.color, thickness); //We draw the lines
		
		printf("Ship Bitmap created\n");
		global->SpaceShipBitmapCreated = true;
	}

	al_identity_transform(&global->ship.transform);
	al_rotate_transform(&global->ship.transform, global->ship.heading + PI / 2); //We rotate it
	al_translate_transform(&global->ship.transform, global->ship.sx, global->ship.sy); //We move the transform to where the ship should be
	al_use_transform(&global->ship.transform);
	al_draw_bitmap(
		global->ship.image,
		global->ship.scale * -10,
		global->ship.scale * -10,
		0);
	teleport();
}

void draw_flame() //Draws the flame when it goes forward
{
	int xoffset = global->ship.BitmapScale * global->ship.scale / 2 , yoffset = global->ship.BitmapScale * global->ship.scale / 2; // Half the Bitmap scale * ship scale
	float thickness = 2.5f; // just a variable to control the thickness in case we wanna vary it;
	thickness += global->ship.scale - 1;
	al_identity_transform(&global->ship.transform);
	al_rotate_transform(&global->ship.transform, global->ship.heading + PI / 2); //We rotate it
	al_translate_transform(&global->ship.transform, global->ship.sx, global->ship.sy); //We move it to an initial position
	al_use_transform(&global->ship.transform);
	al_draw_line(0, 25 * global->ship.scale, 5 * global->ship.scale, 10 * global->ship.scale, al_map_rgb(222,  136,  44),  thickness); //We draw the lines
	al_draw_line(0, 25 * global->ship.scale, -5 * global->ship.scale, 10 * global->ship.scale, al_map_rgb(222,  136,  44),  thickness); //We draw the lines
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

			case ALLEGRO_KEY_M:
				global->Keys[M] = true;
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

			case ALLEGRO_KEY_M:
				global->Keys[M] = false;
				break;
			}
		}

}

void UseKeysForSpaceship() //uses the booleans from ReadKeysForSpaceglobal->ship to perform certain actions
{																						//This way we get smooth movement, sliding, etc
	if (global->Keys[SPACE])
		fire_bullet();

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

	if (global->Keys[M])
	{
	al_use_transform(&global->ship.transform);
	al_draw_bitmap(
		global->ship.mask->bmp, 
		-global->ship.mask->h,
		-global->ship.mask->w,
		0);
	}

	// Keeping the heading angle between 0 and 2*PI
	if (global->ship.heading > 2*PI)
		global->ship.heading = 0;

	else if (global->ship.heading < 0)
		global->ship.heading = 2*PI;

	//Drift of the ship
	global->ship.sx += global->ship.speed * cos(global->ship.drift);
	global->ship.sy += global->ship.speed * sin(global->ship.drift);

	// ship decelaration due to "drag"
	global->ship.speed = global->ship.speed > 0 ? global->ship.speed - DRAG : 0;
	if(global->ship.speed > SPACESHIP_SPEED_MAX) //Not exceeding max speed
		global->ship.speed = SPACESHIP_SPEED_MAX;
}

void Create_Ship_Mask()
{
	//Creates mask and transform for ship
	global->ship.mask = Mask_New(global->ship.image);
	global->ship.mask->tranform = &global->ship.transform;
	global->ship.mask->BitmapScale = global->ship.BitmapScale;
	Mask_Draw(global->ship.mask, al_get_bitmap_height(global->ship.image), al_get_bitmap_width(global->ship.image));
	printf("Ship Mask created\n");
}

/* Collisions
 * If the spaceglobal->ship collides with a rock, it dies immediately and the player
 * loses a life. For the first 5 seconds after a new global->ship is created, it
 * doesn't check for collisions. The new global->ship should appear in the center of
 * the screen
 */