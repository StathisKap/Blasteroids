#ifndef BLASTEROIDS_
#define BLASTEROIDS_
#include "../include/blasteroids.h"
#endif

Global *global;

int main()
{
	LOG(1, "Start of the program\n");

	global = malloc(sizeof(Global));
	DEBUG_ASTEROIDS_ALIVE(Blasteroids_Init(global));

	short wave = 0;

	while (!global->done)
	{
		al_wait_for_event(global->queue, &global->event); // Capture keystrokes

		// if the timer has ticked, redraw
		if (global->event.type == ALLEGRO_EVENT_TIMER)
			global->redraw = true;
		// if the user has pressed ESC or clicked the x on the window. Then close
		else if (global->event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || global->event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			global->done = true;

		if (global->redraw && al_is_event_queue_empty(global->queue))
		{
			draw_ship();
			draw_bullet();
			DEBUG_ASTEROIDS_ALIVE(draw_asteroid());
			draw_lives();
			draw_score();

			DEBUG_ASTEROIDS_ALIVE(spawn_asteroid());

			if (global->asteroids_alive < 0)
			{
				LOG(1, "Asteroids Alive is negative %d\n", global->asteroids_alive);
				return 0;
			}

			if (global->done)
			{
				al_draw_text(global->font, al_map_rgb(255, 255, 255),
							 DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2,
							 ALLEGRO_ALIGN_CENTER, "GAME OVER!!");
				al_flip_display();
				al_rest(3);
				break;
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			global->redraw = false;
		}

		KeysForSpaceship();
		DEBUG_ASTEROIDS_ALIVE(Box_Collision_Bullets());

		if (!al_get_timer_started(global->respawn_timer) && global->ship.live)
			Box_Collision_Ship();
	}

	if (!al_destroy_all())
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
	al_destroy_timer(global->asteroid_rotation_timer);
	al_destroy_timer(global->fire_rate_timer);
	al_destroy_event_queue(global->queue);
	al_destroy_bitmap(global->AsteroidBitmap);
	al_destroy_font(global->font);
	al_destroy_sample(global->shoot_sound);
	al_destroy_sample(global->explosion_sound);
	al_destroy_sample(global->lifeup_sound);
	free(global->bullets);
	free(global->asteroids);
	free(global);
	LOG(1, "Freed Everything\n");
	return 1;
}

int al_register_all()
{
	al_register_event_source(global->queue, al_get_keyboard_event_source());
	al_register_event_source(global->queue, al_get_display_event_source(global->disp));
	al_register_event_source(global->queue, al_get_timer_event_source(global->timer));
	al_register_event_source(global->queue, al_get_timer_event_source(global->asteroid_rotation_timer));
	al_register_event_source(global->queue, al_get_timer_event_source(global->fire_rate_timer));
	LOG(1, "Registerd Everything");
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

void Blasteroids_Init(Global *global)
{
	srand(0);
	setlocale(LC_NUMERIC, "");


	// Initializing variables that are on the heap or are from other source files
	global->Player_Lives = 3;
	global->score = 0;
	global->bullets = malloc(sizeof(Bullet) * BULLET_COUNT);
	global->asteroids_alive = 0;
	global->asteroids_max_count = MAX_BIG_ASTEROIDS;
	global->asteroids = malloc(sizeof(Asteroid) * global->asteroids_max_count * 2);
	global->redraw = true;
	global->done = false;
	global->AsteroidBitmap = NULL;
	global->ship = (Spaceship){
		DISPLAY_HEIGHT / 2,		 //	sx
		DISPLAY_WIDTH / 2,		 // sy
		3 * PI / 2,				 // heading
		0,						 // speed
		0,						 // drift
		2,						 // scale
		true,					 // live
		al_map_rgb(255, 255, 0), // color
		NULL,					 // image
	};

	for (int i = 0; i < global->asteroids_max_count * 2; i++)
		global->asteroids[i].dead = true;
	for (short i = 0; i < global->asteroids_max_count * 2; i++)
		LOG(1, "Asteroid %d is %s", i, global->asteroids[i].dead ? "Dead" : "Alive");

	if (!al_init())
		error("Couldn't initialize Allegro");

	if (!al_init_primitives_addon())
		error("Couldn't initialize Allegro Primitives");

	if (!al_init_font_addon())
		error("Couldn't initialize Allegro Font");

	if (!al_init_ttf_addon())
		error("Couldn't initialize Allegro TTF");

	if (!al_install_audio()) 
		error("Couldn't initialize Allegro Audio");

	if (!al_init_acodec_addon()) 
		error("Couldn't initialize Allegro Acodec");

	if (!al_reserve_samples(1))
		error("Couldn't initialize Allegro Audio Reverse");


	global->font = al_load_ttf_font("./assets/arial.ttf", 40, 0);
	if (!global->font)
		error("Couldn't Load TTF");

	if(!al_reserve_samples(100))
		error("Couldn't resever audio samples");

	global->shoot_sound = al_load_sample("./assets/Laser_Shoot.wav");
	if (!global->shoot_sound)
		error("Couldn't load Shoot Sound");

	global->explosion_sound = al_load_sample("./assets/Explosion.wav");
	if (!global->explosion_sound)
		error("Couldn't Load Explosion Sound");

	global->flame_sound= al_load_sample("./assets/Flame.wav");
	if (!global->flame_sound)
		error("Couldn't Load Flame Sound");

	global->lifeup_sound = al_load_sample("./assets/Life_Up.wav");
	if (!global->lifeup_sound)
		error("Couldn't Load Life Up Sound");

	if (!al_install_keyboard())
		error("Couldn't initialize Keyboard");

	global->timer = al_create_timer(1.0 / 60.0); // FPS
	if (!global->timer)
		error("Couldn't initialize Timer");

	global->asteroid_rotation_timer = al_create_timer(1.0 / 15);
	if (!global->asteroid_rotation_timer)
		error("Couldn't initialize Asteroid Rotation Timer");

	global->fire_rate_timer = al_create_timer(1.0 / 2);
	if (!global->fire_rate_timer)
		error("Couldn't initialize Fire Rate Timer");

	global->respawn_timer = al_create_timer(1.0 / 10);
	if (!global->respawn_timer)
		error("Couldn't initialize Respawn Timer");

	global->queue = al_create_event_queue(); // Create event queue to catch keystrokes
	if (!global->queue)
		error("Couldn't initialize Queue");

	global->disp = al_create_display(DISPLAY_HEIGHT, DISPLAY_WIDTH); // Creates a window
	if (!global->disp)
		error("Couldn't initialize Display");

	if (!al_register_all())
		error("Coulnd't register something");

	al_start_timer(global->timer);
	al_start_timer(global->fire_rate_timer);
	al_start_timer(global->asteroid_rotation_timer);

	al_set_window_title(global->disp, "Blasteroids");

	LOG(1, "Global Variables initialised");

	draw_ship();
}


void draw_score()
{
	al_draw_textf(global->font, al_map_rgb(0, 255, 0),
				 DISPLAY_WIDTH / 2, 50,
				 ALLEGRO_ALIGN_CENTER, "Score: %'u", global->score);
}