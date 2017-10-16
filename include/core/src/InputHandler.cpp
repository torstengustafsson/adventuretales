#include "core/inc/InputHandler.h"

// GameController
InputHandler::InputHandler(function<void(bool, string)> _set_game_paused, function<void(int, int)> _interact, 
		Player* _player)
{
	set_game_paused = _set_game_paused;
	interact = _interact;
	player= _player;
}

void InputHandler::reset_state()
{
	return_pressed = true;
	space_pressed = true;
}

void InputHandler::handle_input()
{
	const Uint8 *keyState = SDL_GetKeyboardState(NULL);

	if( keyState[SDL_SCANCODE_LEFT] )
	{
		player->move(1);
	}
	if( keyState[SDL_SCANCODE_RIGHT] )
	{
		player->move(2);
	}
	if( keyState[SDL_SCANCODE_DOWN] )
	{
		player->move(3);
	}
	if( keyState[SDL_SCANCODE_UP] )
	{
		player->move(4);
	}
	if(!keyState[SDL_SCANCODE_LEFT] && !keyState[SDL_SCANCODE_RIGHT] && !keyState[SDL_SCANCODE_DOWN] && !keyState[SDL_SCANCODE_UP])
	{
		player->move(0);
	}
	if( keyState[SDL_SCANCODE_SPACE] )
	{
		if(!space_pressed)
		{
			//interact with the tile in front of player
			switch(player->get_direction())
			{
				case 1:
					interact(player->get_x_tile() - 1, player->get_y_tile());
					break;
				case 2:
					interact(player->get_x_tile() + 1, player->get_y_tile());
					break;
				case 3:
					interact(player->get_x_tile(), player->get_y_tile() + 1);
					break;
				case 4:
					interact(player->get_x_tile(), player->get_y_tile() - 1);
					break;
			}
		}
	}
	else
		space_pressed = false;

	if( keyState[SDL_SCANCODE_RETURN] )
	{
		if(!return_pressed)
		{
			//Open menu
			set_game_paused(true, "GameController");
		}
	}
	else
		return_pressed = false;
}