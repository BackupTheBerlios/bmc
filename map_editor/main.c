
#include "global.h"

/**********************************************************************/

static int last_save_time=0;
int limit_fps=0;

int start_rendering()
{
    int done = 0;
	/* Loop until done. */
	while( !done ) {
		
		SDL_Event event;
		/* Check if there's a pending event. */
		
		while( SDL_PollEvent( &event ) )
        		{
				done = HandleEvent(&event);
			}

    		get_world_x_y();
		if(!limit_fps || ((cur_time - last_time) && (800/(cur_time-last_time) < (Uint32)limit_fps)))
			{
				draw_scene();
				last_time=cur_time;
			}
		else SDL_Delay(1);
		draw_scene();
		
		if(auto_save_time && (cur_time-last_save_time)>(Uint32)auto_save_time)
			{
				printf("saving map...\n");
				last_save_time=cur_time;
				save_map("maps/Autosave.bmm");
			}
	
#ifdef LINUX
		while (gtk_events_pending())
			gtk_main_iteration();
#endif		
	}


	/* Destroy our GL context, etc. */ 
	destroy_map_tiles();
	SDL_SetTimer(0,NULL);
	end_particles_list();
	SDL_Quit( );
	return(0);
}

int Main(int argc, char *argv[])
{
  
        //int i
  	int logo;
	int numtests;
	//int bpp = 0;
	int slowly;
	//float gamma = 0.0;
	//int noframe = 1;

	logo = 1;
	slowly = 1;
	numtests = 1;

#ifdef	LINUX
	gtk_set_locale ();
	gtk_init (&argc, &argv);
#endif	//LINUX
	init_stuff();
	
	start_rendering();

	return 0;
}

#ifdef LINUX
int main(int argc, char *argv[])
{
  return Main(argc, argv);
}
#endif

#ifndef LINUX
int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow)
{
Main(0, NULL);
  return 0;
}
#endif
