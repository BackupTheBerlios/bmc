#ifndef __ATTRIBUTES_H__
#define __ATTRIBUTES_H__

#include "global.h"

#define AW_BLEND 2

extern int attributes_win;
extern int aw_selected_object;
extern int aw_object_type;

void display_attributes_window();
int display_attributes_handler(window_info * win);
int check_attributes_interface(window_info * win, int mx, int my, Uint32 flags);
void draw_checkbox(int startx, int starty, int selected);
void toggle_attributes_window();


#endif
