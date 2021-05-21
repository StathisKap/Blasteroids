#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#ifndef HEADER_
#define HEADER_
#include "../include/blasteroids_header.h"
#endif

void error(char *msg);

int main()
{
	if (!al_init())
		error("Couldn't initialize Allegro");

	if (!al_install_keyboard())
		error("Couldn't initialize Keyboard");


	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); //FPS
	if (!time)
		error("Couldn't initialize Timer");

	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue(); //Create event queue to catch keystrokes
	if (!queue)
		error("Couldn't initialize Queue");

	ALLEGRO_DISPLAY* disp = al_create_display(520, 500);
	if (!disp)
		error("Couldn't initialize Display");

	ALLEGRO_FONT* font = al_create_builtin_font();
	if (!font)
		error("Couldn't initialize Font");

	Spaceship ship = {250, 250, 0, 0, 0, al_map_rgb(255,255,0)};

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool redraw = true;
	bool Key_Down = false;
    ALLEGRO_EVENT event;

    al_start_timer(timer);	
	while(1)
	{
		// Key_Down = false;
		al_wait_for_event(queue, &event); //Capture keystrokes

        if(event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {  //If you detect any key stroke
			// Key_Down = true;
			switch(event.keyboard.keycode) { //Do something with them
			case ALLEGRO_KEY_LEFT:
				ship.heading -= ROT_SPEED;
				break;
			case ALLEGRO_KEY_RIGHT:
				ship.heading += ROT_SPEED;
				break;
			case ALLEGRO_KEY_SPACE:
				break;
			}
		}

		if(redraw && al_is_event_queue_empty(queue))
		{
		    al_clear_to_color(al_map_rgb(0, 0, 0));
			draw_ship(&ship);
			al_flip_display();
    		redraw = false;
		}
	}
	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}

/* Read keypresses like this
 *
 *
 * You need to display the number of lives, and score on the screen
 * When you run out of lives you need to display "Game Over!"
 * in big friendly letters in the middle of the screen.
 *
 *

*/

void error(char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}