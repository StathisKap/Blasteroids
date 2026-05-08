#ifndef INCLUDE_SCORE_H_
#define INCLUDE_SCORE_H_

typedef struct Score {
  char *name;
  int points;
} Score;

int write_score(Score *score);
Score *get_all_scores(int *count);
void write_score_bin(Score *scores, int count);
Score *get_all_scores_bin(int *count);
#endif // INCLUDE_SCORE_H_
