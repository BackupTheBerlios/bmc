#ifndef __SEEDS_H__
#define __SEEDS_H__

extern int seeds_win;

inline void rendergrid(int columns, int rows, int left, int top, int width, int height);
inline int get_mouse_pos_in_grid(int mx, int my, int columns, int rows, int left, int top, int width, int height);
inline GLuint get_items_texture(int no);
void display_seeds_window();

#endif
