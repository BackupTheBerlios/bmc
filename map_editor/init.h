#ifndef __INIT_H__
#define __INIT_H__

#include "global.h"

extern char lang[10];
extern char configdir[256];
extern char datadir[256];

void init_stuff();
void resize_window();

// 3dlist
void load_e3d_list();
void unload_e3d_list();
typedef struct{
	int id;
	char *fn;
	Uint32 attributes;
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

// partlist
void load_part_list();
void unload_part_list();
typedef struct{
	int id;
	char *fn;
}part_list;
extern part_list *partlist;
extern int partlistsize;

#endif
