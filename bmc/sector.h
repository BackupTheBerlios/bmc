#ifndef __SECTOR_H__
#define __SECTOR_H__

typedef struct{
	Uint32 objects_checksum;
	Uint32 tiles_checksum;
	short e3d_local[100];
	short e2d_local[20];
	short lights_local[4];
	short particles_local[8];
}map_sector;

extern map_sector *sectors;
extern int num_sectors;
extern Uint16 active_sector;

Uint16 global_to_sector(float f);
float sector_to_global_x(int sector, Uint16 f);
float sector_to_global_y(int sector, Uint16 f);
int sector_get(float x, float y);
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
int sector_get(float x, float y);
void sector_update_checksums(int sector);
void sector_update_objects_checksum(int sector);
void sector_update_tiles_checksum(int sector);

void get_tile_data(char *d);
void get_3d_objects(char *d);
void get_2d_objects(char *d);
void get_light_objects(char *d);
void get_particle_objects(char *d);
#endif
