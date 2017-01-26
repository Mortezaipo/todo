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
// New Todo Window

#include "todo.h"

void todo_detail_window(int todo_id) {
  GtkWidget *save_btn = create_button("Save");
  GtkWidget *header = create_headerbar("New Todo", 1, save_btn);
  GtkWidget *window = create_window("New Todo", 500, 430, header, FALSE, FALSE);

  char *title_data = NULL;
  char *description_data = NULL;
  bool is_done_data = FALSE;
  bool is_important_data = FALSE;
  // Look for data in database
  if(todo_id != 0) {
    todo_data **db_row = select_db(todo_id);
    if(*db_row != NULL) {
      title_data = (*(db_row))->title;
      description_data = (*(db_row))->description;
      is_done_data = ((*(db_row))->is_done == 1)?TRUE:FALSE;
      is_important_data = ((*(db_row))->is_important == 1)?TRUE:FALSE;
    }
  }

  GtkWidget *title = create_input("Todo Title", title_data, FALSE, 50);
  GtkWidget *description = create_input("Todo Description", description_data, TRUE, 1000);

  // Switches for is_done & is_important items.
  GtkWidget *is_done_lbl = create_label("Is todo done?");
  GtkWidget *is_important_lbl = create_label("Is todo important?");
  GtkWidget *is_done = create_switchbox(is_done_data);
  GtkWidget *is_important = create_switchbox(is_important_data);

  GtkWidget *is_done_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
  gtk_box_set_homogeneous(GTK_BOX(is_done_box), FALSE);
  gtk_box_pack_start(GTK_BOX(is_done_box), is_done_lbl, FALSE, FALSE, 1);
  gtk_box_pack_start(GTK_BOX(is_done_box), is_done, FALSE, FALSE, 1);

  GtkWidget *is_important_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
  gtk_box_set_homogeneous(GTK_BOX(is_important_box), FALSE);
  gtk_box_pack_start(GTK_BOX(is_important_box), is_important_lbl, FALSE, FALSE, 1);
  gtk_box_pack_start(GTK_BOX(is_important_box), is_important, FALSE, FALSE, 1);

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
  gtk_box_pack_start(GTK_BOX(box), title, TRUE, TRUE, 1);
  gtk_box_pack_start(GTK_BOX(box), description, TRUE, TRUE, 1);
  gtk_box_pack_start(GTK_BOX(box), is_done_box, TRUE, TRUE, 1);
  gtk_box_pack_start(GTK_BOX(box), is_important_box, TRUE, TRUE, 1);

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_widget_show_all(window);
}
