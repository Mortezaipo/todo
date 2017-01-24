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
//FernSphex Todo Widget Library.
#include "todo.h"

// Create Window form.
GtkWidget *
create_window(char *title, int width, int height, GtkWidget *header) {
  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title(GTK_WINDOW(window), title);
  gtk_window_set_default_size(GTK_WINDOW(window), width, height);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  if (header != NULL) {
    gtk_window_set_titlebar(GTK_WINDOW(window), header);
  }

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  return window;
}

// Create Window Header Bar widget.
GtkWidget *
create_headerbar(char *title, int items_count, ...) {
  GtkWidget *headerbar;
  headerbar = gtk_header_bar_new();
  gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), title);
  gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), TRUE);

  va_list btns;
  va_start(btns, items_count);
  for(int i = 0; i < items_count; i++) {
    gtk_header_bar_pack_start(GTK_HEADER_BAR(headerbar), va_arg(btns, GtkWidget *));
  }
  va_end(btns);

  return headerbar;
}

// Create simple Button widget which has just title.
GtkWidget *
create_button(char *title) {
  GtkWidget *btn;
  btn = gtk_button_new_with_label(title);
  return btn;
}

// Create big Button widget which has title & description.
GtkWidget *
create_bigbutton(char *title, char *description) {
  GtkWidget *btn;
  GtkWidget *title_lbl;
  GtkWidget *description_lbl;
  GtkWidget *box;

  char *markup_title = malloc(strlen(title) + 18);
  sprintf(markup_title, "<big><b>%s</b></big>", title);

  btn = gtk_button_new();
  title_lbl = gtk_label_new(NULL);
  description_lbl = gtk_label_new(description);
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

  gtk_label_set_markup(GTK_LABEL(title_lbl), markup_title);
  gtk_label_set_xalign(GTK_LABEL(title_lbl), 0);
  gtk_label_set_xalign(GTK_LABEL(description_lbl), 0);

  gtk_box_pack_start(GTK_BOX(box), title_lbl, TRUE, TRUE, 1);
  gtk_box_pack_start(GTK_BOX(box), description_lbl, TRUE, TRUE, 1);
  gtk_container_add(GTK_CONTAINER(btn), box);

  return btn;
}
