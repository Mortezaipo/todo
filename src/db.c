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

//Database open connection
sqlite3 *open_db() {
  sqlite3 *db;
  char *db_file = malloc(strlen(home_dir()) + 19);
  sprintf(db_file, "%s/fernsphex_todo.db", home_dir());
  int connection = sqlite3_open(db_file, &db);
  if (connection != SQLITE_OK)
    return NULL;
  return db;
}

//Database close connection
void close_db(sqlite3 *db) {
  if(db != NULL)
    sqlite3_close(db);
}

//Add new data
int insert_db(char *title, char *description, int is_done, int is_important) {
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
