#ifndef INCLUDE_ASTEROID_H_
	#define INCLUDE_ASTEROID_H_
#endif // INCLUDE_ASTEROID_H_

void spawn_asteroid();
void draw_asteroid();
void update_asteroid();

typedef struct {
	float sx;
	float sy;
	float heading;
	float twist;
	float speed;
	float rot_velocity;
	float scale;
	int dead;
	ALLEGRO_COLOR color;
	ALLEGRO_BITMAP *image;
	mask_t * mask;
	float s;
} Asteroid;
