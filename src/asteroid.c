#ifndef ASTEROID_
#define ASTEROID_
#include "../include/blasteroids.h"
#endif

extern Global *global;

void draw_asteroid()
{
	int res = 3;
	int size = res * 50;
	float thickness = 3.0f * res;
	if (global->AsteroidBitmap == NULL)
	{
		// Asteroid bitmap
		global->AsteroidBitmap = al_create_bitmap(size, size);
		int offset = size / 2;
		ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
		al_set_target_bitmap(global->AsteroidBitmap);

		al_draw_line(res * -20 + offset, res * 20 + offset, res * -25 + offset, res * 5 + offset, color, thickness);
		al_draw_line(res * -25 + offset, res * 5 + offset, res * -25 + offset, res * -10 + offset, color, thickness);
		al_draw_line(res * -25 + offset, res * -10 + offset, res * -5 + offset, res * -10 + offset, color, thickness);
		al_draw_line(res * -5 + offset, res * -10 + offset, res * -10 + offset, res * -20 + offset, color, thickness);
		al_draw_line(res * -10 + offset, res * -20 + offset, res * 5 + offset, res * -20 + offset, color, thickness);
		al_draw_line(res * 5 + offset, res * -20 + offset, res * 20 + offset, res * -10 + offset, color, thickness);
		al_draw_line(res * 20 + offset, res * -10 + offset, res * 20 + offset, res * -5 + offset, color, thickness);
		al_draw_line(res * 20 + offset, res * -5 + offset, res * 0 + offset, res * 0 + offset, color, thickness);
		al_draw_line(res * 0 + offset, res * 0 + offset, res * 20 + offset, res * 10 + offset, color, thickness);
		al_draw_line(res * 20 + offset, res * 10 + offset, res * 10 + offset, res * 20 + offset, color, thickness);
		al_draw_line(res * 10 + offset, res * 20 + offset, res * 0 + offset, res * 15 + offset, color, thickness);
		al_draw_line(res * 0 + offset, res * 15 + offset, res * -20 + offset, res * 20 + offset, color, thickness);

		al_set_target_bitmap(al_get_backbuffer(global->disp));
		LOG(1, "Asteroid Bitmap Created\n");
	}

	LOG(2, "Draw Asteroids Function Call\n");
	for (short i = 0; i < global->asteroids_max_count * 2; i++)
	{
		LOG(3, "Drawing Asteroid %d\t is_dead: %d\n", i, global->asteroids[i].dead);
		global->asteroids[i].image = global->AsteroidBitmap;

		if (!global->asteroids[i].dead)
		{
			float s = global->asteroids[i].s = global->asteroids[i].scale * size;
			ALLEGRO_TRANSFORM transform;
			al_identity_transform(&transform);
			al_rotate_transform(&transform, global->asteroids[i].twist);						  // We rotate it
			al_translate_transform(&transform, global->asteroids[i].sx, global->asteroids[i].sy); // We move it to an initial position
			al_use_transform(&transform);
			al_draw_tinted_scaled_bitmap(
				global->asteroids[i].image,
				global->asteroids[i].color,
				0, 0,
				size, size,
				-s / 2, -s / 2,
				s, s,
				0);
		}
		LOG(2, "Drew Asteroid\n");
	}

	update_asteroid();
}

void Realloc_Asteroid()
{
	// Create a temporary array
	Asteroid *temp = malloc(sizeof(Asteroid) * global->asteroids_alive);
	if (temp == NULL)
	{
		error("Failed to allocate memory to temp in Realloc Asteroid\n");
	}

	// Copy the contents of global->asteroids to the temporary array
	memcpy(temp, global->asteroids, sizeof(Asteroid) * global->asteroids_alive);

	// Reallocate global->asteroids
	global->asteroids = realloc(global->asteroids, sizeof(Asteroid) * global->asteroids_max_count * 2);
	if (global->asteroids == NULL)
	{
		error("Failed to allocate memory to global->asteroids in Realloc Asteroid\n");
		free(temp);
		return;
	}

	// Copy the contents of the temporary array back to global->asteroids
	memcpy(global->asteroids, temp, sizeof(Asteroid) * global->asteroids_alive);
	global->asteroids[global->asteroids_max_count - 1].dead = true;

	// Free the temporary array
	free(temp);
}


void spawn_asteroid()
{
	// Count the number of dead asteroids

	short dead_asteroids = 0;
	for (short i = 0; i < global->asteroids_max_count; i++)
	{
		if (global->asteroids[i].dead)
			dead_asteroids++;
	}
	LOG(1, "Dead Asteroids %d\tAlive Asteroids %d", dead_asteroids, global->asteroids_alive);

	// Check if the sum of dead and alive asteroids exceeds double the max count
	if (global->asteroids_alive > global->asteroids_max_count * 2)
		error("Error: More asteroids alive than double the max count\n");

	// Check if all asteroids are dead and none are alive
	if (dead_asteroids == global->asteroids_max_count && global->asteroids_alive == 0)
	{
		// Increment the max count and reallocate memory for the asteroids array
		global->asteroids_max_count++;
		Realloc_Asteroid();
		short new_asteroids_count = global->asteroids_max_count;

		// Set all asteroids to dead initially
		for (int i = 0; i < global->asteroids_max_count * 2; i++)
			global->asteroids[i].dead = true;

		// Spawn new asteroids
		for (short i = 0; i < global->asteroids_max_count && new_asteroids_count > 0; i++)
		{
			if (global->asteroids[i].dead)
			{

				// Declare a variable to store the initial x value of the asteroid
				 int x_initial = 0;

				// Loop until a valid x value is generated
				do
				{
					// Generate a random value between 0 and 1, and select a value for x_initial based on the result
					// If the random value is 0, set x_initial to a random value between 0 and half the display width minus a fifth of the display width
					// If the random value is 1, set x_initial to the display width minus a random value between 0 and half the display width minus a fifth of the display width
					x_initial = rand() % 2 ? (rand() % (DISPLAY_WIDTH / 2 - DISPLAY_WIDTH / 5)) : DISPLAY_WIDTH - rand() % (DISPLAY_WIDTH / 2 - DISPLAY_WIDTH / 5);
				} while (fabsf(global->ship.sx - x_initial) < 100); // Repeat the loop if the distance between the ship's x coordinate and the generated x coordinate is less than 100

				// Declare a variable to store the initial x value of the asteroid
				 int y_initial = 0;

				// Loop until a valid x value is generated
				do
				{
					// Generate a random value between 0 and 1, and select a value for y_initial based on the result
					// If the random value is 0, set y_initial to a random value between 0 and half the display width minus a fifth of the display width
					// If the random value is 1, set y_initial to the display width minus a random value between 0 and half the display width minus a fifth of the display width
					y_initial = rand() % 2 ? (rand() % (DISPLAY_WIDTH / 2 - DISPLAY_WIDTH / 5)) : DISPLAY_WIDTH - rand() % (DISPLAY_WIDTH / 2 - DISPLAY_WIDTH / 5);
				} while (fabsf(global->ship.sy - y_initial) < 100); // Repeat the loop if the distance between the ship's x coordinate and the generated x coordinate is less than 100

				float heading_initial = (float)rand() / (float)RAND_MAX * (2 * PI);
				float twist_initial = (float)rand() / (float)RAND_MAX * (2 * PI);
				float speed_initial = (float)rand() / (float)RAND_MAX + 1;
				float rot_velocity_initial = (float)rand() / (float)RAND_MAX * 10;
				float scale_initial = 1.0;

				// Set the asteroid's properties to the generated values and set it as alive
				global->asteroids[i].sx = x_initial;
				global->asteroids[i].sy = y_initial;
				global->asteroids[i].heading = heading_initial;
				global->asteroids[i].twist = twist_initial;
				global->asteroids[i].speed = speed_initial;
				global->asteroids[i].rot_velocity = rot_velocity_initial;
				global->asteroids[i].scale = scale_initial;
				global->asteroids[i].color = al_map_rgba_f(0.211, 0.368, 0.639, 1);

				global->asteroids_alive++;
				new_asteroids_count--;
				global->asteroids[i].dead = false;

				LOG(1, "Asteroid Spawned");
			}
		}
	}
}

void update_asteroid()
{
	for (short i = 0; i < global->asteroids_max_count * 2; i++)
	{
		if (!global->asteroids[i].dead)
		{
			LOG(2, "A%d: %d\t", i, global->asteroids[i].dead);
			if (global->event.timer.source == global->asteroid_rotation_timer)
				global->asteroids[i].twist += global->asteroids[i].rot_velocity * PI / 180;

			if (global->asteroids[i].twist > 2 * PI)
				global->asteroids[i].twist = 0;

			if (global->asteroids[i].twist < 0)
				global->asteroids[i].twist = 2 * PI;

			global->asteroids[i].sx += global->asteroids[i].speed * cos(global->asteroids[i].heading);
			global->asteroids[i].sy += global->asteroids[i].speed * sin(global->asteroids[i].heading);

			teleport(&global->asteroids[i].sx, &global->asteroids[i].sy);
		}
	}
	LOG(2, "Asteroids alive after Update: %d\n", global->asteroids_alive);
}

void Split(short j)
{
	LOG(1, "Splitting");

	// Print the status of all asteroids in the array
	for (short i = 0; i < global->asteroids_max_count * 2; i++)
		LOG(1, "Asteroid %d is %s", i, global->asteroids[i].dead ? "Dead" : "Alive");
	
	global->asteroids[j].dead = true;
	global->asteroids_alive--;

	global->score += global->asteroids[j].scale * 100;

	LOG(1, "\n\tAsteroid %d is %s", j, global->asteroids[j].dead ? "Dead" : "Alive");

	// Check if the asteroid's scale is greater than 0.5
	if (global->asteroids[j].scale > 0.5)
	{
		// Check if there is enough space in the array for the new asteroids
		if (global->asteroids_alive + 2 <= global->asteroids_max_count * 2)
		{

			LOG(1, "Generating Asteroid 1. Max_Count: %d", global->asteroids_max_count);
			// Create two new asteroids and add them to the array
			// Create the first new asteroid
			Asteroid asteroid1 = global->asteroids[j];
			asteroid1.scale = 0.5;
			asteroid1.twist = rand() * 2 * PI / RAND_MAX;
			asteroid1.heading = rand() * 2 * PI / RAND_MAX;
			asteroid1.speed = global->asteroids[j].speed * (float)rand() / RAND_MAX * 1.5f;
			asteroid1.color = al_map_rgb(255, 0, 255);
			asteroid1.sx = global->asteroids[j].sx + (float)rand() / RAND_MAX * 25;
			asteroid1.sy = global->asteroids[j].sy + (float)rand() / RAND_MAX * 25;
			asteroid1.dead = false;

			// Find the first empty spot in the array and add the new asteroid
			for (short i = 0; i < global->asteroids_max_count * 2; i++)
				if (global->asteroids[i].dead)
				{
					LOG(1, "Adding Asteroid 1 to position %d", i);
					global->asteroids[i] = asteroid1;
					global->asteroids_alive++;
					break;
				}

			LOG(1, "Generating Asteroid 2. Max_Count: %d", global->asteroids_max_count);
			// Create the second new asteroid
			Asteroid asteroid2 = global->asteroids[j];
			asteroid2.scale = 0.5;
			asteroid2.twist = rand() * 2 * PI / RAND_MAX;
			asteroid2.heading = rand() * 2 * PI / RAND_MAX;
			asteroid2.speed = global->asteroids[j].speed * (float)rand() / RAND_MAX * 1.5f;
			;
			asteroid2.color = al_map_rgb(255, 0, 255);
			asteroid2.sx = global->asteroids[j].sx + (float)rand() / RAND_MAX * 25;
			asteroid2.sy = global->asteroids[j].sy + (float)rand() / RAND_MAX * 25;
			asteroid2.dead = false;

			// Find the next empty spot in the array and add the new asteroid
			for (short i = 0; i < global->asteroids_max_count * 2; i++)
				if (global->asteroids[i].dead)
				{
					LOG(1, "Adding Asteroid 2 to position %d", i);
					global->asteroids[i] = asteroid2;
					global->asteroids_alive++;
					break;
				}


		}
		else
		{
			// Handle case where there is not enough space in the array for the new asteroids
			global->asteroids[j].scale -= global->asteroids[j].scale / 3;
		}
	}
}

/*
 * if an asteroid is hit by a blast from the spaceship's cannon
 * it immediately splits into two
 * Each of these parts will be half the size of the original asteroid.
 * Once an asteroid has been split 2 times, it's dead.
 * The player score increases by 100 with each hit
 *
 * Use linked lists for sets of asteroid
 * or arrays
 */
