#include <stdlib.h>
#include <string.h>
#include "global.h"

int e3dlist_getid(char *name)
{
	int i;
	for(i=0;i<e3dlistsize;i++)
		if(!strcmp(name,e3dlist[i].fn))
			return i;
	return -1;
}

int e2dlist_getid(char *name)
{
	int i;
	for(i=0;i<e2dlistsize;i++)
		if(!strcmp(name,e2dlist[i].fn))
			return i;
	return -1;
}

char *e3dlist_getname(int id)
{
	int i;
	for(i=0;i<e3dlistsize;i++)
		if(e3dlist[i].id==id)
			return e3dlist[i].fn;
	return NULL;
}

char *e2dlist_getname(int id)
{
	int i;
	for(i=0;i<e2dlistsize;i++)
		if(e2dlist[i].id==id)
			return e2dlist[i].fn;
	return NULL;
}

int partlist_getid(char *name)
{
	int i;
	for(i=0;i<partlistsize;i++)
		if(!strcmp(name,partlist[i].fn))
			return i;
	return -1;
}

char *partlist_getname(int id)
{
	int i;
	for(i=0;i<partlistsize;i++)
		if(partlist[i].id==id)
			return partlist[i].fn;
	return NULL;
}

void destroy_map()
{
	int i;

	//kill the tile and height map
	if(tile_map)
		{
			free(tile_map);
			tile_map=0;
		}

	if(height_map)
		{
			free(height_map);
			height_map=0;
		}


	//destriy sectors
	if(sectors){
		free(sectors);
		sectors=0;
	}
	//kill the 3d objects links
	for(i=0;i<max_obj_3d;i++)
		{
			if(objects_list[i])
				{
					free(objects_list[i]);
					objects_list[i]=0;//kill any refference to it
				}
		}

	//kill the 2d objects links
	for(i=0;i<max_obj_2d;i++)
		{
			if(obj_2d_list[i])
				{
					free(obj_2d_list[i]);
					obj_2d_list[i]=0;//kill any refference to it
				}
		}

	//kill the lights links
	for(i=0;i<max_lights;i++)
		{
			if(lights_list[i])
				{
					free(lights_list[i]);
					lights_list[i]=0;//kill any refference to it
				}
		}

	destroy_all_particles();
}

//fix z_pos
int save_map(char * file_name)
{
	int i,j;
	map_header cur_map_header;
	char * mem_map_header=(char *)&cur_map_header;

	object3d_io cur_3d_obj_io;
	object3d cur_3d_obj;
	int obj_3d_no=0;
	int obj_3d_io_size;

	obj_2d_io cur_2d_obj_io;
	obj_2d cur_2d_obj;
	int obj_2d_no=0;
	int obj_2d_io_size;

	light_io cur_light_io;
	light cur_light;
	int lights_no=0;
	int lights_io_size;

	particles_io cur_particles_io;
	int particles_no=0;
	int particles_io_size;

	map_sector cur_sector;
	int sector_no=0;
	int sector_size;

	FILE *f = NULL;

	memset(sectors,-1,num_sectors*sizeof(map_sector));
/*	sector_add_map(); */
	//get the sizes of structures (they might change in the future)
	obj_3d_io_size=sizeof(object3d_io);
	obj_2d_io_size=sizeof(obj_2d_io);
	lights_io_size=sizeof(light_io);
	particles_io_size=sizeof(particles_io);
	sector_size=sizeof(map_sector);

	//get the number of objects and lights
	for(i=0;i<max_obj_3d;i++)if(objects_list[i])obj_3d_no++;
	for(i=0;i<max_obj_2d;i++)if(obj_2d_list[i])obj_2d_no++;
	for(i=0;i<max_lights;i++)if(lights_list[i])lights_no++;
	// We ignore temporary particle systems (i.e. ones with a ttl)
	for(i=0;i<max_particle_systems;i++){
		if(particles_list[i] && particles_list[i]->def)
			particles_no++;
	}
	sector_no=num_sectors;

	//ok, now build the header...
	//clear the header
	for(i=0;i<sizeof(map_header);i++)
		mem_map_header[i]=0;

	//build the file signature
	cur_map_header.file_sig[0]='b';
	cur_map_header.file_sig[1]='m';
	cur_map_header.file_sig[2]='m';
	cur_map_header.file_sig[3]='f';

	cur_map_header.tile_map_x_len=tile_map_size_x;
	cur_map_header.tile_map_y_len=tile_map_size_y;
	cur_map_header.tile_map_offset=sizeof(map_header);
	cur_map_header.height_map_offset=cur_map_header.tile_map_offset+tile_map_size_x*tile_map_size_y;
	cur_map_header.obj_3d_struct_len=obj_3d_io_size;
	cur_map_header.obj_3d_no=obj_3d_no;
	cur_map_header.obj_3d_offset=cur_map_header.height_map_offset+tile_map_size_x*tile_map_size_y*6*6;
	cur_map_header.obj_2d_struct_len=obj_2d_io_size;
	cur_map_header.obj_2d_no=obj_2d_no;
	cur_map_header.obj_2d_offset=cur_map_header.obj_3d_offset+obj_3d_no*obj_3d_io_size;
	cur_map_header.lights_struct_len=lights_io_size;
	cur_map_header.lights_no=lights_no;
	cur_map_header.lights_offset=cur_map_header.obj_2d_offset+obj_2d_no*obj_2d_io_size;
	cur_map_header.dungeon=dungeon;
	cur_map_header.ambient_r=ambient_r;
	cur_map_header.ambient_g=ambient_g;
	cur_map_header.ambient_b=ambient_b;
	cur_map_header.particles_struct_len=particles_io_size;
	cur_map_header.particles_no=particles_no;
	cur_map_header.particles_offset=cur_map_header.lights_offset+lights_no*lights_io_size;
	cur_map_header.sector_struct_len=sector_size;
	cur_map_header.sectors_no=sector_no;
	cur_map_header.sectors_offset=cur_map_header.particles_offset+(particles_no*particles_io_size);
	//ok, now let's open/create the file, and start writting the header...
	f=fopen(file_name, "wb");

	//write the header
	fwrite(mem_map_header, sizeof(map_header), 1, f);

	//write the tiles map
	fwrite(tile_map, tile_map_size_x*tile_map_size_y, 1, f);

	//write the heights map
	fwrite(height_map, tile_map_size_x*tile_map_size_y*6*6, 1, f);

	//write the 3d objects
	j=0;
	for(i=0;i<max_obj_3d;i++){

		if(j>obj_3d_no)break;
		if(objects_list[i]){
			fwrite(&objects_list[i]->o3dio, sizeof(object3d_io), 1, f);
			j++;
		}
	}

	//write the 2d objects
	j=0;
	for(i=0;i<max_obj_2d;i++){
		if(j>obj_2d_no)break;
		if(obj_2d_list[i]){
			fwrite(&obj_2d_list[i]->o2dio, sizeof(obj_2d_io), 1, f);
			j++;
		}
	}

	//write the lights
	j=0;
	for(i=0;i<max_lights;i++){
		if(j>lights_no)break;
		if(lights_list[i]){
			fwrite(&lights_list[i]->lightio, sizeof(light_io), 1, f);
			j++;
		}
	}

	// Write the particle systems
	j=0;
	for(i=0;i<max_particle_systems;i++)
	{
		if(j>particles_no)break;
		if(particles_list[i] && particles_list[i]->def){	
			fwrite(&particles_list[i]->particleio,sizeof(particles_io),1,f);
			j++;
		}
	}

	// writing sectors
	fwrite(sectors,sizeof(map_sector),sector_no,f);

	fclose(f);

	return 1;

}

//fix z_pos
int load_map(char * file_name)
{
	int i,j;
	map_header cur_map_header;
	char * mem_map_header=(char *)&cur_map_header;


	object3d_io cur_3d_obj_io;
	object3d cur_3d_obj;
	int obj_3d_no=0;
	int obj_3d_io_size;

	obj_2d_io cur_2d_obj_io;
	obj_2d cur_2d_obj;
	int obj_2d_no=0;
	int obj_2d_io_size;

	light_io cur_light_io;
	light cur_light;
	int lights_no=0;
	int lights_io_size;

	particles_io cur_particles_io;
	int particles_no=0;
	int particles_io_size;

	map_sector cur_sector;
	int sector_no=0;
	int sector_size;

	FILE *f = NULL;
	f=fopen(file_name, "rb");
	if(!f)return 0;

	destroy_map();

	fread(mem_map_header, 1, sizeof(cur_map_header), f);//header only

	//verify if we have a valid file
	if(cur_map_header.file_sig[0]!='b')return 0;
	if(cur_map_header.file_sig[1]!='m')return 0;
	if(cur_map_header.file_sig[2]!='m')return 0;
	if(cur_map_header.file_sig[3]!='f')return 0;

	strcpy(map_file_name,file_name);
	
	//get the map size
	tile_map_size_x=cur_map_header.tile_map_x_len;
	tile_map_size_y=cur_map_header.tile_map_y_len;

	//allocate memory for the tile map (it was destroyed)
	tile_map=(unsigned char *)calloc(tile_map_size_x*tile_map_size_y, 1);
	//allocates the memory for the heights now
	height_map=(unsigned char *)calloc(tile_map_size_x*tile_map_size_y*6*6, 1);
	//allocate the terraform map
	terr_map=(terraform_struct *)malloc(tile_map_size_x*tile_map_size_y*sizeof(terraform_struct));
	memset(terr_map,255,tile_map_size_x*tile_map_size_y*sizeof(terraform_struct));//Start at 0xFF...

	//get the sizes of structures (they might change in the future)
	obj_3d_io_size=cur_map_header.obj_3d_struct_len;
	obj_2d_io_size=cur_map_header.obj_2d_struct_len;
	lights_io_size=cur_map_header.lights_struct_len;
	particles_io_size=cur_map_header.particles_struct_len;
	sector_size=cur_map_header.sector_struct_len;

	//get the number of objects and lights
	obj_3d_no=cur_map_header.obj_3d_no;
	obj_2d_no=cur_map_header.obj_2d_no;
	lights_no=cur_map_header.lights_no;
	particles_no=cur_map_header.particles_no;
	sector_no=cur_map_header.sectors_no;
	num_sectors=sector_no;

	//see if we have to change the water texture (when we get from dungeon to surface or
	//the other way around
	if(dungeon && !cur_map_header.dungeon)
		{
			//ok, change the water to normal
			glDeleteTextures(1,&texture_cache[sky_text_1].texture_id);
			//also destroy the name of that texture, since it is not in cache anymore
			texture_cache[sky_text_1].file_name[0]=0;
			sky_text_1=load_texture_cache("./textures/sky.bmp",70);

		}
	if(!dungeon && cur_map_header.dungeon)
		{
			//ok, change the water to dungeon water
			glDeleteTextures(1,&texture_cache[sky_text_1].texture_id);
			//also destroy the name of that texture, since it is not in cache anymore
			texture_cache[sky_text_1].file_name[0]=0;
			sky_text_1=load_texture_cache("./textures/water2.bmp",70);

		}


	//get the type of map, and the ambient light
	dungeon=cur_map_header.dungeon;
	ambient_r=cur_map_header.ambient_r;
	ambient_g=cur_map_header.ambient_g;
	ambient_b=cur_map_header.ambient_b;

	//this is useful if we go in/out a dungeon
	new_minute();

	//read the tiles map
	fread(tile_map, 1, tile_map_size_x*tile_map_size_y, f);
	
	//load the tiles in this map, if not already loaded
	load_map_tiles();

	//read the heights map
	fread(height_map, 1, tile_map_size_x*tile_map_size_y*6*6, f);

	//read the 3d objects
	for(i=0;i<obj_3d_no;i++)
		{
			char * cur_3do_pointer=(char *)&cur_3d_obj_io;
			int k;
			fread(cur_3do_pointer, 1, obj_3d_io_size, f);

			k=add_e3d(e3dlist_getname(cur_3d_obj_io.object_type),cur_3d_obj_io.x_pos,cur_3d_obj_io.y_pos,
			sector_to_global_z(cur_3d_obj_io.z_pos),cur_3d_obj_io.x_rot*1.5,cur_3d_obj_io.y_rot*1.5,cur_3d_obj_io.z_rot*1.5,
			cur_3d_obj_io.flags&0x1,cur_3d_obj_io.flags&0x2,cur_3d_obj_io.r/255.0f,cur_3d_obj_io.g/255.0f,cur_3d_obj_io.b/255.0f);
			memcpy(&objects_list[k]->o3dio,&cur_3d_obj_io,sizeof(object3d_io));
		}

	//read the 2d objects
	for(i=0;i<obj_2d_no;i++)
		{
			char * cur_2do_pointer=(char *)&cur_2d_obj_io;
			int k;
			fread(cur_2do_pointer, 1, obj_2d_io_size, f);

			k = add_2d_obj(e2dlist_getname(cur_2d_obj_io.object_type),cur_2d_obj_io.x_pos,cur_2d_obj_io.y_pos,
			sector_to_global_z(cur_2d_obj_io.z_pos)+0.001,cur_2d_obj_io.x_rot*1.5,cur_2d_obj_io.y_rot*1.5,cur_2d_obj_io.z_rot*1.5);
			memcpy(&obj_2d_list[k]->o2dio,&cur_2d_obj_io,sizeof(obj_2d_io));
		}


	//read the lights
	for(i=0;i<lights_no;i++)
		{
			char * cur_light_pointer=(char *)&cur_light_io;
			int k;
			fread(cur_light_pointer, 1, lights_io_size, f);
			k=add_light(cur_light_io.x_pos,cur_light_io.y_pos,sector_to_global_z(cur_light_io.z_pos),
			io_to_global_intensity(cur_light_io.r),io_to_global_intensity(cur_light_io.g),io_to_global_intensity(cur_light_io.b), 
			io_to_global_intensity(cur_light_io.intensity),cur_light_io.flags, io_to_global_interval(cur_light_io.interval));
			memcpy(&lights_list[k]->lightio,&cur_light_io,sizeof(light_io));
		}

	//read particle systems
	for(i=0;i<particles_no;i++)
		{
			char *cur_particles_pointer=(char *)&cur_particles_io;
			int k;
			fread(cur_particles_pointer,1,particles_io_size,f);
			k=add_particle_sys(partlist_getname(cur_particles_io.object_type),cur_particles_io.x_pos,cur_particles_io.y_pos,sector_to_global_z(cur_particles_io.z_pos));
			memcpy(&particles_list[k]->particleio,&cur_particles_io,sizeof(particles_io));
		}
	
	sectors=(map_sector*)malloc(sizeof(map_sector)*num_sectors);
	fread(sectors,sizeof(map_sector),num_sectors,f);
	fclose(f);

	// Updating positions from local to global
	for(i=0;i<num_sectors;i++)
	{
		for(j=0;j<100;j++){
			if(sectors[i].e3d_local[j]==-1)
				break;
			objects_list[sectors[i].e3d_local[j]]->x_pos=sector_to_global_x(i,objects_list[sectors[i].e3d_local[j]]->x_pos);
			objects_list[sectors[i].e3d_local[j]]->y_pos=sector_to_global_y(i,objects_list[sectors[i].e3d_local[j]]->y_pos);;
		}
		for(j=0;j<20;j++){
			if(sectors[i].e2d_local[j]==-1)
				break;
			obj_2d_list[sectors[i].e2d_local[j]]->x_pos=sector_to_global_x(i,obj_2d_list[sectors[i].e2d_local[j]]->x_pos);
			obj_2d_list[sectors[i].e2d_local[j]]->y_pos=sector_to_global_y(i,obj_2d_list[sectors[i].e2d_local[j]]->y_pos);;
		}
		for(j=0;j<4;j++){
			if(sectors[i].lights_local[j]==-1)
				break;
			lights_list[sectors[i].lights_local[j]]->pos_x=sector_to_global_x(i,lights_list[sectors[i].lights_local[j]]->pos_x);
			lights_list[sectors[i].lights_local[j]]->pos_y=sector_to_global_y(i,lights_list[sectors[i].lights_local[j]]->pos_y);;
		}
		for(j=0;j<8;j++){
			if(sectors[i].particles_local[j]==-1)
				break;
			if(sectors[i].particles_local[j]==0)continue; //Hmm, shouldn't happen in newer map formats
			particles_list[sectors[i].particles_local[j]-1]->x_pos=sector_to_global_x(i,particles_list[sectors[i].particles_local[j]-1]->x_pos);//The client does not have the particle editors default particle system, which is located as no. 0 in the particles_list - hence the particles for this map will always be 1 less than when it was saved in the map editor.
			particles_list[sectors[i].particles_local[j]-1]->y_pos=sector_to_global_y(i,particles_list[sectors[i].particles_local[j]-1]->y_pos);;
		}


	}
	return 1;

}

void new_map(int m_x_size,int m_y_size)
{
	int i;
	//destroy the previous map, if any
	destroy_map();

	//allocate memory for the tile map (it was destroyed)
	tile_map=(unsigned char *)calloc(m_x_size*m_y_size, 1);
	//now, fill the map
	for(i=0;i<m_x_size*m_y_size;i++)tile_map[i]=1;
	tile_map_size_x=m_x_size;
	tile_map_size_y=m_y_size;

	//allocates the memory for the heights now
	height_map=(unsigned char *)calloc(m_x_size*m_y_size*6*6, 1);
	//now, fill the map
	for(i=0;i<m_x_size*m_y_size*6*6;i++)height_map[i]=11;

	// memory for the sectors
	num_sectors=(m_x_size/4)*(m_y_size/4);
	sectors=(map_sector*)malloc(sizeof(map_sector)*num_sectors);
	memset(sectors,-1,sizeof(map_sector)*num_sectors);

	load_map_tiles();
	//reset the camera coordinates
	cx=0;
	cy=0;
}

