#ifndef __MAP_IO_H__
#define __MAP_IO_H__

typedef struct
{
	Uint16 object_type;//the object index
	Uint16 x_pos;
	Uint16 y_pos;
	Sint8 z_pos;
	Uint8 x_rot;
	Uint8 y_rot;
	Uint8 z_rot;
	Uint8 flags;//self_lit or blended
	Uint8 r,g,b;//real color (float) is 255/color
}object3d_io;

typedef struct
{
	Uint16 object_type;//the object index
	Uint16 x_pos;
	Uint16 y_pos;
	Sint8 z_pos;
	Uint8 x_rot;
	Uint8 y_rot;
	Uint8 z_rot;
}obj_2d_io;

typedef struct
{
	Uint16 x_pos;
	Uint16 y_pos;
	Sint8 z_pos;
	Uint8 r,g,b;//real color (float) is 255/color
	Uint8 flags;//flags
}light_io;

typedef struct
{
	Uint16 object_type;
	Uint16 x_pos;
	Uint16 y_pos;
	Sint8 z_pos;
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
	int reserved_10;
	int reserved_11;
	int reserved_12;
	int reserved_13;
	int reserved_14;
	int reserved_15;
	int reserved_16;
	int reserved_17;
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

#endif
