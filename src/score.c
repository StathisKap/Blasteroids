#ifndef SCORE_
#define SCORE_
#include "../include/blasteroids.h"
#include "../include/score.h"
#include <sqlite3.h>
#include <stdio.h>
#endif

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

int write_score(char *name, int points) {
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

  sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 2, points);
  sqlite3_step(stmt);
  sqlite3_reset(stmt);
  sqlite3_close(db);
  return 0;
}

Score *get_all_scores(int *count) {
  sqlite3 *db = open_db();
  sqlite3_stmt *stmt;
  int rc;

  const char *sql = "SELECT * FROM scores;";

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
      scores[*count].name   = strdup((char *)sqlite3_column_text(stmt, 1));
      scores[*count].points = sqlite3_column_int(stmt, 2);
      (*count)++;
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return scores;
}
