#pragma once

#include "Globals.h"
#include "../world/Player.h"

#include <functional>

class InputHandler
{
public:
	InputHandler( function<void(bool, string)> _set_game_paused, function<void(int, int)> _interact, 
			Player* _player );
	
	void handle_input();
	
	void reset_state();
	
private:
	Player* player;
	function<void(bool, string)> set_game_paused;
	function<void(int, int)> interact;
	bool menu_open = false; //used to decide if menu should open or close.
	bool return_pressed = true; //is true as long as key is held down.
	bool space_pressed = true;	//used to prevent instant closing/opening.
	function<void(bool)> set_visible;
};