#ifndef INCLUDE_MENU_H_
    #define INCLUDE_MENU_H_
#endif // INCLUDE_MENU_H_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include "./blasteroids.h"


typedef enum GameState {
    MENU,
    PLAY,
    EXIT,
} GameState;

void init_menu();
void draw_menu(int *selection);
int al_destroy_all();
int menu();
int register_menu_events();
int keys_for_menu(int * selection);
