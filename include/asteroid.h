#ifndef INCLUDE_ASTEROID_H_
	#define INCLUDE_ASTEROID_H_
#endif // INCLUDE_ASTEROID_H_

void Realloc_Asteroid();
void spawn_asteroid();
void draw_asteroid();
void update_asteroid();
void Split(short j);

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
	float s;
} Asteroid;
