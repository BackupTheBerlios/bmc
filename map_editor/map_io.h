#ifndef __MAP_IO_H__
#define __MAP_IO_H__

#define MINABLE 1
#define CUTTABLE 2
#define DIGGABLE 4
#define PICKABLE 8
#define USABLE 16
#define USE_WITH 32
#define ATTACKABLE 64
#define ENTRABLE 128

typedef struct
{
	Uint16 object_type;//the object index
	Uint16 x_pos;
	Uint16 y_pos;
	Uint8 z_pos;
	Uint8 x_rot;
	Uint8 y_rot;
	Uint8 z_rot;
	Uint8 flags;//self_lit, blended
	Uint8 r,g,b;//real color (float) is 255/color
	Uint32 attributes;
	Uint32 reserved_1;
	Uint32 reserved_2;
	Uint32 reserved_3;
}object3d_io;

typedef struct
{
	Uint16 object_type;//the object index
	Uint16 x_pos;
	Uint16 y_pos;
	Uint8 z_pos;
	Uint8 x_rot;
	Uint8 y_rot;
	Uint8 z_rot;
	Uint32 reserved_0;
	Uint32 reserved_1;
	Uint32 reserved_2;
	Uint32 reserved_3;
}obj_2d_io;

typedef struct
{
	Uint16 x_pos;
	Uint16 y_pos;
	Uint8 z_pos;
	Uint8 r,g,b;//real color (float) is color/50 (if > 1 it's specifies the intensity)
	Uint8 flags;//flags
	Uint8 intensity;
	Uint16 interval;
	Uint16 reserved;
	Uint32 reserved_1;
	Uint32 reserved_2;
	Uint32 reserved_3;
}light_io;

typedef struct
{
	Uint16 object_type;
	Uint16 x_pos;
	Uint16 y_pos;
	Uint8 z_pos;
	Uint32 reserved_0;
	Uint32 reserved_1;
	Uint32 reserved_2;
	Uint32 reserved_3;
}particles_io;


typedef struct
{
	char file_sig[4];//should be "bmmf", or else the map is invalid
	int tile_map_x_len;
	int tile_map_y_len;
	int tile_map_offset;
	int height_map_offset;
	int obj_3d_struct_len;
	int obj_3d_no;
	int obj_3d_offset;
	int obj_2d_struct_len;
	int obj_2d_no;
	int obj_2d_offset;
	int lights_struct_len;
	int lights_no;
	int lights_offset;
	char dungeon;//no sun
	char res_2;
	char res_3;
	char res_4;
	float ambient_r;
	float ambient_g;
	float ambient_b;
	int particles_struct_len;
	int particles_no;
	int particles_offset;
	int sector_struct_len;
	int sectors_no;
	int sectors_offset;
	int reserved_0;
	int reserved_1;
	int reserved_2;
	int reserved_3;
	int reserved_4;
	int reserved_5;
	int reserved_6;
	int reserved_7;
	int reserved_8;
	int reserved_9;
	int reserved_10;
}map_header;

extern char dungeon;//no sun
extern float ambient_r;
extern float ambient_g;
extern float ambient_b;

void destroy_map();
void sector_add_map();
int save_map(char * file_name);
int load_map(char * file_name);
void new_map(int m_x_size,int m_y_size);

int e3dlist_getid(char *name);
int e2dlist_getid(char *name);
char *e3dlist_getname(int id);
char *e2dlist_getname(int id);
int partlist_getid(char *name);
char *partlist_getname(int id);
#endif
