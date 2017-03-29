#include "Menu.h"

Menu::Menu(Resources* _res, function<void(bool, string)> _set_game_paused)
{
	resources = _res;
	set_game_paused = _set_game_paused;
}

const bool Menu::is_visible()
{
	return visible;
}

void Menu::set_visible(const bool val)
{
	visible = val;
}


void Menu::set_screen_dim(int w, int h)
{
	screen_w = w;
	screen_h = h;
	resize();
}

const int Menu::scale_x(const int val)
{
	return val * screen_w / 800;
}

const int Menu::scale_y(const int val)
{
	return val * screen_h / 600;
}