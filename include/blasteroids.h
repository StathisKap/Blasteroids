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
#define BULLET_COUNT 100000
#define BULLET_SPEED 15
#define MAX_BIG_ASTEROIDS 4

enum KEYS {UP, LEFT, RIGHT, SPACE, DOWN};
enum COLOURS {YELLOW, ORANGE, RED};

#include "asteroid.h"
#include "spaceship.h"
#include "../include/blast.h"
void ReadKeysForSpaceship(ALLEGRO_EVENT *Ev); 
void UseKeysForSpaceship();
void error(char *msg);
int  al_destroy_all(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer_event, ALLEGRO_EVENT_QUEUE *event_queue);
int  al_register_all(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer_event, ALLEGRO_EVENT_QUEUE *event_queue);
void teleport(float *sx, float *sy);
