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

#endif
