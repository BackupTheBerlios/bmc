#include "global.h"

int seeds_displayed=0;
int cur_displayed_seeds_list[ITEM_NUM_ITEMS];

void rendergrid(int columns, int rows, int left, int top, int width, int height)
{
	int x, y;
	int temp;
	
	glBegin(GL_LINES);

	for(y=0; y<=rows; y++){
		temp = top + y * height;
		glVertex2i(left,         temp);
		glVertex2i(left + width*columns, temp);
	}
		       
	for(x=0; x<columns+1; x++){
		temp = left + x * width;
		glVertex2i(temp, top);
		glVertex2i(temp, top + height*rows);
	}
	
	glEnd();
}

int get_mouse_pos_in_grid(int mx, int my, int columns, int rows, int left, int top, int width, int height)
{
	int x, y, i=0;

	mx-=left;
	my-=top;
	columns*=width;
	rows*=height;
	
	for(y=0; y<=rows; y+=height){
		for(x=0; x<=columns; x+=width, i++){
			if(mx>=x && mx<=x+width && my>=y && my<=y+height)
				return i;
		}
	}

	return -1;
}

inline GLuint get_items_texture(int no)
{
	GLuint retval=-1;
	
	switch(no){
		case 0:
			retval=items_text_1;
			break;
		case 1:
			retval=items_text_2;
			break;
		case 2:
			retval=items_text_3;
			break;
		case 3:
			retval=items_text_4;
			break;
		case 4:
			retval=items_text_5;
			break;
		case 5:
			retval=items_text_6;
			break;
		case 6:
			retval=items_text_7;
			break;
		case 7:
			retval=items_text_8;
			break;
		case 8:
			retval=items_text_9;
			break;
	}

	return retval;
}

int display_seeds_handler(window_info *win)
{
	int i;
	seeds_displayed=0;
	
	glColor3f(0.77f,0.57f,0.39f);
	glDisable(GL_TEXTURE_2D);
	
	rendergrid(12, 3, 10, 10, 33, 33);
	
	glColor3f(1.0f,1.0f,1.0f);
	glEnable(GL_TEXTURE_2D);

	for(i=0;i<ITEM_NUM_ITEMS;i++){
		if(item_list[i].is_seed && item_list[i].quantity>0){
			float u_start, v_start, u_end, v_end;
			int x_start, x_end, y_start, y_end;
			int cur_item;
			GLuint this_texture;

			cur_item=item_list[i].image_id%25;
			u_start=0.2f*(cur_item%5);
			u_end=u_start+(float)50/256;
			v_start=(1.0f+((float)50/256)/256.0f)-((float)50/256*(cur_item/5));
			v_end=v_start-(float)50/256;

			this_texture=get_items_texture(item_list[i].image_id/25);

			if(this_texture!=-1) get_and_set_texture_id(this_texture);

			x_start=seeds_displayed*33+11;
			x_end=x_start+32;
			y_start=(seeds_displayed/12)*33+10;
			y_end=y_start+32;
			
			glBegin(GL_QUADS);
			draw_2d_thing(u_start,v_start,u_end,v_end,x_start,y_start,x_end,y_end);
			glEnd();

			cur_displayed_seeds_list[seeds_displayed]=i;
			
			seeds_displayed++;
		}
	}

	return 1;
}

int click_seeds_handler(window_info *win, int mx, int my, Uint32 flags)
{
	char str[2];
	int pos=get_mouse_pos_in_grid(mx, my, 12, 3, 10, 10, 33, 33);

	if(pos==-1||pos>=seeds_displayed) return 1;

	if(right_click){
		str[0]=LOOK_AT_INVENTORY_ITEM;
	} else if (left_click) {
		str[0]=PLANT_SEED;
	} else return 1;
	
	str[1]=item_list[cur_displayed_seeds_list[pos]].pos;
	
	my_tcp_send(my_socket, str, 2);
	
	return 1;
}

int seeds_win=-1;
int seeds_menu_x=100;
int seeds_menu_y=100;
int seeds_menu_x_len=440;
int seeds_menu_y_len=120;

void display_seeds_window()
{
	if(seeds_win < 0){
		seeds_win= create_window("Seeds", 0, 0, seeds_menu_x, seeds_menu_y, seeds_menu_x_len, seeds_menu_y_len, ELW_WIN_DEFAULT);
		set_window_handler(seeds_win, ELW_HANDLER_DISPLAY, &display_seeds_handler );
		set_window_handler(seeds_win, ELW_HANDLER_CLICK, &click_seeds_handler );
	} else {
		toggle_window(seeds_win);
	}
}


