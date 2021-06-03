#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#define PI 3.14159265359
#define ROT_SPEED PI * 0.025
#define SPACESHIP_KEYS_NUM 5
#define SPACESHIP_SPEED 0.05
#define DRAG 0.005
#define MASS 0.05
#define SPACESHIP_SPEED_MAX 4.5
#define DISPLAY_WIDTH 700
#define DISPLAY_HEIGHT 700
#define BULLET_COUNT 30
#define BULLET_SPEED 5

enum KEYS {UP, LEFT, RIGHT, SPACE, DOWN};

typedef struct {
	float sx; //Where it is on the screen
	float sy;//*
	float heading; //The direction it's pointing
	float speed;
	float drift;
	float scale;
	bool live; //is it dead?
	ALLEGRO_COLOR color;
} Spaceship;


typedef struct 
{
	float sx; //Where it is on the screen
	float sy;
	float heading;
	bool live; //is it dead?
	ALLEGRO_COLOR color;
} Bullet;



void draw_ship(Spaceship* s);
void ReadKeysForSpaceship(ALLEGRO_EVENT *Ev, bool Keys[SPACESHIP_KEYS_NUM]);
void UseKeysForSpaceship(Spaceship *s, bool Keys[SPACESHIP_KEYS_NUM], Bullet bullets[]);
void error(char *msg);
int al_destroy_all(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer_event, ALLEGRO_EVENT_QUEUE *event_queue);
int al_register_all(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer_event, ALLEGRO_EVENT_QUEUE *event_queue);
void teleport(float *sx, float *sy);
void init_bullet(Bullet bullets[]);
void draw_bullet(Bullet bullets[]);
void fire_bullet(Bullet bullets[], Spaceship *s);
void update_bullet(Bullet bullets[]);
