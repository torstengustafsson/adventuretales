#include <emscripten.h>
#include "core/inc/AdventureTales.h"

//Time variables shared globally (see Globals.h).
float curr_time = 0;
float curr_dt = 0;
bool quit = false;
std::string data_path = "../data";

AdventureTales the_game;

void main_loop()
{
	the_game.run();
	emscripten_cancel_main_loop();
}

int main( int argc, char* args[] )
{
	emscripten_set_main_loop(main_loop, 60, 1);
	
	return 0;
}