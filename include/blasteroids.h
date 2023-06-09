#ifndef INCLUDE_BLASTEROIDS_H_
    #define INCLUDE_BLASTEROIDS_H_
#endif // INCLUDE_BLASTEROIDS_H_

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <time.h>
#include <locale.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define PI M_PI
#define FPS 60.0
#define ROT_SPEED PI * 0.01875
#define SPACESHIP_KEYS_NUM 6
#define SPACESHIP_SPEED 0.08
#define SPACESHIP_SPEED_MAX 4.5
#define DRAG 0.005
#define MASS 0.05
#define DISPLAY_WIDTH 1400
#define DISPLAY_HEIGHT 1400
#define BULLET_COUNT 15
#define BULLET_SPEED 15
#define MAX_BIG_ASTEROIDS 2

enum COLOURS {YELLOW, ORANGE, RED};

#include "./collisions.h"
#include "./asteroid.h"
#include "./spaceship.h"
#include "./blast.h"

typedef struct Global{
    short Player_Lives;
    unsigned int score;
    bool done;
    bool SpaceShipBitmapCreated;
    bool redraw;
	  short asteroids_alive;
	  short asteroids_max_count;
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
    ALLEGRO_SAMPLE* shoot_sound;
    ALLEGRO_SAMPLE* explosion_sound;
    ALLEGRO_SAMPLE* lifeup_sound;
    ALLEGRO_SAMPLE* flame_sound;
    ALLEGRO_SAMPLE* death_sound;
    ALLEGRO_SAMPLE_INSTANCE *flame_instance;
} Global;

void draw_score();
void Blasteroids_Init(Global * global);
void error(char *msg);
int  al_destroy_all();
int  al_register_all();
void teleport(float *sx, float *sy);

#define LOG_LEVEL 0

#define DEBUG_ASTEROIDS_ALIVE(func_call) do { \
    if (LOG_LEVEL == 2) { \
        printf("\033[1;31mBefore %s \033[0mat %s:%d - asteroids_alive: %d\n", #func_call, __FILE__, __LINE__, global->asteroids_alive); \
    } \
    func_call; \
    if (LOG_LEVEL == 2) { \
        printf("\033[1;31mAfter %s \033[0mat %s:%d - asteroids_alive: %d\n", #func_call, __FILE__, __LINE__, global->asteroids_alive); \
    } \
} while (0)



#define LOG(level, message, ...) \
        do { \
            if (LOG_LEVEL >= level) { \
                const char* color_code = ""; \
                switch (level) { \
                    case 1: color_code = "\033[1;33m"; break; /* yellow */ \
                    case 2: color_code = "\033[1;35m"; break; /* orange */ \
                    case 3: color_code = "\033[1;31m"; break; /* red */ \
                    default: color_code = ""; break; \
                } \
                printf("%s[LOG][%d] %s:%s():%d - " message "\033[0m\n", \
                    color_code, LOG_LEVEL, __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
            } \
        } while (0)
