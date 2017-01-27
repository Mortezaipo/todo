/* ============================================================
                      FernSphex Todo
                  Todo Tracking Software
Copyright (C) 2016  Morteza Nourelahi Alamdari (Mortezaipo)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
============================================================ */
//FernSphex Todo Database Library.
#include "todo.h"

// Database open connection
sqlite3 *
open_db() {
  sqlite3 *db;
  char *db_file = malloc(strlen(home_dir()) + 19);
  sprintf(db_file, "%s/fernsphex_todo.db", home_dir());
  int connection = sqlite3_open(db_file, &db);
  if (connection != SQLITE_OK)
    return NULL;
  return db;
}

// Database close connection
void
close_db(sqlite3 *db) {
  if(db != NULL)
    sqlite3_close(db);
}

// Add new data
int
insert_db(char *title, char *description, int is_done, int is_important) {
  sqlite3 *db = open_db();
  sqlite3_stmt *res;
  int inserted_id = -1;
  if (db == NULL) {
    return -1;
  }

  char *sql_query = "INSERT INTO todo (title, description, is_done, is_important) VALUES (?, ?, ?, ?)";

  if(sqlite3_prepare_v2(db, sql_query, -1, &res, NULL) != SQLITE_OK) {
    close_db(db);
    return -1;
  }

  if(sqlite3_bind_text(res, 1, title, strlen(title), NULL) != SQLITE_OK) {
    close_db(db);
    return -1;
  }
  if(sqlite3_bind_text(res, 2, description, strlen(description), NULL) != SQLITE_OK) {
    close_db(db);
    return -1;
  }
  if(sqlite3_bind_int(res, 3, is_done) != SQLITE_OK) {
    close_db(db);
    return -1;
  }
  if(sqlite3_bind_int(res, 4, is_important) != SQLITE_OK) {
    close_db(db);
    return -1;
  }

  if(sqlite3_step(res) != SQLITE_DONE) {
    fprintf(stderr, "ERROR ON INSERT! %s", sqlite3_errmsg(db));
    close_db(db);
    return -1;
  }
  sqlite3_finalize(res);
  inserted_id = sqlite3_last_insert_rowid(db);
  close_db(db);
  return inserted_id;
}

// Select query callback.
static int
select_db_callback(void *count, int argc, char **argv, char **col_name) {
  int *c = count;
  *c = atoi(argv[0]);
  return 0;
}

// Fetch data
todo_data  **
select_db(int id) {
  sqlite3 *db = open_db();
  sqlite3_stmt *stmt = NULL;
  todo_data **db_rows = NULL;
  int pq;
  int rows_count = 0;
  char *sql_query = NULL;
  if (db == NULL) {
    return NULL;
  }

  if(id != 0) {
    sql_query = malloc((sizeof(char) * 28) + sizeof(id));
    sprintf(sql_query, "SELECT * FROM todo WHERE id=%d;", id);
    db_rows = malloc(sizeof(todo_data *) + 1);
  } else {
    sql_query = malloc(sizeof(char) * 18);
    sql_query = "SELECT * FROM todo;";
    if(sqlite3_exec(db, "SELECT COUNT(*) FROM todo;", select_db_callback, &rows_count, NULL) != SQLITE_OK) {
      close_db(db);
      return NULL;
    }
    db_rows = malloc(sizeof(todo_data *) * (rows_count + 1));
  }

  if(sqlite3_prepare_v2(db, sql_query, -1, &stmt, NULL) != SQLITE_OK) {
    close_db(db);
    return NULL;
  }

  int row_index = 0;
  pq = sqlite3_step(stmt);
  while(pq != SQLITE_DONE && pq != SQLITE_OK) {

    *(db_rows + row_index) = malloc(sizeof(todo_data));

    const unsigned int id = sqlite3_column_int(stmt, 0);
    (*(db_rows + row_index))->id = id;

    const unsigned char *title = sqlite3_column_text(stmt, 1);
    if(title != NULL) {
      (*(db_rows + row_index))->title = malloc(sizeof(char *) * ((int)strlen(title)+1));
      strncpy((*(db_rows + row_index))->title, title, (int)strlen(title)+1);
    }
    const unsigned char *description = sqlite3_column_text(stmt, 2);
    if(description != NULL) {
      (*(db_rows + row_index))->description = malloc(sizeof(char *) * ((int)strlen(description)+1));
      strncpy((*(db_rows + row_index))->description, description, (int)strlen(description)+1);
    }
    const unsigned int is_done = sqlite3_column_int(stmt, 3);
    (*(db_rows + row_index))->is_done = is_done;

    const unsigned int is_important = sqlite3_column_int(stmt, 4);
    (*(db_rows + row_index))->is_important = is_important;

    row_index++;
    pq = sqlite3_step(stmt);
  }
  *(db_rows+row_index) = NULL;

  sqlite3_finalize(stmt);
  close_db(db);
  return db_rows;
}
