#include "global.h"

map_sector *sectors;
int num_sectors;
Uint16 active_sector;

/* MISC SECTOR, AND CONVERTION FUNCS */

Uint16 global_to_sector(float f)
{
	return /*(int)*/(((float)(f-(int)f)+(float)((int)f%12))/12)*65536;
}

float sector_to_global_x(int sector, Uint16 f)
{
	return (((float)f/65536)*12)+sector%(tile_map_size_x/4)*12.0f;
}

float sector_to_global_y(int sector, Uint16 f)
{
	return (((float)f/65536)*12)+sector/(tile_map_size_y/4)*12.0f;
}

//here there will be useful fuctions for calculating crcs, adding deleting objects etc
int sector_get(float x, float y)
{
	int sx=x/12;
	int sy=y/12;
	return sy*(tile_map_size_x>>2)+sx;
}

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

	for(i=0;i<4;i++){
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

	for(i=0;i<4;i++){
		if(sectors[sector_no].particles_local[i]==objectid){
			memmove(&sectors[sector_no].particles_local[i], &sectors[sector_no].particles_local[i+1], (3-i)*sizeof(short));	
			sectors[sector_no].particles_local[3]=-1;//if the list was full we can get a bad value here
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


// Functions that parse data from server
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
	//	fb=fb<<4;
		change_tile(fb,sb);
	}
}
