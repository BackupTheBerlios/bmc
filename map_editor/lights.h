#ifndef __LIGHTS_H__
#define __LIGHTS_H__

#define FADE 1
#define HALO 2
#define FLICKER 4

typedef struct
{
  float pos_x;
  float pos_y;
  float pos_z;
  float r;
  float g;
  float b;
  Uint8 flags;
  float intensity;
  float interval;
  light_io lightio;
}light;

typedef struct
{
  float x;
  float y;
  float z;
  float w;
}sun;


extern GLfloat light_0_position[4];
extern GLfloat light_0_diffuse[4];
extern GLfloat light_0_dist;

extern GLfloat light_1_position[4];
extern GLfloat light_1_diffuse[4];
extern GLfloat light_1_dist;

extern GLfloat light_2_position[4];
extern GLfloat light_2_diffuse[4];
extern GLfloat light_2_dist;

extern GLfloat light_3_position[4];
extern GLfloat light_3_diffuse[4];
extern GLfloat light_3_dist;

extern GLfloat light_4_position[4];
extern GLfloat light_4_diffuse[4];
extern GLfloat light_4_dist;

extern GLfloat light_5_position[4];
extern GLfloat light_5_diffuse[4];
extern GLfloat light_5_dist;

extern GLfloat light_6_position[4];
extern GLfloat light_6_diffuse[4];
extern GLfloat light_6_dist;

//for the lights
#define global_lights_no 60
extern GLfloat global_lights[global_lights_no][4];
extern GLfloat sky_lights_c1[global_lights_no*2][4];
extern GLfloat sky_lights_c2[global_lights_no*2][4];
extern GLfloat sky_lights_c3[global_lights_no*2][4];
extern GLfloat sky_lights_c4[global_lights_no*2][4];

extern sun sun_pos[60*3];


#define max_lights 1000
extern light *lights_list[max_lights];
extern GLuint halo_tex;

extern char lights_on;
extern unsigned char light_level;
extern int game_minute;

void draw_light_halos();
void draw_light_halo(light * l);
void draw_test_light();
void disable_local_lights();
void enable_local_lights();
void draw_lights();
int add_light(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat intensity, Uint8 flags, float interval);
void update_scene_lights();
void init_lights();
void reset_material();
void set_material(float r, float g, float b);
void draw_global_light();
void draw_dungeon_light();
void make_gradient_light(int start,int steps,float *light_table, float r_start, float g_start, float b_start, float r_end, float g_end, float b_end);
void build_global_light_table();
void build_sun_pos_table();
void new_minute();

#endif
