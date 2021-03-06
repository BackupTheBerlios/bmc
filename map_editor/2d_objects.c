#include "global.h"



void draw_2d_object(obj_2d * object_id)
{
	float render_x_start,render_y_start,u_start,v_start,u_end,v_end;
	float x_pos,y_pos,z_pos;
	float x_rot,y_rot,z_rot;
	float x_size,y_size;
	float alpha_test;
	int object_type;
	obj_2d_def *obj_def_pointer;

	int texture_id;
	int i,k;

	x_pos=object_id->x_pos;
	y_pos=object_id->y_pos;
	z_pos=object_id->z_pos;

	x_rot=object_id->x_rot;
	y_rot=object_id->y_rot;
	z_rot=object_id->z_rot;

	obj_def_pointer=object_id->obj_pointer;

	u_start=obj_def_pointer->u_start;
	u_end=obj_def_pointer->u_end;
 	v_start=obj_def_pointer->v_start;
	v_end=obj_def_pointer->v_end;
	x_size=obj_def_pointer->x_size;
	y_size=obj_def_pointer->y_size;
	alpha_test=obj_def_pointer->alpha_test;
	texture_id=get_texture_id(obj_def_pointer->texture_id);
	render_x_start=-x_size/2.0f;
	object_type=obj_def_pointer->object_type;
	if(object_type==ground)render_y_start=-y_size/2;
	else	render_y_start= 0;

	//find out what kind of object we have
	if(object_type==fence)x_rot+=90;
	if(object_type==plant)
	{
  	x_rot+=90;
    z_rot=-rz;
  }

	glPushMatrix();//we don't want to affect the rest of the scene
	glTranslatef (x_pos, y_pos, 0);
	glRotatef(z_rot, 0.0f, 0.0f, 1.0f);
	glRotatef(x_rot, 1.0f, 0.0f, 0.0f);
	glRotatef(y_rot, 0.0f, 1.0f, 0.0f);

    glEnable(GL_ALPHA_TEST);//enable alpha filtering, so we have some alpha key
    if(alpha_test!=0)
    glAlphaFunc(GL_GREATER,alpha_test);
    else
    glAlphaFunc(GL_GREATER,0.18f);

    		if(last_texture!=texture_id)
   			 	{
					glBindTexture(GL_TEXTURE_2D, texture_id);
					last_texture=texture_id;
				}

	if(!have_multitexture || !clouds_shadows)
		{
			glBegin(GL_QUADS);

			glTexCoord2f(u_start,v_start);
			glVertex3f(render_x_start,render_y_start,z_pos);

			glTexCoord2f(u_start,v_end);
			glVertex3f(render_x_start,render_y_start+y_size,z_pos);

			glTexCoord2f(u_end,v_end);
			glVertex3f(render_x_start+x_size,render_y_start+y_size,z_pos);

			glTexCoord2f(u_end,v_start);
			glVertex3f(render_x_start+x_size,render_y_start,z_pos);
    		glEnd();
		}
	else
		{
			float m,x,y,x1,y1;

			//bind the detail texture
			glActiveTextureARB(GL_TEXTURE1_ARB);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,  texture_cache[ground_detail_text].texture_id);
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glEnable(GL_TEXTURE_2D);

			glBegin(GL_QUADS);

			m=(-z_rot)*3.1415926/180;

			x=render_x_start;
			y=render_y_start;
			x1=x*cos(m)+y*sin(m);
			y1=y*cos(m)-x*sin(m);
			x1=x_pos+x1;
			y1=y_pos+y1;

			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,u_start,v_start);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB,x1/texture_scale+clouds_movement_u,y1/texture_scale+clouds_movement_v);
			glVertex3f(render_x_start,render_y_start,z_pos);

			x=render_x_start;
			y=render_y_start+y_size;
			x1=x*cos(m)+y*sin(m);
			y1=y*cos(m)-x*sin(m);
			x1=x_pos+x1;
			y1=y_pos+y1;

			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,u_start,v_end);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB,x1/texture_scale+clouds_movement_u,y1/texture_scale+clouds_movement_v);
			glVertex3f(render_x_start,render_y_start+y_size,z_pos);

			x=render_x_start+x_size;
			y=render_y_start+y_size;
			x1=x*cos(m)+y*sin(m);
			y1=y*cos(m)-x*sin(m);
			x1=x_pos+x1;
			y1=y_pos+y1;

			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,u_end,v_end);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB,x1/texture_scale+clouds_movement_u,y1/texture_scale+clouds_movement_v);
			glVertex3f(render_x_start+x_size,render_y_start+y_size,z_pos);

			x=render_x_start+x_size;
			y=render_y_start;
			x1=x*cos(m)+y*sin(m);
			y1=y*cos(m)-x*sin(m);
			x1=x_pos+x1;
			y1=y_pos+y1;


			glMultiTexCoord2fARB(GL_TEXTURE0_ARB,u_end,v_start);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB,x1/texture_scale+clouds_movement_u,y1/texture_scale+clouds_movement_v);
			glVertex3f(render_x_start+x_size,render_y_start,z_pos);
    		glEnd();
    		//disable the multitexturing
			glActiveTextureARB(GL_TEXTURE1_ARB);
			glDisable(GL_TEXTURE_2D);
			glActiveTextureARB(GL_TEXTURE0_ARB);
		}

    glDisable(GL_ALPHA_TEST);
	glPopMatrix();//restore the scene
}


obj_2d_def * load_obj_2d_def(char *file_name)
{
  int f_size;
  int i,k,l;
  FILE *f = NULL;
  char cur_dir[200]={0};
  obj_2d_def *cur_object;
  char *obj_file_mem;
  char *texture_file_name;
  char *handle_obj_file_mem;
  float x_size,y_size;
  float alpha_test;
  int file_x_len;
  int file_y_len;
  int u_start,u_end,v_start,v_end;


  cur_object=(obj_2d_def*) calloc(1, sizeof(obj_2d_def));
  //get the current directory
  l=strlen(file_name);
  //parse the string backwards, until we find a /
  while(l>0)
  	{
		  if(file_name[l]=='/' || file_name[l]=='\\')break;
		  l--;
  	}

  i=0;
  if(l)//prevent invalid dir names
  {
  	while(l>=0)
  		{
			cur_dir[i]=file_name[i];
			i++;
			l--;
  		}
  	cur_dir[i+1]=0;
  }


  f = fopen (file_name, "rb");
  if(!f)
	   {
            char str[120];
            sprintf(str,"Error: Can't open file: %s\n",file_name);
            log_error(str);
    	    return NULL;
	   }
  fseek (f, 0, SEEK_END);
  f_size = ftell (f);

  //ok, allocate memory for it
  obj_file_mem =(char*) calloc ( f_size, sizeof(char) );
  handle_obj_file_mem = obj_file_mem;
  fseek (f, 0, SEEK_SET);
  fread (obj_file_mem, 1, f_size, f);
  fclose (f);


  //ok, the file is loaded, so parse it
  file_x_len=get_integer_after_string("file_x_len:",obj_file_mem,f_size);
  file_y_len=get_integer_after_string("file_y_len:",obj_file_mem,f_size);
  u_start=get_integer_after_string("u_start:",obj_file_mem,f_size);
  u_end=get_integer_after_string("u_end:",obj_file_mem,f_size);
  v_start=get_integer_after_string("v_start:",obj_file_mem,f_size);
  v_end=get_integer_after_string("v_end:",obj_file_mem,f_size);
  x_size=get_float_after_string("x_size:",obj_file_mem,f_size);
  y_size=get_float_after_string("y_size:",obj_file_mem,f_size);
  alpha_test=get_float_after_string("alpha_test:",obj_file_mem,f_size);
  if(alpha_test<0)alpha_test=0;

  //get the proper u/v coordinates
  cur_object->u_start=(float)u_start/file_x_len;
  cur_object->u_end=(float)u_end/file_x_len;
  cur_object->v_start=1.0f-(float)v_start/file_y_len;
  cur_object->v_end=1.0f-(float)v_end/file_y_len;
  cur_object->x_size=x_size;
  cur_object->y_size=y_size;
  cur_object->alpha_test=alpha_test;

  //now  find the texture name
      texture_file_name=(char*) calloc(128, sizeof(char));
			i=get_string_occurance("texture:",obj_file_mem,40,0);
			obj_file_mem+=i;
			k=0;
			//find the file name
			while(k<128)
				{
					if(obj_file_mem[k]!=' ' && obj_file_mem[k]!=0x0a)break;
					k++;
				}
			//we found the beginning of the file name
			//now, copy the current directory string to the file_name string
			i=strlen(cur_dir);
			l=0;
			while(l<i)
			{
				texture_file_name[l]=cur_dir[l];
				l++;
			}
			while(l<128)
				{
					if(obj_file_mem[k]!=' ' && obj_file_mem[k]!=0x0a && obj_file_mem[k]!=0x0d)
						{
							texture_file_name[l]=obj_file_mem[k];
							k++;
							l++;
						}
					else
						{
							texture_file_name[l]=0;
							break;
						}
				}

			cur_object->texture_id= load_texture_cache(texture_file_name,0);
			//now get the object type
			i=get_string_occurance("type:",obj_file_mem,f_size,0);
			obj_file_mem+=i;
			k=0;
			for(k=0;k<10;k++)
			   {
			      if(obj_file_mem[k]==0x0a)
               {
                cur_object->object_type=invalid;
                break;
               }
			      if(obj_file_mem[k]==' ')continue;

			      if(obj_file_mem[k]=='g' || obj_file_mem[k]=='G')
               {
                cur_object->object_type=ground;
                break;
               }

			      if(obj_file_mem[k]=='p' || obj_file_mem[k]=='P')
               {
                cur_object->object_type=plant;
                break;
               }

			      if(obj_file_mem[k]=='f' || obj_file_mem[k]=='F')
               {
                cur_object->object_type=fence;
                break;
               }
			   }

  return cur_object;
  free(texture_file_name);
  free(handle_obj_file_mem);

}

//Tests to see if an obj_2d object is already loaded. If it is, return the handle.
//If not, load it, and return the handle
obj_2d_def * load_obj_2d_def_cache(char * file_name)
{
	int i;
	int j;
	int file_name_lenght;
	obj_2d_def * obj_2d_def_id;

	file_name_lenght=strlen(file_name);

	for(i=0;i<max_obj_2d_def;i++)
		{
			j=0;
			while(j<file_name_lenght)
				{
					if(obj_2d_def_cache[i].file_name[j]!=file_name[j])break;
					j++;
				}
			if(file_name_lenght==j)//ok, obj_2d_def already loaded
			return obj_2d_def_cache[i].obj_2d_def_id;
		}
	//asc not found in the cache, so load it, and store it
	obj_2d_def_id=load_obj_2d_def(file_name);

	//find a place to store it
	i=0;
	while(i<max_obj_2d_def)
		{
			if(!obj_2d_def_cache[i].file_name[0])//we found a place to store it
				{
					sprintf(obj_2d_def_cache[i].file_name, "%s", file_name);
					obj_2d_def_cache[i].obj_2d_def_id=obj_2d_def_id;
					return obj_2d_def_id;
				}
			i++;
		}

	return obj_2d_def_id;
}

int add_2d_obj(char * file_name, float x_pos, float y_pos, float z_pos, float x_rot, float y_rot, float z_rot)
{
	int texture_id;
	int i,k,len;
	obj_2d_def *returned_obj_2d_def;
	obj_2d *our_object;
	short sector;

	our_object =(obj_2d*) calloc(1, sizeof(obj_2d));

	//find a free spot, in the obj_2d_list
	i=0;
	while(i<max_obj_2d)
		{
			if(!obj_2d_list[i])break;
			i++;
		}

	//but first convert any '\' in '/'
	len=strlen(file_name);
	for(k=0;k<len;k++)if(file_name[k]=='\\')file_name[k]='/';

	returned_obj_2d_def=load_obj_2d_def_cache(file_name);
	if(!returned_obj_2d_def)
	   {
            char str[120];
            sprintf(str,"Error: Can't load 2d object: %s\n",file_name);
            log_error(str);
	        return 0;
	   }

	sprintf(our_object->file_name,"%s",file_name);
	our_object->x_pos=x_pos;
	our_object->y_pos=y_pos;
	our_object->z_pos=z_pos;

	our_object->x_rot=x_rot;
	our_object->y_rot=y_rot;
	our_object->z_rot=z_rot;
	our_object->obj_pointer=returned_obj_2d_def;

	obj_2d_list[i]=our_object;

	//get the current sector
	sector=(short)((y_pos/sector_size_y)*(map_meters_size_x/sector_size_x)+(x_pos/sector_size_x));
	our_object->sector=sector;

	return i;
}

void display_2d_objects()
{

	int i;
	int x,y;

	x= (int)-cx;
	y= (int)-cy;
	glDisable(GL_CULL_FACE);
	for(i=0;i<max_obj_2d;i++)
		{
			if(obj_2d_list[i])
			     {
			         int dist1;
			         int dist2;

			         dist1= x-(int)obj_2d_list[i]->x_pos;
			         dist2= y-(int)obj_2d_list[i]->y_pos;
			         if(dist1*dist1+dist2*dist2<=((40*40)*(zoom_level/15.75)))
                     	draw_2d_object(obj_2d_list[i]);
                 }
		}
}
