#include <stdio.h>
#include <string.h>
#include "global.h"

/*
TODO:

Figure out a way to handle more than 2 types of tiles. I.e. dirt + desert + grass on different sides
			Use a structure based approach?
			Hardcoded rules
Port to map editor

TBD:
Which tiles can we handle using this system?
Which 2d or 3d objects are needed to improve the usage?
*/

#define SIDE 0
#define CORNER 1

//macros for readability...
#define is_center(I)		(I==tile_pos)
#define is_northwest(I)		(I==tile_pos+tile_map_size_x-1)
#define is_north(I)		(I==tile_pos+tile_map_size_x)
#define is_northeast(I)		(I==tile_pos+tile_map_size_x+1)
#define is_east(I)		(I==tile_pos+1)
#define is_southeast(I)		(I==tile_pos-tile_map_size_x+1)
#define is_south(I)		(I==tile_pos-tile_map_size_x)
#define is_southwest(I)		(I==tile_pos-tile_map_size_x-1)
#define is_west(I)		(I==tile_pos-1)

#define get_2d_side_objects(t)\
		{get_2d_objects_match(t, SIDE);\
		if(!load_obj_2d_def_cache(object_2d_match)) load_obj_2d_def(object_2d_match);\
			if(*object_2d_match)

#define get_2d_corner_objects(t)\
		{get_2d_objects_match(t, CORNER);\
		if(!load_obj_2d_def_cache(object_2d_match)) load_obj_2d_def(object_2d_match);\
			if(*object_2d_match)

#define add_to_northwest(t,tile_id, X, Y)\
		get_2d_corner_objects(t)\
			add_to_nearby(tile_id, add_2d_obj(object_2d_match, X+0.372, Y+2.628, get_highest_2d_object(tile_id), 0, 0, 0));}

#define add_to_north(t, tile_id)\
		get_2d_side_objects(t)\
			add_to_nearby(tile_id, add_2d_obj(object_2d_match, x+1.5, y+2.625, get_highest_2d_object(tile_id), 0, 0, 270));}

#define add_to_northeast(t,tile_id, X, Y)\
		get_2d_corner_objects(t)\
			add_to_nearby(tile_id, add_2d_obj(object_2d_match, X + 2.637, Y+2.628, get_highest_2d_object(tile_id), 0, 0, 270));}

#define add_to_east(t, tile_id)\
		get_2d_side_objects(t)\
			add_to_nearby(tile_id, add_2d_obj(object_2d_match, x+2.625, y+1.5, get_highest_2d_object(tile_id), 0, 0, 180));}
			
#define add_to_west(t, tile_id)\
		get_2d_side_objects(t)\
			add_to_nearby(tile_id, add_2d_obj(object_2d_match, x+0.375, y+1.5, get_highest_2d_object(tile_id), 0, 0, 0));}

#define add_to_southwest(t, tile_id, X, Y)\
		get_2d_corner_objects(t)\
			add_to_nearby(tile_id, add_2d_obj(object_2d_match, X+0.372, Y+0.372, get_highest_2d_object(tile_id), 0, 0, 90));}

#define add_to_south(t, tile_id)\
		get_2d_side_objects(t)\
			add_to_nearby(tile_id, add_2d_obj(object_2d_match, x+1.5, y+0.375, get_highest_2d_object(tile_id), 0, 0, 90));}

#define add_to_southeast(t, tile_id, X, Y)\
		get_2d_corner_objects(t)\
			add_to_nearby(tile_id, add_2d_obj(object_2d_match, X+2.637, Y+0.372, get_highest_2d_object(tile_id), 0, 0, 180));}

#define del_northwest(tile)		destroy_nearby_2d_object(tile,NORTHW);
#define del_from_north()		destroy_nearby_2d_object(NORTH,SOUTH);
#define del_northeast(tile)		destroy_nearby_2d_object(tile,NORTHE);
#define del_from_east()			destroy_nearby_2d_object(EAST,WEST);
#define del_from_west()			destroy_nearby_2d_object(WEST,EAST);
#define del_southwest(tile)		destroy_nearby_2d_object(tile,SOUTHW)
#define del_from_south()		destroy_nearby_2d_object(SOUTH,NORTH);
#define del_southeast(tile)		destroy_nearby_2d_object(tile,SOUTHE);

//Objects located in the 3x3 matrix
int nearby_2d_objects[9][10];
int nearby_3d_objects[9][15];

//The 2d/3d object file that's to be placed in the tile
char object_2d_match[100];
char object_3d_match[100];

void reset_nearby_2d_objects()
{
	int i,j;
	for(i=0;i<9;i++) for (j=0;j<10;j++) nearby_2d_objects[i][j]=-1;
}

void add_to_nearby(int pos, int object_id)
{
	int i;
	for(i=0;i<10;i++)
		{
			if(nearby_2d_objects[pos][i]<0)
				{
					nearby_2d_objects[pos][i]=object_id;
					return;
				}
		}
}

void get_nearby_2d_objects(int tile_pos)
{
	int i;
	reset_nearby_2d_objects();
	for(i=0;i<max_obj_2d;i++)
		{
			if(obj_2d_list[i])
				{
					if (is_center(obj_2d_list[i]->tile)) 		add_to_nearby(CENTER,i);	//Center tile
					else if (is_northwest(obj_2d_list[i]->tile)) 	add_to_nearby(NORTHW,i);	//Northwest
					else if (is_north(obj_2d_list[i]->tile)) 	add_to_nearby(NORTH,i);		//North
					else if (is_northeast(obj_2d_list[i]->tile))	add_to_nearby(NORTHE,i);	//Northeast
					else if (is_east(obj_2d_list[i]->tile))		add_to_nearby(EAST,i);		//East
					else if (is_southeast(obj_2d_list[i]->tile))	add_to_nearby(SOUTHE,i);	//Southeast
					else if (is_south(obj_2d_list[i]->tile))	add_to_nearby(SOUTH,i);		//South
					else if (is_southwest(obj_2d_list[i]->tile))	add_to_nearby(SOUTHW,i);	//Southwest
					else if (is_west(obj_2d_list[i]->tile))		add_to_nearby(WEST,i);		//West
				}
		}
}

void kill_nearby_2d_object(int id, int i)
{
	free(obj_2d_list[nearby_2d_objects[id][i]]);
	obj_2d_list[nearby_2d_objects[id][i]]=0;
	nearby_2d_objects[id][i]=-1;
}

void destroy_nearby_2d_object(int id, int position)
{
	int i;
	int x,y,z_rot;
	for(i=0;i<10;i++)
		{
			if(obj_2d_list[nearby_2d_objects[id][i]])
				{
					x=(int)((obj_2d_list[nearby_2d_objects[id][i]]->x_pos-(int)obj_2d_list[nearby_2d_objects[id][i]]->x_pos)*1000);//We want the offset to be an int - use the first 3 decimals
					y=(int)((obj_2d_list[nearby_2d_objects[id][i]]->y_pos-(int)obj_2d_list[nearby_2d_objects[id][i]]->y_pos)*1000);
					z_rot=obj_2d_list[nearby_2d_objects[id][i]]->z_rot;
					switch(position)
						{
							case -1://Destroy all...
								kill_nearby_2d_object(id,i);
								break;
							case NORTHW:
								if(x==372&&y==627&&z_rot==0)	kill_nearby_2d_object(id,i);
								break;
							case NORTH:
								if(x==500&&y==625&&z_rot==270)	kill_nearby_2d_object(id,i);
								break;
							case NORTHE:
								if(x==637&&y==627&&z_rot==270)	kill_nearby_2d_object(id,i);
								break;
							case EAST:
								if(x==625&&y==500&&z_rot==180)	kill_nearby_2d_object(id,i);
								break;
							case WEST:
								if(x==375&&y==500&&z_rot==0)	kill_nearby_2d_object(id,i);
								break;
							case SOUTHW:
								if(x==372&&y==372&&z_rot==90)	kill_nearby_2d_object(id,i);
								break;
							case SOUTH:
								if(x==500&&y==375&&z_rot==90)	kill_nearby_2d_object(id,i);
								break;
							case SOUTHE:
								if(x==637&&y==372&&z_rot==180)	kill_nearby_2d_object(id,i);
								break;
						}
				}
		}
}


void get_2d_objects_match(int tile_id, int type)
{
	switch(tile_id)
		{
			case 12:
			case 11:
			case 2:
			case 1:
				if (type==SIDE) sprintf(object_2d_match,"./2dobjects/%s",e2dlist[6+rand()%3].fn);
				else if (type==CORNER) sprintf(object_2d_match,"./2dobjects/%s",e2dlist[57+rand()%4].fn);
				return;
			default:
				*object_2d_match=0;
				return;
		}
}

float get_highest_2d_object(int id)
{
	int i=0;
	float highest=0.0001;
	for(i=0;i<10;i++)
		{
			if (nearby_2d_objects[id][i]>=0)
				{
					if (obj_2d_list[nearby_2d_objects[id][i]])
						{
							if(obj_2d_list[nearby_2d_objects[id][i]]->z_pos>=highest) 
								{
									highest=obj_2d_list[nearby_2d_objects[id][i]]->z_pos+0.0001;
								}
						}
				}
		}
	return highest;
}

void terraform_destroy(int * tiles, int type, int x, int y)//If tile type is dominant
{
	//Place the corners and edges... Check the northern, eastern, southern and western tiles first
	//Does anyone know a better way to do this?
	if(tiles[NORTH]==type)//North...
		{
			add_to_south(type,NORTH);
			if(tiles[WEST]==type && tiles[NORTHW]==type)	add_to_southeast(type,NORTHW,x,y);
			if(tiles[EAST]==type && tiles[NORTHE]==type)	add_to_southwest(type,NORTHE,x,y);
		}
	if(tiles[SOUTH]==type)
		{
			add_to_north(type,SOUTH);
			if(tiles[WEST]==type && tiles[SOUTHW]==type) add_to_northeast(type,SOUTHW,x,y);
			if(tiles[EAST]==type && tiles[SOUTHE]==type) add_to_northwest(type,SOUTHE,x,y);
		}
	if(tiles[EAST]==type)	add_to_west(type,EAST);
	if(tiles[WEST]==type)	add_to_east(type,WEST);
}

void terraform_create(int * tiles, int type, int x, int y)//if tile type is inferior
{
	if(tiles[NORTH]==type)//North
		{
			del_from_north();
			if(tiles[WEST]==type) {if (tiles[NORTHW]!=type) add_to_northwest(type,CENTER,x,y);}
			else if(tiles[NORTHW]==type) add_to_southwest(type,NORTH,x,y+3);
			if(tiles[EAST]==type) {if (tiles[NORTHE]!=type)	add_to_northeast(type,CENTER,x,y);}
			else if(tiles[NORTHE]==type) add_to_southeast(type,NORTH,x,y+3);
		}
	else add_to_north(type,CENTER);
	if(tiles[SOUTH]==type)//South
		{
			del_from_south();
			if(tiles[WEST]==type) {if(tiles[SOUTHW]!=type) add_to_southwest(type,CENTER,x,y);}
			else if(tiles[SOUTHW]==type) add_to_northwest(type,SOUTH,x,y-3);
			if(tiles[EAST]==type) {if(tiles[SOUTHE]!=type) add_to_southeast(type,CENTER,x,y);}
			else if(tiles[SOUTHE]==type) add_to_northeast(type,SOUTH,x,y-3);
		}
	else add_to_south(type,CENTER);
	if(tiles[EAST]==type)//East
		{
			del_from_east();
			if(tiles[NORTHE]==type)//Northeast
				{
					if(tiles[NORTH]!=type) add_to_northwest(type,EAST,x+3,y)
					else del_southwest(NORTHE);
				}
			if(tiles[SOUTHE]==type)//Southeast
				{
					if(tiles[SOUTH]!=type) add_to_southwest(type,EAST,x+3,y)
					else del_northwest(SOUTHE);
				}
		}
	else add_to_east(type,CENTER);
	if(tiles[WEST]==type)//West
		{
			del_from_west();
			if(tiles[NORTHW]==type)//Northwest
				{
					if(tiles[NORTH]!=type) add_to_northeast(type,WEST,x-3,y)
					else del_southeast(NORTHW);
				}
			if(tiles[SOUTHW]==type)//Southwest
				{
					if(tiles[SOUTH]!=type) add_to_southeast(type,WEST,x-3,y)
					else del_northeast(SOUTHW);
				}
		}
	else add_to_west(type,CENTER);
}

void terraform(int pos, int type)
{
	int tiles[9];//The tiles within reach.. 3x3
	int x=3*(pos%tile_map_size_x);
	int y=3*(pos-pos%tile_map_size_x)/tile_map_size_x;
	if (tile_map[pos]==type) return;
	get_nearby_2d_objects(pos);
	tile_map[pos]=tiles[CENTER]=type;
	destroy_nearby_2d_object(CENTER,-1);
	
	//Read the tiles ID's
	tiles[WEST]=tile_map[pos-1];
	tiles[EAST]=tile_map[pos+1];
	pos+=tile_map_size_x;
	tiles[NORTHW]=tile_map[pos-1];
	tiles[NORTH]=tile_map[pos];
	tiles[NORTHE]=tile_map[pos+1];
	pos-=2*tile_map_size_x;
	tiles[SOUTHW]=tile_map[pos-1];
	tiles[SOUTH]=tile_map[pos];
	tiles[SOUTHE]=tile_map[pos+1];

	terraform_create(tiles, type, x, y);
}

int create_terraform_partsys(int x, int y, int from, int to, int state)
{
	float x_pos=x*3+1.5f, y_pos=y*3+1.5f, z_pos=0;
	particle_sys_def *def=(particle_sys_def*)calloc(1,sizeof(particle_sys_def));

	def->part_sys_type=4;
	def->sblend=302;
	def->dblend=303;

	def->total_particle_no=(int)((float)state/255.0f*1600.0f);
	def->ttl=-1;
	def->part_texture=0;
	def->part_size=1.8f;
	def->random_func=0;
	def->minx=    -1.50000f; def->miny=    -1.50000f; def->minz=     0.00000f;
	def->maxx=     1.50000f; def->maxx= 	1.50000f; def->maxz=     0.00000f;
	def->constrain_rad_sq=-1.0f;
	def->vel_minx= 0.00000f; def->vel_miny=	0.00000f; def->vel_minz=-0.00150f;
	def->vel_maxx= 0.00000f; def->vel_maxy=	0.00000f; def->vel_maxz= 0.00000f;
	def->minr=     0.25000f; def->ming=	3.00000f; def->minb=     0.25000f; def->mina=-0.15000f;
	def->maxr=     0.90000f; def->maxg=	0.90000f; def->maxb=     0.90000f; def->maxa= 0.10000f;
	def->acc_minx=-0.00005f; def->acc_miny=-0.00005f; def->acc_minz=-0.01015f;
	def->acc_maxx= 0.00000f; def->acc_maxy= 0.00000f; def->acc_maxz= 0.01150f;
	def->mindr=   -0.01750f; def->mindg=   -0.09750f; def->mindb=   -0.01750f; def->minda=-0.03000f;
	def->maxdr=    0.02000f; def->maxdg=	0.10000f; def->maxdb=    0.02000f; def->maxda= 0.02000f;
	
	return create_particle_sys(def,x_pos,y_pos,z_pos);
}

void terraform_partsys_update(int idx, int status)
{
	if(particles_list[idx])
		{
			particles_list[idx]->particle_count=(float)status/255.0f*1600.0f;
		}
}

terraform_struct * terr_map;//just for compiling ;)

void terraform_control()
{
	int x;
	int y;
	int pos;
	for(y=0;y<tile_map_size_y;y++)
		{
			for(x=0;x<tile_map_size_x;x++)
				{
					pos=y*tile_map_size_x+x;
					if(terr_map[pos].into_tile!=tile_map[pos])
						{
							if(particles_list[terr_map[pos].index])
								{
									terraform_partsys_update(terr_map[pos].index, terr_map[pos].state);
								}
							else
								{
									terr_map[pos].index=create_terraform_partsys(x, y, tile_map[pos], terr_map[pos].into_tile, terr_map[pos].state);
								}
						}
				}
		}
}
