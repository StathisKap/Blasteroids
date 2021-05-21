#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#define PI 3.14159265359
#define ROT_SPEED PI * 0.05

typedef struct {
	float sx; //Where it is on the screen
	float sy;//*
	float heading; //The direction it's pointing
	float speed;
	int gone; //is it dead?
	ALLEGRO_COLOR color;
} Spaceship;


void draw_ship(Spaceship* s);