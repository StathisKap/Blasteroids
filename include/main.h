#ifndef INCLUDE_MAIN_H_
    #define INCLUDE_MAIN_H_

    #include <allegro5/allegro5.h>
    #include <allegro5/allegro_font.h>
    #include <allegro5/allegro_primitives.h>
    #include <allegro5/allegro_image.h>
    #include <allegro5/allegro_ttf.h>
    #include "./debug.h"
    #include "./blasteroids.h"

    typedef enum GameState {
        MENU,
        PLAY,
        HIGH_SCORE,
        EXIT,
    } GameState;

    int al_destroy_all();
#endif // INCLUDE_MAIN_H_
