#include "menu/inc/MainMenu.h"

MainMenu::MainMenu(Resources* _res, PlayerData* _pd, function<void(bool, string)> _set_game_paused)
	: Menu(_res, _set_game_paused)
{
	player_data = _pd;
}

void MainMenu::render()
{
	Texture* menu = resources->get_texture("../data/sprites/menu/main_menu.png");
	menu->render(0, 0);
}

void MainMenu::handle_action()
{
	if(marked_pos == 0)
	{
		//do stuff
	}
	if(marked_pos == 1)
	{
		//do stuff
	}
	if(marked_pos == 2)
	{
		//do stuff
	}
	if(marked_pos == 3)
	{
		//do stuff
	}
	if(marked_pos == 4)
		quit = true;
}

void MainMenu::handle_input()
{
	const Uint8 *keyState = SDL_GetKeyboardState(NULL);
	if( keyState[SDL_SCANCODE_DOWN] )
	{
		if(!button_pressed)
		{
			//do stuff
		}
		button_pressed = true;
	}
	else if( keyState[SDL_SCANCODE_UP] )
	{
		if(!button_pressed)
		{
			//do stuff
		}
		button_pressed = true;
	}
	else if( keyState[SDL_SCANCODE_SPACE] )
	{
		if(!button_pressed)
		{
			//do stuff
		}
		button_pressed = true;
	}
	else
	{
		button_pressed = false;
	}
}

void MainMenu::set_visible(bool val)
{
	marked_pos = 0;
	button_pressed = true;
	visible = val;
}