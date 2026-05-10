#ifndef SCORE_
#define SCORE_
#include "../include/score.h"
#include "../include/blasteroids.h"
#include "../include/main.h"
#include "allegro5/allegro_font.h"
#include "allegro5/keycodes.h"
#include <sqlite3.h>
#include <stdio.h>
#endif

extern Global *global;
extern GameState gameState;

int scoreboard() {
  LOG(1, "Start of the Scoreboard\n");
  if (!global->disp)
    init_scoreboard();

  int count;
  Score *scores = get_all_scores(&count);
  int selection = 0;

  LOG(1, "Drawing the Scoreboard Once\n");
  draw_scoreboard(&selection, scores, count);
  while (gameState == HIGH_SCORE) {
    al_wait_for_event(global->queue, &global->event); // Capture keystrokes

    // if the timer has ticked, redraw
    if (global->event.type == ALLEGRO_EVENT_TIMER) {
      global->redraw = true;
    }
    // if the user clicked the x on the window. Then close
    else if (global->event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
      global->done = true;

    if (global->redraw && al_is_event_queue_empty(global->queue)) {
      draw_scoreboard(&selection, scores, count);
      global->redraw = false;
    }

    if (global->event.type == ALLEGRO_EVENT_KEY_DOWN) {
      keys_for_scoreboard(&selection, count);
    }
  }
  return 0;
}

void init_scoreboard() {
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

  if (!register_scoreboard_events())
    error("Coulnd't register Menu events");

  al_start_timer(global->timer);

  LOG(1, "Initialised Global Variables for Menu");
}

void draw_scoreboard(int *selection, Score *scores, short scores_num) {
  ALLEGRO_TRANSFORM transform;

  al_identity_transform(&transform);
  // Set the color to dark green and clear the screen
  al_clear_to_color(al_map_rgb(0, 100, 0));
  // Calculate the height of the scoreboard scores
  int font_height = al_get_font_line_height(global->font);
  int total_height = font_height * 4; // 3 scores and 1 additional space for between the scores

  // The Y position to start drawing the scoreboard scores
  int start_y = (DISPLAY_HEIGHT - total_height) / 2; // This will center the scores
  int max_name_width = 0;
  int gap = 20;
  int center = DISPLAY_WIDTH / 2;

  for (int i = 0; i < scores_num; i++) {
    int w = al_get_text_width(global->font, scores[i].name);
    if (w > max_name_width) max_name_width = w;
  }

  // Set the colors of the text and the chosen scores
  ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
  ALLEGRO_COLOR gray = al_map_rgb(150, 150, 150);

  ALLEGRO_COLOR colors[scores_num];

  for (int i = 0; i < scores_num; i++) {
    char points_str[64];
    char name_str[64];
    snprintf(name_str, sizeof(name_str), "%s:", scores[i].name);
    snprintf(points_str, sizeof(points_str), "%d", scores[i].points);
    colors[i] = *selection == i ? white : gray;
    int y = start_y + font_height * i;

    al_draw_text(global->font, colors[i], center - gap, y,
        ALLEGRO_ALIGN_RIGHT, name_str);
    al_draw_text(global->font, colors[i], center + gap,
                 y, ALLEGRO_ALIGN_LEFT, points_str);
  }
  LOG(1, "Selection in draw_scoreboard: %d", *selection);

  al_use_transform(&transform);
  al_flip_display();
}

int register_scoreboard_events() {
  LOG(1, "Registering scoreboard events");
  al_register_event_source(global->queue, al_get_keyboard_event_source());
  al_register_event_source(global->queue,
                           al_get_timer_event_source(global->timer));
  al_register_event_source(global->queue,
                           al_get_display_event_source(global->disp));
  LOG(1, "Registered scoreboard events");
  return 1;
}

void keys_for_scoreboard(int *selection, short options_num) {
  LOG(1, "%d", *selection);
  if (global->event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
    (*selection)++;
  }

  if (global->event.keyboard.keycode == ALLEGRO_KEY_UP) {
    (*selection)--;
  }

  if (global->event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
    gameState = MENU;
  }

  if (*selection < 0)
    *selection = 0;
  else if (*selection > options_num - 1)
    *selection = options_num - 1;
}

sqlite3 *open_db() {
  sqlite3 *db;
  int rc;

  rc = sqlite3_open("blasteroids.db", &db);
  if (rc != SQLITE_OK) {
    error((char *)sqlite3_errmsg(db));
    sqlite3_close(db);
    return NULL;
  }

  const char *create_sql = "CREATE TABLE IF NOT EXISTS scores ("
                           "  id    INTEGER PRIMARY KEY AUTOINCREMENT,"
                           "  name  TEXT    NOT NULL,"
                           "  score INTEGER NOT NULL"
                           ");";

  rc = sqlite3_exec(db, create_sql, NULL, NULL, NULL);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
  }

  return db;
};

int write_score(Score *score) {
  sqlite3 *db = open_db();
  sqlite3_stmt *stmt;
  int rc;

  const char *insert_sql = "INSERT INTO scores (name, score) VALUES (?, ?);";

  rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    error((char *)sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
  }

  sqlite3_bind_text(stmt, 1, score->name, -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 2, score->points);
  sqlite3_step(stmt);
  sqlite3_reset(stmt);
  sqlite3_close(db);
  return 0;
}

Score *get_all_scores(int *count) {
  sqlite3 *db = open_db();
  sqlite3_stmt *stmt;
  int rc;

  const char *sql = "SELECT * FROM scores ORDER BY score DESC;";

  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    error((char *)sqlite3_errmsg(db));
    sqlite3_close(db);
    return NULL;
  }

  Score *scores = NULL;
  *count = 0;

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    scores = realloc(scores, (*count + 1) * sizeof(Score));
    scores[*count].name = strdup((char *)sqlite3_column_text(stmt, 1));
    scores[*count].points = sqlite3_column_int(stmt, 2);
    (*count)++;
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return scores;
}

void write_score_bin(Score *scores, int count) {
  FILE *f = fopen("blasteroids.bin", "wb");
  fwrite(&count, sizeof(int), 1, f);
  for (int i = 0; i < count; i++) {
    int len = strlen(scores[i].name) + 1;
    fwrite(&len, sizeof(int), 1, f);
    fwrite(scores[i].name, 1, len, f);
    fwrite(&scores[i].points, sizeof(int), 1, f);
  }
  fclose(f);
}

Score *get_all_scores_bin(int *count) {
  FILE *f = fopen("scores.bin", "rb");
  fread(count, sizeof(int), 1, f);
  Score *scores = malloc(*count * sizeof(Score));
  for (int i = 0; i < *count; i++) {
    int len;
    fread(&len, sizeof(int), 1, f);
    scores[i].name = malloc(len);
    fread(scores[i].name, 1, len, f);
    fread(&scores[i].points, sizeof(int), 1, f);
  }
  fclose(f);
  return scores;
}
