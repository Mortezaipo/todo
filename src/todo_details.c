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

void
save_todo(GtkWidget *btn, gpointer data) {
  printf("ID: %d\n", 10);
}

void
delete_todo(GtkWidget *btn, gpointer sd) {
  if (delete_db(((signal_data *)sd)->id) == TRUE) {
    gtk_widget_destroy(((signal_data *)sd)->btn);
    gtk_widget_show_all(((signal_data *)sd)->box);
  }
}

void todo_details_window(signal_data *sd) {
  GtkWidget *save_btn = create_button("Save");
  GtkWidget *header;
  char *window_title = (sd == NULL)?"New Todo":"Edit Todo";
  if(sd == NULL) {
    header = create_headerbar(window_title, 1, save_btn);
  } else {
    GtkWidget *delete_btn = create_button("Delete");
    header = create_headerbar(window_title, 2, save_btn, delete_btn);
    g_signal_connect(delete_btn, "clicked", G_CALLBACK(delete_todo), sd);
  }

  GtkWidget *window = create_window("New Todo", 500, 430, header, FALSE, FALSE);

  char *title_data = NULL;
  char *description_data = NULL;
  bool is_done_data = FALSE;
  bool is_important_data = FALSE;
  // Look for data in database
  if(sd != NULL) {
    todo_data **db_row = select_db(sd->id);
    if(*db_row != NULL) {
      title_data = (*(db_row))->title;
      description_data = (*(db_row))->description;
      is_done_data = ((*(db_row))->is_done == 1)?TRUE:FALSE;
      is_important_data = ((*(db_row))->is_important == 1)?TRUE:FALSE;
    }
  }

  GtkWidget *title = create_input("Todo Title", title_data, FALSE, 50);
  GtkWidget *description = create_input("Todo Description", description_data, TRUE, 1000);
  //GtkWidget *input_description = gtk_text_view_get_buffer(description);

  // Switches for is_done & is_important items.
  GtkWidget *is_done_lbl = create_label("Is todo done?");
  GtkWidget *is_important_lbl = create_label("Is todo important?");
  GtkWidget *is_done = create_switchbox(is_done_data);
  GtkWidget *is_important = create_switchbox(is_important_data);

  gtk_label_set_xalign(GTK_LABEL(is_done_lbl), 0);
  GtkWidget *is_done_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
  gtk_box_set_homogeneous(GTK_BOX(is_done_box), FALSE);
  gtk_box_pack_start(GTK_BOX(is_done_box), is_done_lbl, TRUE, TRUE, 1);
  gtk_box_pack_start(GTK_BOX(is_done_box), is_done, FALSE, FALSE, 1);

  gtk_label_set_xalign(GTK_LABEL(is_important_lbl), 0);
  GtkWidget *is_important_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
  gtk_box_set_homogeneous(GTK_BOX(is_important_box), FALSE);
  gtk_box_pack_start(GTK_BOX(is_important_box), is_important_lbl, TRUE, TRUE, 1);
  gtk_box_pack_start(GTK_BOX(is_important_box), is_important, FALSE, FALSE, 1);

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
  gtk_box_pack_start(GTK_BOX(box), title, TRUE, TRUE, 1);
  gtk_box_pack_start(GTK_BOX(box), description, TRUE, TRUE, 1);
  gtk_box_pack_start(GTK_BOX(box), is_done_box, TRUE, TRUE, 1);
  gtk_box_pack_start(GTK_BOX(box), is_important_box, TRUE, TRUE, 1);

  todo_data *input_data = malloc(sizeof(todo_data));
  input_data->id = sd->id;
  // input_data->title = gtk_entry_get_text(title);
  //input_data->description = gtk_text_buffer_get_text(description_input);
  input_data->is_done = gtk_switch_get_active(GTK_SWITCH(is_done));
  input_data->is_important = gtk_switch_get_active(GTK_SWITCH(is_important));
  g_signal_connect(save_btn, "clicked", G_CALLBACK(save_todo), input_data);

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_widget_show_all(window);
}
