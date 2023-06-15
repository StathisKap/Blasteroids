#ifndef BLASTEROIDS_
#define BLASTEROIDS_
#include "../include/main.h"
#endif

Global *global;
GameState gameState;
int selection;

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
        	      case HIGH_SCORES:
        	          // Show high scores.
        	          break;
        	      default:
        	          break;
        	}
    };
}

int menu()
{
    LOG(1, "Start of the Menu\n");
    selection = 0;
    init_menu();
    while (gameState == MENU){
        al_wait_for_event(global->queue, &global->event); // Capture keystrokes

        // if the timer has ticked, redraw
        if (global->event.type == ALLEGRO_EVENT_TIMER){
            global->redraw = true;
        }
       // if the user has pressed ESC or clicked the x on the window. Then close
        else if (global->event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ||
                 (global->event.type == ALLEGRO_EVENT_KEY_DOWN &&
                  global->event.keyboard.keycode == ALLEGRO_KEY_ESCAPE))
            global->done = true;

        if (global->redraw && al_is_event_queue_empty(global->queue))
        {
            draw_menu(&selection);
            global->redraw = false;
        }

        if (global->event.type == ALLEGRO_EVENT_KEY_DOWN) {
            selection = keys_for_menu(&selection);
        }
    }
    return 0;
}


void init_menu()
{
    LOG(1, "Initialising Global Variables for Menu");
    srand(0);
    setlocale(LC_NUMERIC, "");

	  global->redraw = true;
	  global->done = false;

    if (!al_init())
        error("Couldn't initialize Allegro");

    if (!al_init_primitives_addon())
        error("Couldn't initialize Allegro Primitives");

    if (!al_init_font_addon())
        error("Couldn't initialize Allegro Font");

    if (!al_init_ttf_addon())
        error("Couldn't initialize Allegro TTF");

    global->font = al_load_ttf_font("./assets/arial.ttf", 40, 0);
    if (!global->font)
        error("Couldn't Load TTF");
    else
        printf("Loaded TTF\n");

    if (!al_install_keyboard())
        error("Couldn't initialize Keyboard");

    global->queue = al_create_event_queue();
    if (!global->queue)
        error("Couldn't initialize Queue");

    global->disp = al_create_display(DISPLAY_HEIGHT, DISPLAY_WIDTH);
    if (!global->disp)
        error("Couldn't initialize Display");

    global->timer = al_create_timer(1.0 / FPS); // FPS
	  if (!global->timer)
		    error("Couldn't initialize Timer");

    al_set_window_title(global->disp, "Blasteroids");


	  if (!register_menu_events())
        error("Coulnd't register Menu events");

	  al_start_timer(global->timer);

    draw_menu(&selection);
    LOG(1, "Initialised Global Variables for Menu");
}

void draw_menu(int *selection)
{
    // Set the color to dark green and clear the screen
    al_clear_to_color(al_map_rgb(0, 100, 0));
    // Calculate the height of the menu options
    int font_height = al_get_font_line_height(global->font);
    int total_height = font_height * 4; // 3 options and 1 additional space for between the options

    // The Y position to start drawing the menu options
    int start_y = (DISPLAY_HEIGHT - total_height) / 2; // This will center the options

    int options_num = 2;
    char options[][5] = {"PLAY", "EXIT" };

    // Set the color to white for the text
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR gray= al_map_rgb(150, 150, 150);

    ALLEGRO_COLOR colors[options_num];

    for (int i = 0; i < options_num; i++){
        colors[i] = *selection == i ? white : gray;
        al_draw_text(global->font, colors[i], DISPLAY_WIDTH / 2.0, start_y +font_height * i,
                     ALLEGRO_ALIGN_CENTRE, options[i]);
    }
    LOG(1, "Selection in draw_menu: %d", *selection);

    al_flip_display();
}

int register_menu_events()
{
    LOG(1, "Registering menu events");
    al_register_event_source(global->queue, al_get_keyboard_event_source());
	  al_register_event_source(global->queue, al_get_timer_event_source(global->timer));
    al_register_event_source(global->queue, al_get_display_event_source(global->disp));
    LOG(1, "Registered menu events");
    return 1;
}

int keys_for_menu(int *selection)
{
    LOG(1, "%d", *selection);
    if (global->event.keyboard.keycode == ALLEGRO_KEY_DOWN){
        (*selection)++;
    }

    if (global->event.keyboard.keycode == ALLEGRO_KEY_UP){
        (*selection)--;
    }

    if (global->event.keyboard.keycode == ALLEGRO_KEY_ENTER){
        gameState = *selection;
    }

    if (*selection < 0)
        *selection = 0;
    else if (*selection > 1)
        *selection = 1;

    return *selection;
}
