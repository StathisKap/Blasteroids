#ifndef MAIN_
#define MAIN_
#include "../include/main.h"
#endif

Global *global;
GameState gameState;
void main()
{
    int menuSelection = 0;
    gameState = MENU;
    LOG(1, "Start of the program\n");
    global = malloc(sizeof(Global));

    while (!global->done)
    {
        LOG(1, "Main Loop\n");
            switch (gameState) {
        	      case MENU:
                    LOG(1, "Menu Case\n");
                    menu();
        	      break;
        	      case PLAY:
                    LOG(1, "Blasteroids Case\n");
                    blasteroids();
        	          break;
        	      case EXIT:
                    LOG(1, "Exit Case\n");
                    global->done = true;
        	          break;
        	      default:
        	          break;
        	}
    };
    al_destroy_all();
}


int al_destroy_all()
{
	al_destroy_display(global->disp);
	al_destroy_timer(global->timer);
	al_destroy_event_queue(global->queue);
	al_destroy_font(global->font);
  free(global);
	LOG(1, "Freed All Blasteroids Variables\n");
	return 1;
}
