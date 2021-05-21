#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#ifndef HEADER_
#define HEADER_
#include "../include/blasteroids_header.h"
#endif

void draw_ship(Spaceship* s)
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, s->heading);
	al_translate_transform(&transform, s->sx, s->sy);
	al_use_transform(&transform);
	al_draw_line(-8, 9, 0, -11, s->color, 3.0f);
	al_draw_line(0, -11, 8, 9, s->color, 3.0f);
	al_draw_line(-6, 4, -1, 4, s->color, 3.0f);
	al_draw_line(6, 4, 1, 4, s->color, 3.0f);
}

/* Collisions
 * If the spaceship collides with a rock, it dies immediately and the player
 * loses a life. For the first 5 seconds after a new ship is created, it
 * doesn't check for collisions. The new ship should appear in the center of
 * the screen
 */

/* Spaceship behaviour
 * The spaceship starts stationary in the center of the screen.
 * "Up" goes forward. "Right" and "Left" rotate. "Space" fires
 */

