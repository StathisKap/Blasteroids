#ifndef INCLUDE_MENU_H_
    #define INCLUDE_MENU_H_
#endif // INCLUDE_MENU_H_

#include "./main.h"

int menu();
void init_menu();
void draw_menu(int *selection);
int register_menu_events();
int keys_for_menu(int * selection);
