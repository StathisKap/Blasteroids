#ifndef BLASTEROIDS_
#define BLASTEROIDS_
#include "../include/main.h"
#endif

extern Global *global;
extern GameState gameState;

int blasteroids()
{
	LOG(1, "Start of the Game\n");

	DEBUG_ASTEROIDS_ALIVE(blasteroids_init());

	LOG(1, "Start of the Game Loop\n");
	while (gameState == PLAY)
	{
		al_wait_for_event(global->queue, &global->event); // Capture keystrokes

		// if the timer has ticked, redraw
		if (global->event.type == ALLEGRO_EVENT_TIMER)
			global->redraw = true;
		// if the user has pressed ESC or clicked the x on the window. Then close
		else if (global->event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			global->done = true;
		else if (global->event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
			LOG(1, "ESC pressed. Setting GameState to MENU\n");
			gameState = MENU;
		}

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
							 DISPLAY_WIDTH / 2.0, DISPLAY_HEIGHT / 2.0,
							 ALLEGRO_ALIGN_CENTER, "GAME OVER!!");
				al_flip_display();
				al_rest(3);
				break;
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			global->redraw = false;
		}

		keys_for_spaceship();
		DEBUG_ASTEROIDS_ALIVE(Box_Collision_Bullets());

		life_up(10000);

		if (!al_get_timer_started(global->respawn_timer) && global->ship.live)
			Box_Collision_Ship();
	}

	if (!al_destroy_blasteroids())
		error("Couldn't destroy everything");
	return 0;
}

void error(char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

int al_destroy_blasteroids()
{
	al_destroy_timer(global->asteroid_rotation_timer);
	al_destroy_timer(global->fire_rate_timer);
	al_destroy_bitmap(global->AsteroidBitmap);
	al_destroy_bitmap(global->ship.image);
	global->SpaceShipBitmapCreated = false;
	al_destroy_sample(global->shoot_sound);
	al_destroy_sample(global->explosion_sound);
	al_destroy_sample(global->lifeup_sound);
	al_destroy_sample(global->flame_sound);
	free(global->bullets);
	free(global->asteroids);
	LOG(1, "Freed All Blasteroids Variables\n");
	return 1;
}

int al_register_all()
{
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

void blasteroids_init()
{
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
		DISPLAY_HEIGHT / 2.0,		 //	sx
		DISPLAY_WIDTH / 2.0,		 // sy
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

	if (!al_install_audio())
		error("Couldn't initialize Allegro Audio");

	if (!al_init_acodec_addon())
		error("Couldn't initialize Allegro Acodec");

	if (!al_reserve_samples(1))
		error("Couldn't initialize Allegro Audio Reverse");

	if(!al_reserve_samples(100))
		error("Couldn't resever audio samples");

	global->shoot_sound = al_load_sample("./assets/Laser_Shoot.wav");
	if (!global->shoot_sound)
		error("Couldn't load Shoot Sound");

	global->explosion_sound = al_load_sample("./assets/Explosion.wav");
	if (!global->explosion_sound)
		error("Couldn't Load Explosion Sound");

	global->flame_sound = al_load_sample("./assets/Flame.wav");
	if (!global->flame_sound)
		error("Couldn't Load Flame Sound");

	global->flame_instance = al_create_sample_instance(global->flame_sound);
	if (!global->flame_instance)
		error("Couldn't Create Flame Insance");

	al_set_sample_instance_playmode(global->flame_instance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(global->flame_instance, al_get_default_mixer());

	global->lifeup_sound = al_load_sample("./assets/Life_Up.wav");
	if (!global->lifeup_sound)
		error("Couldn't Load Life Up Sound");

	global->death_sound= al_load_sample("./assets/Death.wav");
	if (!global->death_sound)
		error("Couldn't Load Death Sound");


	global->asteroid_rotation_timer = al_create_timer(1.0 / 15);
	if (!global->asteroid_rotation_timer)
		error("Couldn't initialize Asteroid Rotation Timer");

	global->fire_rate_timer = al_create_timer(1.0 / 2);
	if (!global->fire_rate_timer)
		error("Couldn't initialize Fire Rate Timer");

	global->respawn_timer = al_create_timer(1.0 / 10);
	if (!global->respawn_timer)
		error("Couldn't initialize Respawn Timer");

	if (!al_register_all())
		error("Coulnd't register something");

	al_start_timer(global->fire_rate_timer);
	al_start_timer(global->asteroid_rotation_timer);

	LOG(1, "Blasteroids Variables initialised");

	draw_ship();
}

void draw_score()
{
	al_draw_textf(global->font, al_map_rgb(0, 255, 0),
				 DISPLAY_WIDTH / 2.0, 50,
				 ALLEGRO_ALIGN_CENTER, "Score: %'u", global->score);
}
