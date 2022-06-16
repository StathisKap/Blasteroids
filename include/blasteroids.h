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

#define PI 3.14159265359
#define ROT_SPEED PI * 0.025
#define SPACESHIP_KEYS_NUM 5
#define SPACESHIP_SPEED 0.025
#define SPACESHIP_SPEED_MAX 2.5
#define DRAG 0.005
#define MASS 0.05
#define DISPLAY_WIDTH 700
#define DISPLAY_HEIGHT 700
#define BULLET_COUNT 100000
#define BULLET_SPEED 15
#define MAX_BIG_ASTEROIDS 4

enum KEYS {UP, LEFT, RIGHT, SPACE, DOWN};
enum COLOURS {YELLOW, ORANGE, RED};

#include "collisions.h"
#include "asteroid.h"
#include "spaceship.h"
#include "blast.h"

typedef struct Global{
    bool done;
    Bullet *bullets;
    Asteroid *asteroids;
    bool *Keys;
    Spaceship ship;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_EVENT event;
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_TIMER *asteroid_rotation_timer;
    ALLEGRO_TIMER* timer;
    ALLEGRO_BITMAP *collision_mask;
    bool SpaceShipBitmapCreated;
    bool redraw;
    ALLEGRO_BITMAP *AsteroidBitmap;
} Global;



void Blasteroids_Init(Global * global);
void ReadKeysForSpaceship(); 
void UseKeysForSpaceship();
void error(char *msg);
int  al_destroy_all();
int  al_register_all();
void teleport(float *sx, float *sy);