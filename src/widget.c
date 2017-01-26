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
create_window(char *title, int width, int height, GtkWidget *header, bool enable_scrolling, bool is_parent) {
  GtkWidget *window;
  void *tmp = NULL;
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title(GTK_WINDOW(window), title);
  gtk_window_set_default_size(GTK_WINDOW(window), width, height);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  if (is_parent == TRUE) {
    gtk_window_set_default_icon_from_file("todo.png", NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  } else {
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
  }

  if (header != NULL) {
    gtk_window_set_titlebar(GTK_WINDOW(window), header);
  }

  if(enable_scrolling == TRUE) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    GtkWidget *scroll_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    GtkWidget *window_scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_box_pack_start(GTK_BOX(box), window_scroll, TRUE, TRUE, 1);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(window_scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    gtk_container_set_border_width(GTK_CONTAINER(window_scroll), 10);
    gtk_container_add(GTK_CONTAINER(window_scroll), scroll_box);
    tmp = (void *)scroll_box;
  } else {
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    tmp = (void *)window;
  }
  gtk_widget_show_all(window);
  return (GtkWidget *)tmp;
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

// Create Input widget.
GtkWidget *
create_input(char *placeholder, char *value, bool is_multiline, int max_length) {
  GtkWidget *entry;
  if(is_multiline == FALSE) {
    //Single line input
    entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry), max_length);
    if(placeholder != NULL)
      gtk_entry_set_placeholder_text(GTK_ENTRY(entry), placeholder);
    if(value != NULL)
      gtk_entry_set_text(GTK_ENTRY(entry), value);
  } else {
    //Multi line input
    entry = gtk_text_view_new();

    gtk_widget_set_size_request(entry, 450, 300);
    gtk_text_view_set_border_window_size(GTK_TEXT_VIEW(entry), GTK_TEXT_WINDOW_LEFT, 1);
    gtk_text_view_set_border_window_size(GTK_TEXT_VIEW(entry), GTK_TEXT_WINDOW_RIGHT, 1);
    gtk_text_view_set_border_window_size(GTK_TEXT_VIEW(entry), GTK_TEXT_WINDOW_TOP, 1);
    gtk_text_view_set_border_window_size(GTK_TEXT_VIEW(entry), GTK_TEXT_WINDOW_BOTTOM, 1);

    gtk_text_view_set_accepts_tab(GTK_TEXT_VIEW(entry), TRUE);

    char *default_value = (value!=NULL)?value:placeholder;
    if (default_value != NULL) {
      GtkTextBuffer *bd = gtk_text_buffer_new(NULL);
      gtk_text_buffer_set_text(bd, default_value, strlen(default_value));
      gtk_text_view_set_buffer(GTK_TEXT_VIEW(entry), bd);
    }
  }

  return entry;
}

// Create Checkbox widget.
GtkWidget *
create_switchbox(bool is_active) {
  GtkWidget *switchbox;
  switchbox = gtk_switch_new();
  if(is_active == TRUE)
    gtk_switch_set_active(GTK_SWITCH(switchbox), TRUE);
  return switchbox;
}

// Create Label widget.
GtkWidget *
create_label(char *text) {
  GtkWidget *label;
  label = gtk_label_new(text);
  return label;
}
