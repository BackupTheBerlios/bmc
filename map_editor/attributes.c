#include "global.h"

int aw_selected_object=-1;
int aw_object_type=0;

int view_attributes=0;
int attributes_x=20;
int attributes_y=100;
int attributes_x_len=240;
int attributes_y_len=180;
int attributes_win;

draw_option(int startx, int starty, char * str, int selected)
{
	draw_string(startx,starty,str,1);

	startx+=185;
	
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_LINE_LOOP);
	glVertex2i(startx,starty);
	glVertex2i(startx+15,starty);
	glVertex2i(startx+15,starty+15);
	glVertex2i(startx,starty+15);
	glEnd();

	if(selected)
		{
			glBegin(GL_LINES);
			glVertex2i(startx,starty);
			glVertex2i(startx+15,starty+15);

			glVertex2i(startx+15,starty);
			glVertex2i(startx,starty+15);
			glEnd();
		}
	
	glEnable(GL_TEXTURE_2D);
}

void display_attributes_window()
{
	if(attributes_win <= 0){
		attributes_win= create_window("attributes", 0, 0, attributes_x, attributes_y, attributes_x_len, attributes_y_len, ELW_TITLE_BAR|ELW_DRAGGABLE|ELW_USE_BACKGROUND|ELW_USE_BORDER|ELW_SHOW);
		set_window_handler(attributes_win, ELW_HANDLER_DISPLAY, &display_attributes_handler );
		set_window_handler(attributes_win, ELW_HANDLER_CLICK, &check_attributes_interface );

	} else {
		show_window(attributes_win);
		select_window(attributes_win);
	}
	display_window(attributes_win);
}

void toggle_attributes_window()
{
	if(attributes_win && windows_list.window[attributes_win].displayed)
		{
			view_attributes=0;
			if(aw_selected_object!=-1)
				{
					objects_list[aw_selected_object]->blended^=AW_BLEND;
					aw_selected_object=-1;
				}
		}
	else view_attributes=1;
	toggle_window(attributes_win);
}

int display_attributes_handler(window_info * win)
{
	//Draw the [X]
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.77f,0.57f,0.39f);
	
	glBegin(GL_LINES);
	glVertex3i(win->len_x, ELW_BOX_SIZE, 0);
	glVertex3i(win->len_x-ELW_BOX_SIZE, ELW_BOX_SIZE, 0);
	
	glVertex3i(win->len_x-ELW_BOX_SIZE, ELW_BOX_SIZE, 0);
	glVertex3i(win->len_x-ELW_BOX_SIZE, 0, 0);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	
	draw_string(win->len_x-(ELW_BOX_SIZE-4), 2, "X", 1);

	if(aw_selected_object==-1)
		{
			draw_string(15,80,"Select an object...",1);
			return 1;
		}

	draw_option(15,15,"Minable:",objects_list[aw_selected_object]->attributes&MINABLE);
	draw_option(15,35,"Pickable:",objects_list[aw_selected_object]->attributes&PICKABLE);
	draw_option(15,55,"Cuttable:",objects_list[aw_selected_object]->attributes&CUTTABLE);
	draw_option(15,75,"Diggable:",objects_list[aw_selected_object]->attributes&DIGGABLE);
	draw_option(15,95,"Usable:",objects_list[aw_selected_object]->attributes&USABLE);
	draw_option(15,115,"Use with:",objects_list[aw_selected_object]->attributes&USE_WITH);
	draw_option(15,135,"Attackable:",objects_list[aw_selected_object]->attributes&ATTACKABLE);
	draw_option(15,155,"Entrable:",objects_list[aw_selected_object]->attributes&ENTRABLE);

	return 1;
}

int check_attributes_interface(window_info * win, int mx, int my, Uint32 flags)
{
	if(my>0 && my<=20 && mx>(win->len_x-20) && mx<=win->len_x)
		{
			toggle_attributes_window();
			return 1;
		}

	if(aw_selected_object!=-1 && mx>200 && mx<215)
		{
			if(my>15&&my<30) objects_list[aw_selected_object]->attributes^=MINABLE|(objects_list[aw_selected_object]->attributes&(CUTTABLE|PICKABLE|DIGGABLE));
			if(my>35&&my<50) objects_list[aw_selected_object]->attributes^=PICKABLE|(objects_list[aw_selected_object]->attributes&(CUTTABLE|DIGGABLE|MINABLE));
			if(my>55&&my<70) objects_list[aw_selected_object]->attributes^=CUTTABLE|(objects_list[aw_selected_object]->attributes&(DIGGABLE|PICKABLE|MINABLE));
			if(my>75&&my<90) objects_list[aw_selected_object]->attributes^=DIGGABLE|(objects_list[aw_selected_object]->attributes&(CUTTABLE|PICKABLE|MINABLE));
			if(my>95&&my<110) objects_list[aw_selected_object]->attributes^=USABLE|(objects_list[aw_selected_object]->attributes&USE_WITH);
			if(my>115&&my<130) objects_list[aw_selected_object]->attributes^=USE_WITH|(objects_list[aw_selected_object]->attributes&USABLE);
			if(my>135&&my<150) objects_list[aw_selected_object]->attributes^=ATTACKABLE;
			if(my>155&&my<170) objects_list[aw_selected_object]->attributes^=ENTRABLE;
		}
	return 1;
}
