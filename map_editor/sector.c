#include "global.h"

map_sector *sectors;
int num_sectors;

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

void sector_update_objects_checksum(int sector)
{
	sectors[sector].objects_checksum=CRC32((unsigned char*)sectors[sector].e3d_local, 264);
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

// adds everything from the maps to the sectors
void sector_add_map()
{
	int i,j;
	int obj_3d_no=0;
	int obj_2d_no=0;
	int lights_no=0;
	int particles_no=0;


	for(i=0;i<max_obj_3d;i++)if(objects_list[i])obj_3d_no++;
	for(i=0;i<max_obj_2d;i++)if(obj_2d_list[i])obj_2d_no++;
	for(i=0;i<max_lights;i++)if(lights_list[i])lights_no++;
	for(i=0;i<max_particle_systems;i++){
		if(particles_list[i] && particles_list[i]->def && particles_list[i]->def != &def)
			particles_no++;
	}
	// 3d objects
	for(i=0;i<max_obj_3d;i++){
		if(j>obj_3d_no)
			break;
		if(objects_list[i]){
			sector_add_3do(i);
			j++;
		}
	}

	//2d objects
	j=0;
	for(i=0;i<max_obj_2d;i++){
		if(j>obj_2d_no)
			break;
		if(obj_2d_list[i]){
			sector_add_2do(i);
			j++;
		}
	}

	//lights
	j=0;
	for(i=0;i<max_lights;i++){
		if(j>lights_no)break;
		if(lights_list[i]){
			sector_add_light(i);
			j++;
		}
	}

	//particle systems
	j=0;
	for(i=0;i<max_particle_systems;i++){
		if(j>particles_no)
			break;
		if(particles_list[i] && particles_list[i]->def && particles_list[i]->def != &def){
			sector_add_particle(i);
			j++;
		}
	}

	for(i=0;i<num_sectors;i++)
		sector_update_checksums(i);

}

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

