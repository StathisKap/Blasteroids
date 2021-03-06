#ifndef INCLUDE_BLASTEROIDS_H_
    #define INCLUDE_BLASTEROIDS_H_
#endif // INCLUDE_BLASTEROIDS_H_

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#define PI M_PI
#define ROT_SPEED PI * 0.025
#define SPACESHIP_KEYS_NUM 6
#define SPACESHIP_SPEED 0.08
#define SPACESHIP_SPEED_MAX 4.5
#define DRAG 0.005
#define MASS 0.05
#define DISPLAY_WIDTH 1400
#define DISPLAY_HEIGHT 1400
#define BULLET_COUNT 15
#define BULLET_SPEED 15
#define MAX_BIG_ASTEROIDS 4

enum COLOURS {YELLOW, ORANGE, RED};

#include "./collisions.h"
#include "./asteroid.h"
#include "./spaceship.h"
#include "./blast.h"

typedef struct Global{
    short Player_Lives;
    bool done;
    bool SpaceShipBitmapCreated;
    bool redraw;
    Bullet *bullets;
    Asteroid *asteroids;
    Spaceship ship;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_EVENT event;
    ALLEGRO_DISPLAY * disp;
    ALLEGRO_FONT * font;
    ALLEGRO_TIMER * asteroid_rotation_timer;
    ALLEGRO_TIMER * fire_rate_timer;
    ALLEGRO_TIMER * timer;
    ALLEGRO_TIMER * respawn_timer;
    ALLEGRO_BITMAP *AsteroidBitmap;
} Global;

void Blasteroids_Init(Global * global);
void error(char *msg);
int  al_destroy_all();
int  al_register_all();
void teleport(float *sx, float *sy);
