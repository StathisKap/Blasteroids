/*
 * Unlike the other objects, blasts that disappear off the screen won't
 * reappear.
 * Blasts are always fired in the direction of the ship
 * They always travel in a straight line and constant speed
 * If a blast collides with an asteroid, the asteroid will divide into two
*typedef struct {
*	float sx;
*	float sy;
*	float heading;
*	float speed;
*	int gone;
*	ALLEGRO_COLOR color;
*	} Blast;
 */
