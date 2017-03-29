#include "core/AdventureTales.h"

//Time variables shared globally (see Globals.h).
float curr_time = 0;
float curr_dt = 0;
bool quit = false;

int main( int argc, char* args[] )
{
	AdventureTales the_game;
	the_game.run();
	
	return 0;
}