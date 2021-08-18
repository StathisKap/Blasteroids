#ifndef HEADER_
#define HEADER_
#include "../include/blasteroids.h"
#endif

bool done = false;
Bullet *bullets;
bool *Keys;

int main()
{ 
	bullets = malloc(sizeof(Bullet)*BULLET_COUNT);
	Keys = malloc(sizeof(bool)*(SPACESHIP_KEYS_NUM));
	bool redraw = true;
	Spaceship ship = {DISPLAY_HEIGHT / 2, DISPLAY_WIDTH / 2, 0, 0, 0, 1, true, al_map_rgb(255,255,0)};
    ALLEGRO_EVENT event;

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

	ALLEGRO_DISPLAY* disp = al_create_display(DISPLAY_HEIGHT, DISPLAY_WIDTH); //Creates a window
	if (!disp)
		error("Couldn't initialize Display");

	if(!al_register_all(disp, timer, queue))
		error("Coulnd't register something");

    al_start_timer(timer);	
	while(!done)
	{
		al_wait_for_event(queue, &event); //Capture keystrokes

        if(event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			done = true; 

		ReadKeysForSpaceship(&event);
		UseKeysForSpaceship(&ship);
		

		if(redraw && al_is_event_queue_empty(queue))
		{
			draw_ship(&ship);
			draw_bullet(bullets);
			update_bullet(bullets);
			teleport(&ship.sx, &ship.sy);
			al_flip_display();
		    al_clear_to_color(al_map_rgb(0, 0, 0));
    		redraw = false;
		}
	}
		if(!al_destroy_all(disp,timer,queue))
			error("Couldn't destroy everything");
	return 0;
}

/* 
 * You need to display the number of lives, and score on the screen
 * When you run out of lives you need to display "Game Over!"
 * in big friendly letters in the middle of the screen.
 *
*/

void error(char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

int al_destroy_all(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer_event, ALLEGRO_EVENT_QUEUE *event_queue)
{
	al_destroy_display(display);
	al_destroy_timer(timer_event);
	al_destroy_event_queue(event_queue);
	free(bullets);
	free(Keys);
	return 1;
}

int al_register_all(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer_event, ALLEGRO_EVENT_QUEUE *event_queue)
{
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer_event));
	return 1;
}

void teleport(float *sx, float *sy)
{
	if (*sx > DISPLAY_WIDTH)
		*sx = 0;
	if (*sx < 0)
		*sx = DISPLAY_WIDTH;
	if (*sy > DISPLAY_HEIGHT)
		*sy = 0;
	if (*sy < 0)
		*sy = DISPLAY_HEIGHT;
}