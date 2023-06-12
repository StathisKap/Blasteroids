#ifndef SHIP_
#define SHIP_
#include "../include/blasteroids.h"
#endif

extern Global *global;

void draw_ship()
{
	int xoffset = 20 * global->ship.scale / 2 , yoffset = 20 * global->ship.scale / 2; // Half the Bitmap scale * ship scale

	if(global->SpaceShipBitmapCreated == false)
	{
		float thickness = 2.5f; // just a variable to control the thickness in case we wanna vary it;
		thickness += global->ship.scale - 1;
		global->ship.image = al_create_bitmap(20 * global->ship.scale, 20 * global->ship.scale);
 	  al_set_target_bitmap(global->ship.image);
	 	al_draw_line(-8 * global->ship.scale + xoffset, 10 * global->ship.scale + yoffset, 0 * global->ship.scale + xoffset, -10 * global->ship.scale + yoffset, global->ship.color, thickness ); //We draw the lines
		al_draw_line(0 * global->ship.scale  + xoffset, -10 * global->ship.scale + yoffset, 8 * global->ship.scale + xoffset, 10 * global->ship.scale + yoffset, global->ship.color, thickness);  //We draw the lines
		al_draw_line(-6 * global->ship.scale + xoffset, 4 * global->ship.scale + yoffset, -1 * global->ship.scale + xoffset, 4 * global->ship.scale + yoffset, global->ship.color, thickness); //We draw the lines
		al_draw_line(6 * global->ship.scale  + xoffset, 4 * global->ship.scale + yoffset, 1 * global->ship.scale + xoffset, 4 * global->ship.scale + yoffset, global->ship.color, thickness); //We draw the lines
		al_set_target_bitmap(al_get_backbuffer(global->disp));

		LOG(1, "Ship Bitmap created");
		global->SpaceShipBitmapCreated = true;
	}

	if (global->ship.live == true)
	{
		al_identity_transform(&global->ship.transform);
		al_rotate_transform(&global->ship.transform, global->ship.heading + PI / 2); //We rotate it
		al_translate_transform(&global->ship.transform, global->ship.sx, global->ship.sy); //We move the transform to where the ship should be
		al_use_transform(&global->ship.transform);
		al_draw_bitmap(global->ship.image,
			global->ship.scale * -10,
			global->ship.scale * -10, 0);
		teleport(&global->ship.sx, &global->ship.sy);
	}
	else
		respawn();
}

void draw_flame() //Draws the flame when it goes forward
{
	int xoffset = 20 * global->ship.scale / 2 , yoffset = 20 * global->ship.scale / 2; // Half the Bitmap scale * ship scale
	float thickness = 2.5f; // just a variable to control the thickness in case we wanna vary it;
	thickness += global->ship.scale - 1;
	al_identity_transform(&global->ship.transform);
	al_rotate_transform(&global->ship.transform, global->ship.heading + PI / 2); //We rotate it
	al_translate_transform(&global->ship.transform, global->ship.sx, global->ship.sy); //We move it to an initial position
	al_use_transform(&global->ship.transform);
	al_draw_line(0, 25 * global->ship.scale, 5 * global->ship.scale, 10 * global->ship.scale, al_map_rgb(222,  136,  44),  thickness); //We draw the lines
	al_draw_line(0, 25 * global->ship.scale, -5 * global->ship.scale, 10 * global->ship.scale, al_map_rgb(222,  136,  44),  thickness); //We draw the lines
	al_play_sample_instance(global->flame_instance);
}

void keys_for_spaceship()
{
	// create a keyboard keystate
	ALLEGRO_KEYBOARD_STATE keystate;
	// get the current state of the keyboard
	al_get_keyboard_state(&keystate);

	if (al_key_down(&keystate, ALLEGRO_KEY_SPACE))
		fire_bullet();

	if (al_key_down(&keystate, ALLEGRO_KEY_LEFT))
		global->ship.heading -= ROT_SPEED;

	if (al_key_down(&keystate, ALLEGRO_KEY_RIGHT))
		global->ship.heading += ROT_SPEED;

	if (al_key_down(&keystate, ALLEGRO_KEY_UP)){
		global->ship.speed += SPACESHIP_SPEED;
		global->ship.drift = global->ship.heading;
		draw_flame();
	}

	if (!al_key_down(&keystate, ALLEGRO_KEY_UP))
		al_stop_sample_instance(global->flame_instance);

	if (al_key_down(&keystate, ALLEGRO_KEY_DOWN))
		global->ship.speed -= DRAG * 10;

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

	if (global->event.type == ALLEGRO_EVENT_TIMER)
		if (!al_key_down(&keystate, ALLEGRO_KEY_SPACE))
			if (global->event.timer.source == global->fire_rate_timer)
			{
				al_stop_timer(global->fire_rate_timer);
			}
}


void respawn()
{
	if (global->Player_Lives <= 0)
	{
		global->done = true;
		return;
	}

	if (al_get_timer_count(global->respawn_timer) == 0)
	{
		global->ship.sx = DISPLAY_WIDTH / 2.0;
		global->ship.sy = DISPLAY_HEIGHT / 2.0;
		global->ship.heading = 3 * PI / 2;
		global->ship.speed = 0;
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	if(!al_get_timer_started(global->respawn_timer))
		al_start_timer(global->respawn_timer);

	if (al_get_timer_count(global->respawn_timer) % 5)
	{
		al_identity_transform(&global->ship.transform);
		al_rotate_transform(&global->ship.transform, global->ship.heading + PI / 2); //We rotate it
		al_translate_transform(&global->ship.transform, global->ship.sx, global->ship.sy);
		al_use_transform(&global->ship.transform);
		al_draw_tinted_bitmap(global->ship.image,
			al_map_rgba_f(0.5, 0.5, 0.5, 0.5),
			global->ship.scale * -10,
			global->ship.scale * -10, 0);
	}
	if (al_get_timer_count(global->respawn_timer) > 30)
	{
		global->ship.live = true;
		al_set_timer_count(global->respawn_timer, 0);
		al_stop_timer(global->respawn_timer);
	}
}

void life_up(int points) {
	static int previous_score = 0; // static variable to track previous score
	if (global->score >= previous_score + points) {
	    global->Player_Lives++; // increase player lives by 1
	    previous_score += points; // update previous score
			al_play_sample(global->lifeup_sound, 0.7, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}

void draw_lives()
{
		al_identity_transform(&global->ship.transform);
		al_use_transform(&global->ship.transform);
		for (short i = 0; i < global->Player_Lives; i++)
		{
			al_draw_tinted_scaled_bitmap(global->ship.image,
					al_map_rgba_f(0.2, 0.7, 0.2, 1.0),
					0,0,
					20 * global->ship.scale,
					20 * global->ship.scale,
					17 * global->ship.scale * i + 5, // the +5 is the shift from the left
					5, // Shift from the top
					15 * global->ship.scale,
					15 * global->ship.scale,
					0);
		}
}
