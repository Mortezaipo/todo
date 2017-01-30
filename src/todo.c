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
//FernSphex Todo Window Form.
#include "todo.h"

void
todo_details(GtkWidget *btn, gpointer sd) {
    todo_details_window((signal_data *)sd);
}

void
todo_window() {
  todo_data **tdata = select_db(0);

  GtkWidget *add_new_btn = create_button("Add New", "button_success");
  GtkWidget *header = create_headerbar("FernSphex Todo", 1, add_new_btn);
  GtkWidget *window = create_window("FernSphex Todo", 500, 400, header, TRUE, TRUE);

  main_window_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
  gtk_box_set_homogeneous(GTK_BOX(main_window_box), TRUE);

  signal_data *sdn = malloc(sizeof(signal_data));
  sdn->btn = add_new_btn;
  sdn->box = main_window_box;
  sdn->id = 0;
  strcpy(sdn->action, "new");
  g_signal_connect(G_OBJECT(add_new_btn), "clicked", G_CALLBACK(todo_details), sdn);

  signal_data *sd;
  int i = 0;
  if(*tdata == NULL)
    show_no_todo_alert();

  while((*(tdata+i)) != NULL) {
    GtkWidget *btn = create_bigbutton((*(tdata+i))->title, (*(tdata+i))->description, "todo_item");
    sd = malloc(sizeof(signal_data));
    sd->btn = btn;
    sd->box = main_window_box;
    sd->id = ((*(tdata+i))->id);
    strcpy(sd->action, "edit");
    g_signal_connect(G_OBJECT(btn), "clicked", G_CALLBACK(todo_details), sd);
    gtk_box_pack_start(GTK_BOX(main_window_box), btn, TRUE, FALSE, 1);
    //free(sd);
    i++;
  }

  gtk_container_add(GTK_CONTAINER(window), main_window_box);
  gtk_widget_show_all(window);
}
