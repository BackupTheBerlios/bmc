#ifndef __SECTOR_H__
#define __SECTOR_H__

typedef struct{
	int objects_checksum;
	int tiles_checksum;
	short e3d_local[100];
	short e2d_local[20];
	short lights_local[4];
	short particles_local[8];
}map_sector;

extern map_sector *sectors;
extern int num_sectors;

int sector_get(float x, float y)
{
	int sx=x/12;
	int sy=y/12;
	return sy*(tile_map_size_x>>2)+sx;
}

void sector_add_map();
int sector_add_3do(int objectid);
int sector_del_3do(int objectid);
int sector_add_2do(int objectid);
int sector_del_2do(int objectid);
int sector_add_light(int objectid);
int sector_del_light(int objectid);
int sector_add_particle(int objectid);
int sector_del_particle(int objectid);
int sector_add_tile(int objectid);
int sector_del_tile(int objectid);

#endif
