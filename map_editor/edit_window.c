#include "global.h"

int view_edit_window=0;
int edit_window_x=20;
int edit_window_y=100;
int edit_window_x_len=560;
int edit_window_y_len=170;
int edit_window_win=0;

int ew_selected_object=-1;
int ew_object_type=-1;
int g1_x1=158,g1_x2=172,g1_y1=13,g1_y2=27;
int g2_x1=180,g2_x2=194,g2_y1=13,g2_y2=27;
int g3_x1=158,g3_x2=172,g3_y1=33,g3_y2=47;
int g4_x1=180,g4_x2=194,g4_y1=33,g4_y2=47;
int g5_x1=158,g5_x2=172,g5_y1=53,g5_y2=67;
int g6_x1=180,g6_x2=194,g6_y1=53,g6_y2=67;

int g7_x1=158,g7_x2=172,g7_y1=83,g7_y2=97;
int g8_x1=180,g8_x2=194,g8_y1=83,g8_y2=97;
int g9_x1=158,g9_x2=172,g9_y1=103,g9_y2=117;
int g10_x1=180,g10_x2=194,g10_y1=103,g10_y2=117;
int g11_x1=158,g11_x2=172,g11_y1=123,g11_y2=137;
int g12_x1=180,g12_x2=194,g12_y1=123,g12_y2=137;

int g13_x1=378,g13_x2=392,g13_y1=13,g13_y2=27;
int g14_x1=400,g14_x2=414,g14_y1=13,g14_y2=27;
int g15_x1=378,g15_x2=392,g15_y1=33,g15_y2=47;
int g16_x1=400,g16_x2=414,g16_y1=33,g16_y2=47;
int g17_x1=378,g17_x2=392,g17_y1=53,g17_y2=67;
int g18_x1=400,g18_x2=414,g18_y1=53,g18_y2=67;

int g19_x1=378,g19_x2=392,g19_y1=83,g19_y2=97;
int g20_x1=378,g20_x2=392,g20_y1=103,g20_y2=117;

int g21_x1=445,g21_x2=530,g21_y1=65,g21_y2=85;

obj_2d o2t;
object3d o3t;

void display_edit_window()
{
	if(edit_window_win <= 0){
		edit_window_win= create_window("edit_window", 0, 0, edit_window_x, edit_window_y, edit_window_x_len, edit_window_y_len, ELW_WIN_DEFAULT);

		set_window_handler(edit_window_win, ELW_HANDLER_DISPLAY, &display_edit_window_handler );
		set_window_handler(edit_window_win, ELW_HANDLER_CLICK, &check_edit_window_interface );
		
	} else {
		show_window(edit_window_win);
		select_window(edit_window_win);
	}
	display_window(edit_window_win);
}

int display_edit_window_handler(window_info *win)
{
	char temp[100];
	glColor3f(0.77f,0.57f,0.39f);

	if(ew_selected_object!=-1 && !ew_object_type?(int)objects_list[ew_selected_object]:(int)obj_2d_list[ew_selected_object]){

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE,GL_SRC_ALPHA);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		// Drawing buttons
		glBegin(GL_LINE_LOOP);
		glVertex3i(g1_x1,g1_y1,0);
		glVertex3i(g1_x2,g1_y1,0);
		glVertex3i(g1_x2,g1_y2,0);
		glVertex3i(g1_x1,g1_y2,0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3i(g2_x1,g2_y1,0);
		glVertex3i(g2_x2,g2_y1,0);
		glVertex3i(g2_x2,g2_y2,0);
		glVertex3i(g2_x1,g2_y2,0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3i(g3_x1,g3_y1,0);
		glVertex3i(g3_x2,g3_y1,0);
		glVertex3i(g3_x2,g3_y2,0);
		glVertex3i(g3_x1,g3_y2,0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3i(g4_x1,g4_y1,0);
		glVertex3i(g4_x2,g4_y1,0);
		glVertex3i(g4_x2,g4_y2,0);
		glVertex3i(g4_x1,g4_y2,0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3i(g5_x1,g5_y1,0);
		glVertex3i(g5_x2,g5_y1,0);
		glVertex3i(g5_x2,g5_y2,0);
		glVertex3i(g5_x1,g5_y2,0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3i(g6_x1,g6_y1,0);
		glVertex3i(g6_x2,g6_y1,0);
		glVertex3i(g6_x2,g6_y2,0);
		glVertex3i(g6_x1,g6_y2,0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3i(g7_x1,g7_y1,0);
		glVertex3i(g7_x2,g7_y1,0);
		glVertex3i(g7_x2,g7_y2,0);
		glVertex3i(g7_x1,g7_y2,0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3i(g8_x1,g8_y1,0);
		glVertex3i(g8_x2,g8_y1,0);
		glVertex3i(g8_x2,g8_y2,0);
		glVertex3i(g8_x1,g8_y2,0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3i(g11_x1,g11_y1,0);
		glVertex3i(g11_x2,g11_y1,0);
		glVertex3i(g11_x2,g11_y2,0);
		glVertex3i(g11_x1,g11_y2,0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3i(g12_x1,g12_y1,0);
		glVertex3i(g12_x2,g12_y1,0);
		glVertex3i(g12_x2,g12_y2,0);
		glVertex3i(g12_x1,g12_y2,0);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex3i(g21_x1,g21_y1,0);
		glVertex3i(g21_x2,g21_y1,0);
		glVertex3i(g21_x2,g21_y2,0);
		glVertex3i(g21_x1,g21_y2,0);
		glEnd();

		if(ew_object_type==0){
			glBegin(GL_LINE_LOOP);
			glVertex3i(g9_x1,g9_y1,0);
			glVertex3i(g9_x2,g9_y1,0);
			glVertex3i(g9_x2,g9_y2,0);
			glVertex3i(g9_x1,g9_y2,0);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex3i(g10_x1,g10_y1,0);
			glVertex3i(g10_x2,g10_y1,0);
			glVertex3i(g10_x2,g10_y2,0);
			glVertex3i(g10_x1,g10_y2,0);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex3i(g13_x1,g13_y1,0);
			glVertex3i(g13_x2,g13_y1,0);
			glVertex3i(g13_x2,g13_y2,0);
			glVertex3i(g13_x1,g13_y2,0);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex3i(g14_x1,g14_y1,0);
			glVertex3i(g14_x2,g14_y1,0);
			glVertex3i(g14_x2,g14_y2,0);
			glVertex3i(g14_x1,g14_y2,0);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex3i(g15_x1,g15_y1,0);
			glVertex3i(g15_x2,g15_y1,0);
			glVertex3i(g15_x2,g15_y2,0);
			glVertex3i(g15_x1,g15_y2,0);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex3i(g16_x1,g16_y1,0);
			glVertex3i(g16_x2,g16_y1,0);
			glVertex3i(g16_x2,g16_y2,0);
			glVertex3i(g16_x1,g16_y2,0);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex3i(g17_x1,g17_y1,0);
			glVertex3i(g17_x2,g17_y1,0);
			glVertex3i(g17_x2,g17_y2,0);
			glVertex3i(g17_x1,g17_y2,0);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex3i(g18_x1,g18_y1,0);
			glVertex3i(g18_x2,g18_y1,0);
			glVertex3i(g18_x2,g18_y2,0);
			glVertex3i(g18_x1,g18_y2,0);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex3i(g19_x1,g19_y1,0);
			glVertex3i(g19_x2,g19_y1,0);
			glVertex3i(g19_x2,g19_y2,0);
			glVertex3i(g19_x1,g19_y2,0);
			glEnd();
			glBegin(GL_LINE_LOOP);
			glVertex3i(g20_x1,g20_y1,0);
			glVertex3i(g20_x2,g20_y1,0);
			glVertex3i(g20_x2,g20_y2,0);
			glVertex3i(g20_x1,g20_y2,0);
			glEnd();
		}
		glEnable(GL_TEXTURE_2D);
   


		// Drawing object info
		snprintf(temp,99,"X Pos: %03.2f",ew_object_type?obj_2d_list[ew_selected_object]->x_pos:objects_list[ew_selected_object]->x_pos);
		draw_string(10,10,temp,1);
		draw_string(160,10,"+ -",1);
		snprintf(temp,99,"Y Pos: %03.2f",ew_object_type?obj_2d_list[ew_selected_object]->y_pos:objects_list[ew_selected_object]->y_pos);
		draw_string(10,30,temp,1);
		draw_string(160,30,"+ -",1);
		snprintf(temp,99,"Z Pos: %03.2f",ew_object_type?obj_2d_list[ew_selected_object]->z_pos:objects_list[ew_selected_object]->z_pos);
		draw_string(10,50,temp,1);
		draw_string(160,50,"+ -",1);
		snprintf(temp,99,"X Rot: %03.2f",ew_object_type?obj_2d_list[ew_selected_object]->x_rot:objects_list[ew_selected_object]->x_rot);
		draw_string(10,80,temp,1);
		draw_string(160,80,"+ -",1);
		snprintf(temp,99,"Z Rot: %03.2f",ew_object_type?obj_2d_list[ew_selected_object]->z_rot:objects_list[ew_selected_object]->z_rot);
		draw_string(10,120,temp,1);
		draw_string(160,120,"+ -",1);
		snprintf(temp,99,"File Name: %s",ew_object_type?obj_2d_list[ew_selected_object]->file_name:objects_list[ew_selected_object]->file_name);
		draw_string(10,150,temp,1);
		snprintf(temp,99,"ObjectID: %d",ew_selected_object);
		draw_string(220,120,temp,1);

		draw_string(450,65,"Restore",1);

		if(ew_object_type==0){
			snprintf(temp,99,"Y Rot: %03.2f",objects_list[ew_selected_object]->y_rot);
			draw_string(10,100,temp,1);
			draw_string(160,100,"+ -",1);
			snprintf(temp,99,"Red: %01.3f",objects_list[ew_selected_object]->r);
			draw_string(220,10,temp,1);
			draw_string(380,10,"+ -",1);
			snprintf(temp,99,"Green: %01.3f",objects_list[ew_selected_object]->g);
			draw_string(220,30,temp,1);
			draw_string(380,30,"+ -",1);
			snprintf(temp,99,"Blue: %01.3f",objects_list[ew_selected_object]->b);
			draw_string(220,50,temp,1);
			draw_string(380,50,"+ -",1);
			snprintf(temp,99,"Blended: %s",objects_list[ew_selected_object]->blended?"Yes":"No");
			draw_string(220,80,temp,1);
			draw_string(380,80,"+",1);
			snprintf(temp,99,"SelfLit: %s",objects_list[ew_selected_object]->self_lit?"Yes":"No");
			draw_string(220,100,temp,1);
			draw_string(380,100,"+",1);
		
		}

		
	}
	// The X
	draw_string(0+win->len_x-16,0+2,(unsigned char *)"X",1);
	return 1;
}


int check_edit_window_interface(window_info *win, int mx, int my, Uint32 flags)
{
	int x,y;
	if(mouse_x>win->pos_x+win->len_x || mouse_x<win->pos_x
      || mouse_y<win->pos_y || mouse_y>win->pos_y+win->len_y)return 0;

   	if(view_edit_window && mouse_x>(win->pos_x+win->len_x-20) && mouse_x<=(win->pos_x+win->len_x)
	&& mouse_y>win->pos_y && mouse_y<=win->pos_y+20)
	{
		view_edit_window=0;
		return 1;
	}

	if(ew_selected_object==-1)return 0;
   x=mouse_x-win->pos_x;
   y=mouse_y-win->pos_y;
   
   if(x>g1_x1 && x<=g1_x2 && y>g1_y1 && y<=g1_y2){
		if(ew_object_type)
			obj_2d_list[ew_selected_object]->x_pos+=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
		else
			objects_list[ew_selected_object]->x_pos+=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
	}
   if(x>g2_x1 && x<=g2_x2 && y>g2_y1 && y<=g2_y2){
		if(ew_object_type)
			obj_2d_list[ew_selected_object]->x_pos-=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
		else
			objects_list[ew_selected_object]->x_pos-=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
	}
   if(x>g3_x1 && x<=g3_x2 && y>g3_y1 && y<=g3_y2){
		if(ew_object_type)
			obj_2d_list[ew_selected_object]->y_pos+=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
		else
			objects_list[ew_selected_object]->y_pos+=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
	}
   if(x>g4_x1 && x<=g4_x2 && y>g4_y1 && y<=g4_y2){
		if(ew_object_type)
			obj_2d_list[ew_selected_object]->y_pos-=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
		else
			objects_list[ew_selected_object]->y_pos-=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
	}
   if(x>g5_x1 && x<=g5_x2 && y>g5_y1 && y<=g5_y2){
		if(ew_object_type)
			obj_2d_list[ew_selected_object]->z_pos+=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
		else
			objects_list[ew_selected_object]->z_pos+=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
	}
   if(x>g6_x1 && x<=g6_x2 && y>g6_y1 && y<=g6_y2){
		if(ew_object_type)
			obj_2d_list[ew_selected_object]->z_pos-=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
		else
			objects_list[ew_selected_object]->z_pos-=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
	}

   if(x>g7_x1 && x<=g7_x2 && y>g7_y1 && y<=g7_y2){
		if(ew_object_type)
			obj_2d_list[ew_selected_object]->x_rot+=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
		else
			objects_list[ew_selected_object]->x_rot+=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
	}
   if(x>g8_x1 && x<=g8_x2 && y>g8_y1 && y<=g8_y2){
		if(ew_object_type)
			obj_2d_list[ew_selected_object]->x_rot-=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
		else
			objects_list[ew_selected_object]->x_rot-=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
	}
   if(x>g9_x1 && x<=g9_x2 && y>g9_y1 && y<=g9_y2 && !ew_object_type)objects_list[ew_selected_object]->y_rot+=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
   if(x>g10_x1 && x<=g10_x2 && y>g10_y1 && y<=g10_y2 && !ew_object_type)objects_list[ew_selected_object]->y_rot-=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
   if(x>g11_x1 && x<=g11_x2 && y>g11_y1 && y<=g11_y2){
		if(ew_object_type)
			obj_2d_list[ew_selected_object]->z_rot+=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
		else
			objects_list[ew_selected_object]->z_rot+=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
	}
   if(x>g12_x1 && x<=g12_x2 && y>g12_y1 && y<=g12_y2){
		if(ew_object_type)
			obj_2d_list[ew_selected_object]->z_rot-=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
		else
			objects_list[ew_selected_object]->z_rot-=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
	}

   if(x>g13_x1 && x<=g13_x2 && y>g13_y1 && y<=g13_y2 && !ew_object_type)objects_list[ew_selected_object]->r+=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
   if(x>g14_x1 && x<=g14_x2 && y>g14_y1 && y<=g14_y2 && !ew_object_type)objects_list[ew_selected_object]->r-=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
   if(x>g15_x1 && x<=g15_x2 && y>g15_y1 && y<=g15_y2 && !ew_object_type)objects_list[ew_selected_object]->g+=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
   if(x>g16_x1 && x<=g16_x2 && y>g16_y1 && y<=g16_y2 && !ew_object_type)objects_list[ew_selected_object]->g-=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
   if(x>g17_x1 && x<=g17_x2 && y>g17_y1 && y<=g17_y2 && !ew_object_type)objects_list[ew_selected_object]->b+=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));
   if(x>g18_x1 && x<=g18_x2 && y>g18_y1 && y<=g18_y2 && !ew_object_type)objects_list[ew_selected_object]->b-=(shift_on)?(ctrl_on?0.001:(alt_on?0.01:0.1)):(ctrl_on?100:(alt_on?10:1));

   if(x>g19_x1 && x<=g19_x2 && y>g19_y1 && y<=g19_y2 && !ew_object_type)objects_list[ew_selected_object]->blended=!objects_list[ew_selected_object]->blended;
   if(x>g20_x1 && x<=g20_x2 && y>g20_y1 && y<=g20_y2 && !ew_object_type)objects_list[ew_selected_object]->self_lit=!objects_list[ew_selected_object]->self_lit;

   if(x>g21_x1 && x<=g21_x2 && y>g21_y1 && y<=g21_y2){
	   if(ew_object_type==1)
			memcpy(obj_2d_list[ew_selected_object],&o2t,sizeof(obj_2d));
	   else
		   memcpy(objects_list[ew_selected_object],&o3t,sizeof(object3d));
   }

   return 1;
}

