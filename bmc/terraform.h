#ifndef __TERRAFORM_H__
#define __TERRAFORM_H__

#define translate_coords(x,y) ((int)y/3*tile_map_size_x+(int)x/3)

//Defines for readability...	//	       Tile Matrix
#define CENTER	0		//		|	|	
#define NORTHW	1		//	   1	|   2	|   3	
#define NORTH	2		//	________|_______|_______
#define NORTHE	3		//		|	|	
#define EAST	4		//	   8	|   0	|   4	
#define SOUTHE	5		//	________|_______|_______
#define SOUTH	6		//		|	|	
#define SOUTHW	7		//	   7	|   6	|   5	
#define WEST	8		//		|	|	 

typedef struct {	
	Uint8 into_tile;
	Uint8 state;
	Uint16 index; //The location in the particle system
} terraform_struct;

extern terraform_struct * terr_map;

void terraform(int tile_pos, int type);
void terraform_control();

#endif
