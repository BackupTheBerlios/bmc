#ifndef __TERRAFORM_H__
#define __TERRAFORM_H__

#define translate_coords(x,y) ((int)y/3*tile_map_size_x+(int)x/3)

void terraform(int tile_pos, int type);

#endif
