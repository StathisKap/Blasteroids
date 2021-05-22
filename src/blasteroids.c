#ifndef HEADER_
#define HEADER_
#include "../include/blasteroids_header.h"
#endif

void error(char *msg);
void ReadKeys(ALLEGRO_EVENT *Ev, bool Keys[4]);

int main()
{
	bool redraw = true;
	bool done = false;
	bool KeyIsDown[4] = {false};
	Spaceship ship = {250, 250, 0, 0, 0, 0, al_map_rgb(255,255,0)};
    ALLEGRO_EVENT event;
	ALLEGRO_KEYBOARD_STATE key_state;

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

	ALLEGRO_DISPLAY* disp = al_create_display(520, 500); //Creates a window
	if (!disp)
		error("Couldn't initialize Display");

	
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));


    al_start_timer(timer);	
	while(!done)
	{
		al_wait_for_event(queue, &event); //Capture keystrokes

        if(event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			done = true; 
        else if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			done = true; 


		ReadKeys(&event,KeyIsDown);

		// if (KeyIsDown[UP])
			// ship.heading -= ROT_SPEED;
		if (KeyIsDown[LEFT])
			ship.heading -= ROT_SPEED;
		else if (KeyIsDown[RIGHT])
			ship.heading += ROT_SPEED;
		// else if (KeyIsDown[SPACE])
			// ship.heading += ROT_SPEED;	

		if(redraw && al_is_event_queue_empty(queue))
		{
			draw_ship(&ship);
			al_flip_display();
		    al_clear_to_color(al_map_rgb(0, 0, 0));
    		redraw = false;
		}
	}
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

void ReadKeys(ALLEGRO_EVENT *Ev, bool Keys[4])
{
		if (Ev->type == ALLEGRO_EVENT_KEY_DOWN ) {  //If you detect any key stroke
			switch(Ev->keyboard.keycode) { //Do something with them

			case ALLEGRO_KEY_UP:
				Keys[UP] = true;
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