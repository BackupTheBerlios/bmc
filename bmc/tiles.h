#ifndef __TILE_H__
#define __TILE_H__


extern unsigned char *tile_map;
extern unsigned char *height_map;
extern int tile_map_size_x;
extern int tile_map_size_y;
extern int tile_list[256];
extern int ground_detail_text;

int is_water_tile(int tile);
int is_reflecting(int tile);
void draw_tile_map();
void load_map_tiles();
#endif
