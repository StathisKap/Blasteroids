#ifndef INCLUDE_SCORE_H_
#define INCLUDE_SCORE_H_

typedef struct Score {
        char* name;
        int points;
} Score;

int write_score(char* name, int points);
Score *get_all_scores(int *count);
#endif // INCLUDE_SCORE_H_
