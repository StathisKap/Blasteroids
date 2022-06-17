#ifndef BLASTEROIDS_
#define BLASTEROIDS_
#include "../include/blasteroids.h"
#endif

Global *global;

int main()
{
	printf("Start of the program\n");
	global = malloc(sizeof(Global));
	Blasteroids_Init(global);



	while(!global->done)
	{
		al_wait_for_event(global->queue, &global->event); //Capture keystrokes

        if(global->event.type == ALLEGRO_EVENT_TIMER)
            global->redraw = true;
        else if(global->event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || global->event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			global->done = true;

		ReadKeysForSpaceship();
		UseKeysForSpaceship();

		if(global->redraw && al_is_event_queue_empty(global->queue))
		{
			draw_ship();
			draw_bullet();
			draw_asteroid();
			spawn_asteroid();
			al_flip_display();
		    al_clear_to_color(al_map_rgb(0, 0, 0));
    		global->redraw = false;
		}
	}
		if(!al_destroy_all(global->disp, global->timer, global->queue))
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

int al_destroy_all()
{
	al_destroy_display(global->disp);
	al_destroy_timer(global->timer);
	al_destroy_event_queue(global->queue);
	free(global->bullets);
	free(global->Keys);
	return 1;
}

int al_register_all()
{
	al_register_event_source(global->queue, al_get_keyboard_event_source());
	al_register_event_source(global->queue, al_get_display_event_source(global->disp));
	al_register_event_source(global->queue, al_get_timer_event_source(global->timer));
	return 1;
}

void teleport()
{
	if (global->ship.sx > DISPLAY_WIDTH)
		global->ship.sx = 0;
	if (global->ship.sx < 0)
		global->ship.sx = DISPLAY_WIDTH;
	if (global->ship.sy > DISPLAY_HEIGHT)
		global->ship.sy = 0;
	if (global->ship.sy < 0)
		global->ship.sy = DISPLAY_HEIGHT;
}

void Blasteroids_Init(Global * global)
{
	// Initializing variables that are on the heap or are from other source files
	global->bullets = malloc(sizeof(Bullet)*BULLET_COUNT);
	global->asteroids = malloc(sizeof(Asteroid)*MAX_BIG_ASTEROIDS);
	global->Keys = malloc(sizeof(bool)*SPACESHIP_KEYS_NUM);
	global->redraw = true;
 	global->ship = (Spaceship){
		 DISPLAY_HEIGHT / 2,//	sx
		 DISPLAY_WIDTH / 2, // sy
		 0, 				// heading
		 0,					// speed 
		 0,					// drift
		 2,					// scale
		 20,				// Bitmapscale
		 true,				// live
		 al_map_rgb(255,255,0), //color
		 NULL, 				// image
		 NULL,				// mask
		 };
	srand(time(NULL));

	for(int i = 0 ; i < MAX_BIG_ASTEROIDS; i++)
		global->asteroids[i].gone = true;

	if (!al_init())
		error("Couldn't initialize Allegro");

	if (!al_init_primitives_addon())
		error("Couldn't initialize Allegro Primitives");

	if (!al_install_keyboard())
		error("Couldn't initialize Keyboard");

	global->timer = al_create_timer(1.0 / 60.0); //FPS
	if (!global->timer)
		error("Couldn't initialize Timer");

	global->asteroid_rotation_timer = al_create_timer(1.0/15);
	if (!global->asteroid_rotation_timer)
		error("Couldn't initialize Timer");

	global->queue = al_create_event_queue(); //Create event queue to catch keystrokes
	if (!global->queue)
		error("Couldn't initialize Queue");

	global->disp = al_create_display(DISPLAY_HEIGHT, DISPLAY_WIDTH); //Creates a window
	if (!global->disp)
		error("Couldn't initialize Display");

	if(!al_register_all())
		error("Coulnd't register something");

	al_register_event_source(global->queue, al_get_timer_event_source(global->asteroid_rotation_timer));

    al_start_timer(global->timer);
    al_start_timer(global->asteroid_rotation_timer);

	// Draw the ship once so that it creates a Bitmap for it
	draw_ship();
	Create_Ship_Mask();

	printf("Global Variables initialised\n");
}