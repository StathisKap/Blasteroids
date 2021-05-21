/*
 *
 * if an asteroid is hit by a blast from the spaceship's cannon
 * it immediately splits into two
 * Each of these parts will be half the size of the original asteroid.
 * Once an asteroid has been split 2 times, it's gone.
 * The player score increases by 100 with each hit
 *
 *
 * Use linked lists for sets of asteroid
 * or arrays
 *
 *
typedef struct {
	float sx;
	float sy;
	float heading;
	float twist;
	float speed;
	float rot_velocity;
	float scale;
	int gone;
	ALLEGRO_COLOR color;
} Asteroid;

*/


/* To draw an asteroid
 al_draw_line(-20, 20, -25, 5, a->color, 2.0f);
 al_draw_line(-25, 5, -25, -10, a->color, 2.0f);
 al_draw_line(-25, -10, -5, -10, a->color, 2.0f);
 al_draw_line(-5, -10, -10, -20, a->color, 2.0f);
 al_draw_line(-10, -20, 5, -20, a->color, 2.0f);
 al_draw_line(5, -20, 20, -10, a->color, 2.0f);
 al_draw_line(20, -10, 20, -5, a->color, 2.0f);
 al_draw_line(20, -5, 0, 0, a->color, 2.0f);
 al_draw_line(0, 0, 20, 10, a->color, 2.0f);
 al_draw_line(20, 10, 10, 20, a->color, 2.0f);
 al_draw_line(10, 20, 0, 15, a->color, 2.0f);
 al_draw_line(0, 15, -20, 20, a->color, 2.0f);
 */
