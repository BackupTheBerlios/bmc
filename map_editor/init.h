#ifndef __INIT_H__
#define __INIT_H__

#include "global.h"

char lang[10];

void init_stuff();
void resize_window();

// 3dlist
void load_e3d_list();
void unload_e3d_list();
typedef struct{
	int id;
	char *fn;
}e3d_list;
extern e3d_list *e3dlist;
extern int e3dlistsize;

// 2dlist
void load_e2d_list();
void unload_e2d_list();
typedef struct{
	int id;
	char *fn;
}e2d_list;
extern e2d_list *e2dlist;
extern int e2dlistsize;

#endif
