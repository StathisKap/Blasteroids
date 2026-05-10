#ifndef INCLUDE_SCORE_H_
#define INCLUDE_SCORE_H_

typedef struct Score {
  char *name;
  int points;
} Score;


int scoreboard();
void init_scoreboard();
void draw_scoreboard(int *selection, Score *scores, short scores_num);
int register_scoreboard_events();
void keys_for_scoreboard(int *selection, short options_num);

int write_score(Score *score);
Score *get_all_scores(int *count);
void write_score_bin(Score *scores, int count);
Score *get_all_scores_bin(int *count);
#endif // INCLUDE_SCORE_H_
