#include <string.h>
#ifdef MAP_EDITOR
#include "../map_editor/global.h"
#else
#include "global.h"
#endif

map_sector *sectors;
int num_sectors;
Uint16 active_sector;

/* MISC SECTOR*/

void sector_update_checksums(int sector)
{
	sector_update_objects_checksum(sector);
	sector_update_tiles_checksum(sector);
}


/* CHECKSUM FUNCTIONS */
void sector_update_objects_checksum(int sector)
{
	int i;
	Uint32 t=0;
	//3d objects
	for(i=0;i<100;i++){
		if(sectors[sector].e3d_local[i]==-1)
			break;
		t=CRC32_continue(t,(unsigned char*)&objects_list[sectors[sector].e3d_local[i]]->o3dio,sizeof(object3d_io));
	}
	// 2d objects
	for(i=0;i<20;i++){
		if(sectors[sector].e2d_local[i]==-1)
			break;
		t=CRC32_continue(t,(unsigned char*)&obj_2d_list[sectors[sector].e2d_local[i]]->o2dio,sizeof(obj_2d_io));
	}
	//lights
	for(i=0;i<4;i++){
		if(sectors[sector].lights_local[i]==-1)
			break;
		t=CRC32_continue(t,(unsigned char*)&lights_list[sectors[sector].lights_local[i]]->lightio,sizeof(light_io));
	}
	//particles
	for(i=0;i<8;i++){
		if(sectors[sector].particles_local[i]==-1)
			break;
		t=CRC32_continue(t,(unsigned char*)&particles_list[sectors[sector].particles_local[i]]->particleio,sizeof(particles_io));
	}

	sectors[sector].objects_checksum = t ? ~t : t;

}

void sector_update_tiles_checksum(int sector)
{
	char temp[16];
	int fy=sector/(tile_map_size_y/4)*4;
	int fx=sector%(tile_map_size_x/4)*4;
	int i,j,k=0;
	for(i=fx;i<fx+4;i++)
		for(j=fy;j<fy+4;j++)
			temp[k++]=tile_map[(j*tile_map_size_x)+i];
	sectors[sector].tiles_checksum=CRC32(temp, 16);
}


/* SECTOR OBJECT MANIPULATION */
int sector_add_3do(int objectid)
{
	int i;
	int sector_no=sector_get(objects_list[objectid]->x_pos, objects_list[objectid]->y_pos);

	if(sector_no>=num_sectors) return -1;

	for(i=0;i<100;i++){
		if(sectors[sector_no].e3d_local[i]==-1){
			sectors[sector_no].e3d_local[i]=objectid;
			return i;
		}
	}
	return -1;
}

int sector_del_3do(int objectid)
{
	int i;
	int sector_no=sector_get(objects_list[objectid]->x_pos, objects_list[objectid]->y_pos);

	if(sector_no>=num_sectors) return -1;

	for(i=0;i<100;i++){
		if(sectors[sector_no].e3d_local[i]==objectid){
			memmove(&sectors[sector_no].e3d_local[i], &sectors[sector_no].e3d_local[i+1], (99-i)*sizeof(short));
			sectors[sector_no].e3d_local[99]=-1;//if the list was full we can get a bad value here
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

	for(i=0;i<20;i++){
		if(sectors[sector_no].e2d_local[i]==-1){
			sectors[sector_no].e2d_local[i]=objectid;
			return i;
		}
	}
	return -1;
}

int sector_del_2do(int objectid)
{
	int i;
	int sector_no=sector_get(obj_2d_list[objectid]->x_pos, obj_2d_list[objectid]->y_pos);

	if(sector_no>=num_sectors) return -1;

	for(i=0;i<20;i++){
		if(sectors[sector_no].e2d_local[i]==objectid){
			memmove(&sectors[sector_no].e2d_local[i], &sectors[sector_no].e2d_local[i+1], (19-i)*sizeof(short));
			sectors[sector_no].e2d_local[19]=-1;//if the list was full we can get a bad value here
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

	for(i=0;i<4;i++){
		if(sectors[sector_no].lights_local[i]==-1){
			sectors[sector_no].lights_local[i]=objectid;
			return i;
		}
	}
	return -1;
}

int sector_del_light(int objectid)
{
	int i;
	int sector_no=sector_get(lights_list[objectid]->pos_x, lights_list[objectid]->pos_y);

	if(sector_no>=num_sectors) return -1;

	for(i=0;i<4;i++){
		if(sectors[sector_no].lights_local[i]==objectid){
			memmove(&sectors[sector_no].lights_local[i], &sectors[sector_no].lights_local[i+1], (3-i)*sizeof(short));
			sectors[sector_no].lights_local[3]=-1;//if the list was full we can get a bad value here
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

	for(i=0;i<8;i++){
		if(sectors[sector_no].particles_local[i]==-1){
			sectors[sector_no].particles_local[i]=objectid;
			return i;
		}
	}
	return -1;
}

int sector_del_particle(int objectid)
{
	int i;
	int sector_no=sector_get(particles_list[objectid]->x_pos, particles_list[objectid]->y_pos);

	if(sector_no>=num_sectors) return -1;

	for(i=0;i<8;i++){
		if(sectors[sector_no].particles_local[i]==objectid){
			memmove(&sectors[sector_no].particles_local[i], &sectors[sector_no].particles_local[i+1], (3-i)*sizeof(short));
			sectors[sector_no].particles_local[7]=-1;//if the list was full we can get a bad value here
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

int sector_del_tile(int objectid)
{
	//crc recalc
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

// Functions that send data to server
void send_superchecksum(int sector)
{
	Uint32 t=0;
	int fy=sector/(tile_map_size_y/4);
	int fx=sector%(tile_map_size_x/4);
	int sx,sy,ex,ey,i,j;
	char msg[5];
	sx=fx-1;
	if(sx<0)sx=0;
	sy=fy-1;
	if(sy<0)sy=0;
	ex=fx+1;
	if(ex==(tile_map_size_x/4))ex=(tile_map_size_x/4)-1;
	ey=fy+1;
	if(ey==(tile_map_size_y/4))ey=(tile_map_size_y/4)-1;

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
	char msg[5];
	sx=fx-1;
	if(sx<0)sx=0;
	sy=fy-1;
	if(sy<0)sy=0;
	ex=fx+1;
	if(ex==(tile_map_size_x/4))ex=(tile_map_size_x/4)-1;
	ey=fy+1;
	if(ey==(tile_map_size_y/4))ey=(tile_map_size_y/4)-1;

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
#endif



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

		k=add_e3d(e3dlist_getname(o3dio.object_type),sector_to_global_x(active_sector,o3dio.x_pos),sector_to_global_y(active_sector,o3dio.y_pos),
		sector_to_global_z(o3dio.z_pos),o3dio.x_rot*1.5,o3dio.y_rot*1.5,o3dio.z_rot*1.5,
		o3dio.flags&0x1,o3dio.flags&0x2,o3dio.r/255.0f,o3dio.g/255.0f,o3dio.b/255.0f);
		memcpy(&objects_list[k]->o3dio,&o3dio,sizeof(object3d_io));
		sector_add_3do(k);
	}
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

		k=add_e3d(e3dlist_getname(o3dio.object_type),sector_to_global_x(active_sector,o3dio.x_pos),sector_to_global_y(active_sector,o3dio.y_pos),
		sector_to_global_z(o3dio.z_pos),o3dio.x_rot*1.5,o3dio.y_rot*1.5,o3dio.z_rot*1.5,
		o3dio.flags&0x1,o3dio.flags&0x2,o3dio.r/255.0f,o3dio.g/255.0f,o3dio.b/255.0f);
		memcpy(&objects_list[k]->o3dio,&o3dio,sizeof(object3d_io));
		sector_add_3do(k);
	}

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

		d+=2;
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

		k=add_light(sector_to_global_x(active_sector,lightio.x_pos),sector_to_global_y(active_sector,lightio.y_pos),
		sector_to_global_z(lightio.z_pos),lightio.r/255.0f,lightio.g/255.0f,lightio.b/255.0f, 1.0f);
		memcpy(&lights_list[k]->lightio,&lightio,sizeof(light_io));
		sector_add_light(k);
	}
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
}
