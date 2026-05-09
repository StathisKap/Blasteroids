#ifndef MAIN_
#define MAIN_
#include "../include/main.h"
#include "../include/menu.h"
#include "../include/score.h"
#endif

Global *global;
GameState gameState;
int main() {
  int menuSelection = 0;

  gameState = MENU;
  LOG(1, "Start of the program\n");
  global = malloc(sizeof(Global));

  while (!global->done) {
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
    case HIGH_SCORE:
      LOG(1, "High Score Case\n");
      //int count = 10;
      //Score *scores;
      //scores = get_all_scores(&count);
      //for (int i = 0; i < count; i++) {
      //  printf("%s: %d\n", scores[i].name, scores[i].points);
      //}
      //for (int i = 0; i < count; i++)
      //  free(scores[i].name);
      //free(scores);
      //gameState = MENU;
      scoreboard();
      break;
    case EXIT:
      LOG(1, "Exit Case\n");
      global->done = true;
      break;
    default:
      break;
    }
  };
  if (!al_destroy_all())
    error("Couldn't destroy all Main Variables");
  return 0;
}

int al_destroy_all() {
  al_destroy_display(global->disp);
  al_destroy_timer(global->timer);
  al_destroy_event_queue(global->queue);
  al_destroy_font(global->font);
  free(global);
  LOG(1, "Freed All Blasteroids Variables\n");
  return 1;
}
