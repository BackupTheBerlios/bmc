#include <string.h>
#ifdef MAP_EDITOR
#include "../map_editor/global.h"
#else
#include "global.h"
#endif

map_sector *sectors;
int num_sectors;
Uint16 active_sector;
int current_sector=-1;
Uint16 num_changes=0;
#define NEEDED_CHANGES 500


#ifndef MAP_EDITOR //added by Entropy, otherwise the map editor bitches about map_file_name
void add_change(){
	num_changes++;
	if(num_changes==NEEDED_CHANGES){
		num_changes=0;
		save_map(map_file_name);
	}
}
#else//if the map editor is defined, add an empty prototype, or else we get undefiend stuff in the linker
void add_change(){}
#endif

/* MISC SECTOR*/

void get_supersector(int sector, int *sx, int *sy, int *ex, int *ey)
{
	int tile_map_size_y_4=tile_map_size_y>>2;
	int tile_map_size_x_4=tile_map_size_x>>2;
	int fy=sector/(tile_map_size_y_4);
	int fx=sector%(tile_map_size_x_4);

	*sx=fx-1;
	if(*sx<0)*sx=0;
	*sy=fy-1;
	if(*sy<0)*sy=0;
	*ex=fx+1;
	if(*ex==tile_map_size_x_4)*ex=tile_map_size_x_4-1;
	*ey=fy+1;
	if(*ey==tile_map_size_y_4)*ey=tile_map_size_y_4-1;
}

void sector_update_checksums(int sector)
{
	sector_update_objects_checksum(sector);
	sector_update_tiles_checksum(sector);
}

float sector_to_global_x(int sector, Uint16 f)
{
	return (((float)f/65536)*12)+sector%(tile_map_size_x/4)*12.0f;
}

float sector_to_global_y(int sector, Uint16 f)
{
	return (((float)f/65536)*12)+sector/(tile_map_size_y/4)*12.0f;
}

/* CHECKSUM FUNCTIONS */
void sector_update_objects_checksum(int sector)
{
	int i;
	Uint32 t=0;
	//3d objects
	for(i=0;i<MAX_3D_PER_SECTOR;i++){
		if(sectors[sector].e3d_local[i]==-1)
			break;
		t=CRC32_continue(t,(unsigned char*)&objects_list[sectors[sector].e3d_local[i]]->o3dio,sizeof(object3d_io));
	}
	// 2d objects
	for(i=0;i<MAX_2D_PER_SECTOR;i++){
		if(sectors[sector].e2d_local[i]==-1)
			break;
		t=CRC32_continue(t,(unsigned char*)&obj_2d_list[sectors[sector].e2d_local[i]]->o2dio,sizeof(obj_2d_io));
	}
	//lights
	for(i=0;i<MAX_LIGHTS_PER_SECTOR;i++){
		if(sectors[sector].lights_local[i]==-1)
			break;
		t=CRC32_continue(t,(unsigned char*)&lights_list[sectors[sector].lights_local[i]]->lightio,sizeof(light_io));
	}
	//particles
	for(i=0;i<MAX_PARTICLES_PER_SECTOR;i++){
		if(sectors[sector].particles_local[i]==-1)
			break;
		t=CRC32_continue(t,(unsigned char*)&particles_list[sectors[sector].particles_local[i]]->particleio,sizeof(particles_io));
	}

	sectors[sector].objects_checksum = t ? ~t : t;

}

void sector_update_tiles_checksum(int sector)
{
	char temp[16];
	int fy=(sector<<2)/tile_map_size_y<<2;
	int fx=(sector<<2)%tile_map_size_x;
	int i,j,k=0;
	for(i=fx;i<fx+4;i++)
		for(j=fy;j<fy+4;j++)
			temp[k++]=tile_map[(j*tile_map_size_x)+i];
	sectors[sector].tiles_checksum=CRC32(temp, 16);
}


/* SECTOR OBJECT MANIPULATION */

void clear_sector(Uint16 sector)
{
	int i;
	// 3d objects
	for(i=0;i<MAX_3D_PER_SECTOR;i++){
		if(sectors[sector].e3d_local[i]!=-1){
			destroy_3d_object(sectors[sector].e3d_local[i]);
			sectors[sector].e3d_local[i]=-1;
		}
	}
	//2d objects
	for(i=0;i<MAX_2D_PER_SECTOR;i++){
		if(sectors[sector].e2d_local[i]!=-1){
			free(obj_2d_list[i]);
			obj_2d_list[i]=0;
			sectors[sector].e2d_local[i]=-1;
		}
	}
	//lights
	for(i=0;i<MAX_LIGHTS_PER_SECTOR;i++){
		if(sectors[sector].lights_local[i]!=-1){
			free(lights_list[i]);
			lights_list[i]=0;
			sectors[sector].lights_local[i]=-1;
		}
	}
	//particles
	for(i=0;i<MAX_PARTICLES_PER_SECTOR;i++){
		if(sectors[sector].particles_local[i]!=-1){
			free(particles_list[i]);
			particles_list[i]=0;
			sectors[sector].particles_local[i]=-1;
		}
	}

}

int sector_add_3do(int objectid)
{
	int i;
	int sector_no=sector_get(objects_list[objectid]->x_pos, objects_list[objectid]->y_pos);

	if(sector_no>=num_sectors) return -1;

	for(i=0;i<MAX_3D_PER_SECTOR;i++){
		if(sectors[sector_no].e3d_local[i]==-1){
			sectors[sector_no].e3d_local[i]=objectid;
			add_change();
			return i;
		}
	}
	return -1;
}


int sector_add_2do(int objectid)
{
	int i;
	int sector_no=sector_get(obj_2d_list[objectid]->x_pos, obj_2d_list[objectid]->y_pos);

	if(sector_no>=num_sectors) return -1;

	for(i=0;i<MAX_2D_PER_SECTOR;i++){
		if(sectors[sector_no].e2d_local[i]==-1){
			sectors[sector_no].e2d_local[i]=objectid;
			add_change();
			return i;
		}
	}
	return -1;
}


int sector_add_light(int objectid)
{
	int i;
	int sector_no=sector_get(lights_list[objectid]->pos_x, lights_list[objectid]->pos_y);

	if(sector_no>=num_sectors) return -1;

	for(i=0;i<MAX_LIGHTS_PER_SECTOR;i++){
		if(sectors[sector_no].lights_local[i]==-1){
			sectors[sector_no].lights_local[i]=objectid;
			add_change();
			return i;
		}
	}
	return -1;
}


int sector_add_particle(int objectid)
{
	int i;
	int sector_no=sector_get(particles_list[objectid]->x_pos, particles_list[objectid]->y_pos);

	if(sector_no>=num_sectors) return -1;

	for(i=0;i<MAX_PARTICLES_PER_SECTOR;i++){
		if(sectors[sector_no].particles_local[i]==-1){
			sectors[sector_no].particles_local[i]=objectid;
			add_change();
			return i;
		}
	}
	return -1;
}


int sector_add_tile(int objectid)
{
	//only crc calc here
	return -1;
}


void change_tile(Uint8 nt, Uint8 t)
{
	int fy=active_sector/(tile_map_size_y/4)*4;
	int fx=active_sector%(tile_map_size_x/4)*4;
	fx+=nt/4;
	fy+=nt%4;
	tile_map[(fy*tile_map_size_x)+fx]=t;
}


#ifdef ELC
void check_sector()
{
	int ns;
	actor *act=pf_get_our_actor();
	if(act==NULL) return;

	ns=sector_get(act->x_pos, act->y_pos);
	if(ns!=current_sector){
		current_sector=ns;
		send_superchecksum(current_sector);
	}
}
#endif


// Functions that send data to server
#ifdef ELC
void send_superchecksum(int sector)
{
	Uint32 t=0;
	int sx,sy,ex,ey,i,j;
	char msg[5];

	get_supersector(sector, &sx, &sy, &ex, &ey);

	for(i=sx;i<=ex;i++){
		for(j=sy;j<=ey;j++){
			t=CRC32_continue(t,(unsigned char*)&sectors[(j*(tile_map_size_x/4))+i].objects_checksum,sizeof(Uint32));
			t=CRC32_continue(t,(unsigned char*)&sectors[(j*(tile_map_size_x/4))+i].tiles_checksum,sizeof(Uint32));
		}
	}

	msg[0]=SEND_SUPERCHECKSUM;
	*(Uint32 *)&msg[1]=~t;
	my_tcp_send(my_socket,msg,5);
}

void update_sector_objects(Uint16 sector)
{
	char msg[3];
	clear_sector(sector);
	msg[0]=UPDATE_SECTOR_OBJECTS;
	*(Uint16 *)&msg[1]=sector;
	my_tcp_send(my_socket,msg,3);
}

void update_sector_tiles(Uint16 sector)
{
	char msg[3];
	msg[0]=UPDATE_SECTOR_TILES;
	*(Uint16 *)&msg[1]=sector;
	my_tcp_send(my_socket,msg,3);
}

// Functions that parse data from server

void get_checksums(char *d, int sector)
{
	int fy=sector/(tile_map_size_y/4);
	int fx=sector%(tile_map_size_x/4);
	int sx,sy,ex,ey,i,j;

	get_supersector(sector, &sx, &sy, &ex, &ey);

	for(i=sx;i<=ex;i++){
		for(j=sy;j<=ey;j++){
			if(*(Uint32*)d != sectors[(j*(tile_map_size_x/4))+i].objects_checksum)
				update_sector_objects((j*(tile_map_size_x/4))+i);
			d+=4;
			if(*(Uint32*)d != sectors[(j*(tile_map_size_x/4))+i].tiles_checksum)
				update_sector_tiles((j*(tile_map_size_x/4))+i);
			d+=4;
		}
	}

}




void get_tile_data(char *d)
{
	int i;
	Uint8 numtiles=*(Uint8*)d;
	d++;
	for(i=0;i<numtiles;i++){
		Uint8 fb=*(Uint8*)(d), sb;
		d++;
		sb=*(Uint8*)(d);
		d++;
		change_tile(fb,sb);
	}
	load_map_tiles();
	sector_update_tiles_checksum(active_sector);
}

void get_3d_objects(char *d)
{
	int i;
	Uint8 numobjects=*(Uint8*)d;
	d++;
	for(i=0;i<numobjects;i++){
		int k;
		object3d_io o3dio;

		memset(&o3dio,0,sizeof(object3d_io));

		o3dio.object_type=*(Uint16*)d;
		d+=2;
		o3dio.x_pos=*(Uint16*)d;
		d+=2;
		o3dio.y_pos=*(Uint16*)d;
		d+=2;
		o3dio.z_pos=*(Uint8*)d;
		d++;
		o3dio.z_rot=*(Uint8*)d;
		d++;
		/*
		//Should this be here or should we put all non-standard attributes in get_3d_objects_full_rotation?
		d++;
		o3dio.attributes=*(Uint16*)d;*/

		k=add_e3d(e3dlist_getname(o3dio.object_type),sector_to_global_x(active_sector,o3dio.x_pos), sector_to_global_y(active_sector,o3dio.y_pos) ,
		sector_to_global_z(o3dio.z_pos),o3dio.x_rot*1.5,o3dio.y_rot*1.5,o3dio.z_rot*1.5,
		o3dio.flags&0x1,o3dio.flags&0x2,o3dio.r/255.0f,o3dio.g/255.0f,o3dio.b/255.0f, o3dio.attributes);
		memcpy(&objects_list[k]->o3dio,&o3dio,sizeof(object3d_io));
		sector_add_3do(k);
	}
	sector_update_objects_checksum(active_sector);
}

void get_3d_objects_full_rotation(char *d)
{
	int i;
	Uint8 numobjects=*(Uint8*)d;
	d++;
	for(i=0;i<numobjects;i++){
		int k;
		object3d_io o3dio;

		memset(&o3dio,0,sizeof(object3d_io));

		o3dio.object_type=*(Uint16*)d;
		d+=2;
		o3dio.x_pos=*(Uint16*)d;
		d+=2;
		o3dio.y_pos=*(Uint16*)d;
		d+=2;
		o3dio.z_pos=*(Uint8*)d;
		d++;
		o3dio.z_rot=*(Uint8*)d;
		d++;
		o3dio.x_rot=*(Uint8*)d;
		d++;
		o3dio.y_rot=*(Uint8*)d;
		d++;
		o3dio.flags=*(Uint8*)d;
		d++;
		o3dio.attributes=*(Uint32*)d;
		d+=4;

		k=add_e3d(e3dlist_getname(o3dio.object_type),sector_to_global_x(active_sector,o3dio.x_pos),sector_to_global_y(active_sector,o3dio.y_pos),
		sector_to_global_z(o3dio.z_pos),o3dio.x_rot*1.5,o3dio.y_rot*1.5,o3dio.z_rot*1.5,
		o3dio.flags&0x1,o3dio.flags&0x2,o3dio.r/255.0f,o3dio.g/255.0f,o3dio.b/255.0f,o3dio.attributes);
		memcpy(&objects_list[k]->o3dio,&o3dio,sizeof(object3d_io));
		sector_add_3do(k);
	}
	sector_update_objects_checksum(active_sector);
}

void get_2d_objects(char *d)
{
	int i;
	Uint8 numobjects=*(Uint8*)d;
	d++;
	for(i=0;i<numobjects;i++){
		int k;
		obj_2d_io o2dio;

		memset(&o2dio,0,sizeof(obj_2d_io));

		o2dio.object_type=*(Uint16*)d;
		d+=2;
		o2dio.x_pos=*(Uint16*)d;
		d+=2;
		o2dio.y_pos=*(Uint16*)d;
		d+=2;
		o2dio.z_pos=*(Uint8*)d;
		d++;
		o2dio.z_rot=*(Uint8*)d;
		d++;

		k=add_2d_obj(e2dlist_getname(o2dio.object_type),sector_to_global_x(active_sector,o2dio.x_pos),sector_to_global_y(active_sector,o2dio.y_pos),
		sector_to_global_z(o2dio.z_pos)+0.001,o2dio.x_rot*1.5,o2dio.y_rot*1.5,o2dio.z_rot*1.5);
		memcpy(&obj_2d_list[k]->o2dio,&o2dio,sizeof(obj_2d_io));
		sector_add_2do(k);
	}
	sector_update_objects_checksum(active_sector);
}


void get_light_objects(char *d)
{
	int i;
	Uint8 numobjects=*(Uint8*)d;
	d++;
	for(i=0;i<numobjects;i++){
		int k;
		light_io lightio;

		memset(&lightio,0,sizeof(light_io));

		lightio.x_pos=*(Uint16*)d;
		d+=2;
		lightio.y_pos=*(Uint16*)d;
		d+=2;
		lightio.z_pos=*(Uint8*)d;
		d++;
		lightio.r=*(Uint8*)d;
		d++;
		lightio.g=*(Uint8*)d;
		d++;
		lightio.b=*(Uint8*)d;
		d++;
		lightio.flags=*(Uint8*)d;
		d++;
		lightio.intensity=*(Uint8*)d;
		d++;
		lightio.flicker=*(Sint8*)d;
		d++;
		lightio.interval=*(Uint16*)d;
		d+=2;

		k=add_light(sector_to_global_x(active_sector,lightio.x_pos),sector_to_global_y(active_sector,lightio.y_pos),
		sector_to_global_z(lightio.z_pos),io_to_global_intensity(lightio.r),io_to_global_intensity(lightio.g),
		io_to_global_intensity(lightio.b), 1.0f,lightio.flags, io_to_global_interval(lightio.interval), io_to_global_flicker(lightio.flicker));

		memcpy(&lights_list[k]->lightio,&lightio,sizeof(light_io));
		sector_add_light(k);
	}
	sector_update_objects_checksum(active_sector);
}

void get_particle_objects(char *d)
{
	int i;
	Uint8 numobjects=*(Uint8*)d;
	d++;
	for(i=0;i<numobjects;i++){
		int k;
		particles_io particlesio;

		memset(&particlesio,0,sizeof(particles_io));

		particlesio.object_type=*(Uint16*)d;
		d+=2;
		particlesio.x_pos=*(Uint16*)d;
		d+=2;
		particlesio.y_pos=*(Uint16*)d;
		d+=2;
		particlesio.z_pos=*(Uint8*)d;
		d++;

		k=add_particle_sys(partlist_getname(particlesio.object_type),sector_to_global_x(active_sector,particlesio.x_pos),sector_to_global_y(active_sector,particlesio.y_pos),
		sector_to_global_z(particlesio.z_pos));
		memcpy(&particles_list[k]->particleio,&particlesio,sizeof(particles_io));
		sector_add_particle(k);
	}
	sector_update_objects_checksum(active_sector);
}



// add delete replace funcs

void add_3d_object(char *d)
{
	int k, sector;
	object3d_io o3dio;

	memset(&o3dio,0,sizeof(object3d_io));

	sector=*(Uint16*)d;
	d+=2;
	o3dio.object_type=*(Uint16*)d;
	d+=2;
	o3dio.x_pos=*(Uint16*)d;
	d+=2;
	o3dio.y_pos=*(Uint16*)d;
	d+=2;
	o3dio.z_pos=*(Uint8*)d;
	d++;
	o3dio.z_rot=*(Uint8*)d;

	k=add_e3d(e3dlist_getname(o3dio.object_type),sector_to_global_x(sector,o3dio.x_pos), sector_to_global_y(sector,o3dio.y_pos) ,
	sector_to_global_z(o3dio.z_pos),o3dio.x_rot*1.5,o3dio.y_rot*1.5,o3dio.z_rot*1.5,
	o3dio.flags&0x1,o3dio.flags&0x2,o3dio.r/255.0f,o3dio.g/255.0f,o3dio.b/255.0f, o3dio.attributes);
	memcpy(&objects_list[k]->o3dio,&o3dio,sizeof(object3d_io));
	sector_add_3do(k);
	sector_update_objects_checksum(sector);
}

void add_3d_object_fullrotation(char *d)
{
	int k, sector;
	object3d_io o3dio;

	memset(&o3dio,0,sizeof(object3d_io));

	sector=*(Uint16*)d;
	d+=2;
	o3dio.object_type=*(Uint16*)d;
	d+=2;
	o3dio.x_pos=*(Uint16*)d;
	d+=2;
	o3dio.y_pos=*(Uint16*)d;
	d+=2;
	o3dio.z_pos=*(Uint8*)d;
	d++;
	o3dio.z_rot=*(Uint8*)d;
	d++;
	o3dio.x_rot=*(Uint8*)d;
	d++;
	o3dio.y_rot=*(Uint8*)d;
	d++;
	o3dio.flags=*(Uint8*)d;
	d++;
	o3dio.attributes=*(Uint32*)d;


	k=add_e3d(e3dlist_getname(o3dio.object_type),sector_to_global_x(sector,o3dio.x_pos), sector_to_global_y(sector,o3dio.y_pos) ,
	sector_to_global_z(o3dio.z_pos),o3dio.x_rot*1.5,o3dio.y_rot*1.5,o3dio.z_rot*1.5,
	o3dio.flags&0x1,o3dio.flags&0x2,o3dio.r/255.0f,o3dio.g/255.0f,o3dio.b/255.0f, o3dio.attributes);
	memcpy(&objects_list[k]->o3dio,&o3dio,sizeof(object3d_io));
	sector_add_3do(k);
	sector_update_objects_checksum(sector);
}


void delete_3d_object(char *d)
{
	int k, sector;
	sector=*(Uint16*)d;
	d+=2;
	k=*(Uint8*)d;

	destroy_3d_object(sectors[sector].e3d_local[k]);
	sectors[sector].e3d_local[k]=-1;
	sector_update_objects_checksum(sector);
}

void replace_3d_object(char *d)
{
	int k, sector, otype, n;
	object3d_io *o3dio;
	sector=*(Uint16*)d;
	d+=2;
	k=*(Uint8*)d;
	d++;
	otype=*(Uint16*)d;

	o3dio=&objects_list[sectors[sector].e3d_local[k]]->o3dio;
	o3dio->object_type=otype;
	// we create a new object
	n=add_e3d(e3dlist_getname(o3dio->object_type),sector_to_global_x(sector,o3dio->x_pos), sector_to_global_y(sector,o3dio->y_pos) ,
	sector_to_global_z(o3dio->z_pos),o3dio->x_rot*1.5,o3dio->y_rot*1.5,o3dio->z_rot*1.5,
	o3dio->flags&0x1,o3dio->flags&0x2,o3dio->r/255.0f,o3dio->g/255.0f,o3dio->b/255.0f, o3dio->attributes);
	memcpy(&objects_list[k]->o3dio,&o3dio,sizeof(object3d_io));

	// destroy old object
	destroy_3d_object(sectors[sector].e3d_local[k]);

	// add new object to sectors
	sectors[sector].e3d_local[k]=n;
	sector_update_objects_checksum(sector);

}


void add_2d_object(char *d)
{

	int k, sector;
	obj_2d_io o2dio;

	memset(&o2dio,0,sizeof(obj_2d_io));

	sector=*(Uint16*)d;
	d+=2;
	o2dio.object_type=*(Uint16*)d;
	d+=2;
	o2dio.x_pos=*(Uint16*)d;
	d+=2;
	o2dio.y_pos=*(Uint16*)d;
	d+=2;
	o2dio.z_pos=*(Uint8*)d;
	d++;
	o2dio.z_rot=*(Uint8*)d;

	k=add_2d_obj(e2dlist_getname(o2dio.object_type),sector_to_global_x(active_sector,o2dio.x_pos),sector_to_global_y(active_sector,o2dio.y_pos),
	sector_to_global_z(o2dio.z_pos)+0.001,o2dio.x_rot*1.5,o2dio.y_rot*1.5,o2dio.z_rot*1.5);
	memcpy(&obj_2d_list[k]->o2dio,&o2dio,sizeof(obj_2d_io));
	sector_add_2do(k);
	sector_update_objects_checksum(sector);
}

void delete_2d_object(char *d)
{
	int k, sector;
	sector=*(Uint16*)d;
	d+=2;
	k=*(Uint8*)d;

	free(obj_2d_list[sectors[sector].e2d_local[k]]);
	obj_2d_list[sectors[sector].e2d_local[k]]=0;
	sectors[sector].e2d_local[k]=-1;
	sector_update_objects_checksum(sector);
}

void replace_2d_object(char *d)
{
	int k, sector, otype, n;
	obj_2d_io *o2dio;
	sector=*(Uint16*)d;
	d+=2;
	k=*(Uint8*)d;
	d++;
	otype=*(Uint16*)d;

	o2dio=&obj_2d_list[sectors[sector].e2d_local[k]]->o2dio;
	o2dio->object_type=otype;
	// we create a new object
	n=add_2d_obj(e2dlist_getname(o2dio->object_type),sector_to_global_x(active_sector,o2dio->x_pos),sector_to_global_y(active_sector,o2dio->y_pos),
	sector_to_global_z(o2dio->z_pos)+0.001,o2dio->x_rot*1.5,o2dio->y_rot*1.5,o2dio->z_rot*1.5);
	memcpy(&obj_2d_list[k]->o2dio,&o2dio,sizeof(obj_2d_io));

	// destroy old object
	free(obj_2d_list[sectors[sector].e2d_local[k]]);
	obj_2d_list[sectors[sector].e2d_local[k]]=0;

	// add new object to sectors
	sectors[sector].e2d_local[k]=n;
	sector_update_objects_checksum(sector);

}


void add_lights(char *d)
{

	int k, sector;
	light_io lightio;

	memset(&lightio,0,sizeof(light_io));

	sector=*(Uint16*)d;
	d+=2;
	lightio.x_pos=*(Uint16*)d;
	d+=2;
	lightio.y_pos=*(Uint16*)d;
	d+=2;
	lightio.z_pos=*(Uint16*)d;
	d++;
	lightio.r=*(Uint8*)d;
	d++;
	lightio.g=*(Uint8*)d;
	d++;
	lightio.b=*(Uint8*)d;
	d++;
	lightio.flags=*(Uint8*)d;
	d++;
	lightio.intensity=*(Uint8*)d;
	d++;
	lightio.flicker=*(Uint8*)d;
	d++;
	lightio.interval=*(Uint8*)d;


	k=add_light(sector_to_global_x(active_sector,lightio.x_pos),sector_to_global_y(active_sector,lightio.y_pos),
	sector_to_global_z(lightio.z_pos),io_to_global_intensity(lightio.r),io_to_global_intensity(lightio.g),
	io_to_global_intensity(lightio.b), 1.0f,lightio.flags, io_to_global_interval(lightio.interval), io_to_global_flicker(lightio.flicker));

	memcpy(&lights_list[k]->lightio,&lightio,sizeof(light_io));
	sector_add_light(k);
	sector_update_objects_checksum(sector);
}

void delete_light(char *d)
{
	int k, sector;
	sector=*(Uint16*)d;
	d+=2;
	k=*(Uint8*)d;

	free(lights_list[sectors[sector].lights_local[k]]);
	lights_list[sectors[sector].lights_local[k]]=0;
	sectors[sector].lights_local[k]=-1;
	sector_update_objects_checksum(sector);
}


void add_particle(char *d)
{

	int k, sector;
	particles_io particlesio;

	memset(&particlesio,0,sizeof(particles_io));

	sector=*(Uint16*)d;
	d+=2;
	particlesio.object_type=*(Uint16*)d;
	d+=2;
	particlesio.x_pos=*(Uint16*)d;
	d+=2;
	particlesio.y_pos=*(Uint16*)d;
	d+=2;
	particlesio.z_pos=*(Uint8*)d;

	k=add_particle_sys(partlist_getname(particlesio.object_type),sector_to_global_x(active_sector,particlesio.x_pos),sector_to_global_y(active_sector,particlesio.y_pos),
	sector_to_global_z(particlesio.z_pos));
	memcpy(&particles_list[k]->particleio,&particlesio,sizeof(particles_io));
	sector_add_particle(k);
	sector_update_objects_checksum(sector);
}

void delete_particle(char *d)
{
	int k, sector;
	sector=*(Uint16*)d;
	d+=2;
	k=*(Uint8*)d;

	free(particles_list[sectors[sector].particles_local[k]]);
	particles_list[sectors[sector].particles_local[k]]=0;
	sectors[sector].particles_local[k]=-1;
	sector_update_objects_checksum(sector);
}

void replace_particle(char *d)
{
	int k, sector, otype, n;
	particles_io *particlesio;
	sector=*(Uint16*)d;
	d+=2;
	k=*(Uint8*)d;
	d++;
	otype=*(Uint16*)d;

	particlesio=&particles_list[sectors[sector].particles_local[k]]->particleio;
	particlesio->object_type=otype;
	// we create a new object
	n=add_particle_sys(partlist_getname(particlesio->object_type),sector_to_global_x(active_sector,particlesio->x_pos),sector_to_global_y(active_sector,particlesio->y_pos),
	sector_to_global_z(particlesio->z_pos));
	memcpy(&particles_list[k]->particleio,&particlesio,sizeof(particles_io));

	// destroy old object
	free(particles_list[sectors[sector].particles_local[k]]);
	particles_list[sectors[sector].particles_local[k]]=0;

	// add new object to sectors
	sectors[sector].particles_local[k]=n;
	sector_update_objects_checksum(sector);

}

#endif
