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

void todo_window() {

  //printf("INSERT: %d\n", insert_db("Sample Data", "Sample Description", 1, 0));
  todo_data **tdata = select_db(0);

  GtkWidget *add_new_btn = gtk_button_new_with_label("Add New");
  GtkWidget *header = create_headerbar("FernSphex Todo", 1, add_new_btn);
  GtkWidget *window = create_window("FernSphex Todo", 500, 400, header);

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
  gtk_box_set_homogeneous(GTK_BOX(box), TRUE);

  int i = 0;
  while((*(tdata+i)) != NULL) {
    GtkWidget *btn = create_bigbutton((*(tdata+i))->title, (*(tdata+i))->description);
    gtk_box_pack_start(GTK_BOX(box), btn, TRUE, FALSE, 1);
    i++;
  }

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_widget_show_all(window);
}
