#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#define PI 3.14159265359
#define ROT_SPEED PI * 0.025

enum KEYS {UP, LEFT, RIGHT, SPACE};

typedef struct {
	float sx; //Where it is on the screen
	float sy;//*
	float heading; //The direction it's pointing
	float speed;
	float scale;
	int gone; //is it dead?
	ALLEGRO_COLOR color;
} Spaceship;


void draw_ship(Spaceship* s);