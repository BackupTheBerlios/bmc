#ifndef __SECTOR_H__
#define __SECTOR_H__

void add_change();

//Conversion macros - no need to do function calls for so simple maths...
#define FTI 5461.333333333f //65536/12
#define ITF    0.000183105f //12/65536
#define global_to_sector(f) (((float)(f-(int)f)+(float)((int)f%12))*FTI)
#define global_to_sector_z(z) ((int)((float)(z+2.2f)/0.025f))
/* they dont want to work on vc...i'll check it later
#define sector_to_global_x(sector,f) (((float)f*ITF)+sector%(tile_map_size_x>>2)*12.0f)
#define sector_to_global_y(sector,f) (((float)f*ITF)+sector/(tile_map_size_y>>2)*12.0f)
*/
float sector_to_global_x(int sector, Uint16 f);
float sector_to_global_y(int sector, Uint16 f);

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
#define global_to_io_intensity(intensity) (intensity*50.0f)
#define io_to_global_intensity(intensity) ((float)intensity/(float)50.0f)
#define global_to_io_interval(interval) ((float)interval/500.0f)
#define io_to_global_interval(interval) ((float)interval*500.0f)
#define global_to_io_flicker(flicker) ((float)flicker*100)
#define io_to_global_flicker(flicker) ((float)flicker/100.0f)
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
extern int current_sector;

void check_sector();

int sector_add_3do(int objectid);
int sector_add_2do(int objectid);
int sector_add_light(int objectid);
int sector_add_particle(int objectid);
int sector_add_tile(int objectid);
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

// add delete replace funcs
void add_3d_object(char *d);
void delete_3d_object(char *d);
void replace_3d_object(char *d);
void add_2d_object(char *d);
void delete_2d_object(char *d);
void replace_2d_object(char *d);
void add_lights(char *d);
void delete_light(char *d);
void add_particle(char *d);
void delete_particle(char *d);
void replace_particle(char *d);

#endif
