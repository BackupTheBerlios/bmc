#ifndef __SECTOR_H__
#define __SECTOR_H__

//Conversion macros - no need to do function calls for so simple maths...
#define FTI 5461.333333333f //65536/12
#define ITF    0.000183105f //12/65536
#define global_to_sector(f) (((float)(f-(int)f)+(float)((int)f%12))*FTI)
#define global_to_sector_z(z) ((int)((float)(z+2.2f)/0.025f))
#define sector_to_global_x(sector,f) (((float)f*ITF)+sector%(tile_map_size_x>>2)*12.0f)
#define sector_to_global_y(sector,f) (((float)f*ITF)+sector/(tile_map_size_y>>2)*12.0f)
#define sector_to_global_z_step(z) (z*0.025f)
#define sector_to_global_z(z) ((float)sector_to_global_z_step(z)-2.2f)
#define sector_to_global_rot(rot) ((float)rot*1.5f)
#define global_to_sector_rot(rot) ((float)rot/1.5f)
#define sector_to_global_rgb(rgb) ((float)rgb/255.0f)
#define global_to_sector_rgb(rgb) (rgb*255)
#define global_to_sector_selflit(selflit) (selflit<<0)
#define global_to_sector_blended(blended) (blended<<1)
#define sector_to_global_selflit(flags) (flags&0x01)
#define sector_to_global_blended(flags) (flags&0x02)
#define sector_get(x,y) (((int)y/12)*(tile_map_size_x>>2)+(int)x/12)
#define fast_reconv_x(x,y) (sector_to_global_x(sector_get(x,y),((int)global_to_sector(x))))
#define fast_reconv_y(x,y) (sector_to_global_y(sector_get(x,y),((int)global_to_sector(y))))
#define fast_reconv_z(z) (sector_to_global_z(global_to_sector_z(z)))
#define fast_reconv_rot(rot) (sector_to_global_rot((int)global_to_sector_rot(rot)))

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
void sector_update_checksums(int sector);
void sector_update_objects_checksum(int sector);
void sector_update_tiles_checksum(int sector);

void get_checksums(char *d, int sector);
void get_tile_data(char *d);
void get_3d_objects(char *d);
void get_2d_objects(char *d);
void get_light_objects(char *d);
void get_particle_objects(char *d);
void get_3d_objects_full_rotation(char *d);

void send_superchecksum(int sector);
void update_sector_objects(Uint16 sector);
void update_sector_tiles(Uint16 sector);

#endif
