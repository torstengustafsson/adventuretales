#pragma once

#include "../core/Globals.h"
#include "../core/Resources.h"
#include "../textures/Text.h"

#include <vector>
#include <map>
#include <memory>
#include <functional>

//using namespace std::placeholders;

class Menu
{
public:
	virtual ~Menu() = default;
	virtual void render() = 0;

	const bool is_visible();
	virtual void set_visible(const bool val);
	
	void set_screen_dim(int w, int h);
	virtual void resize() = 0;
	
protected:
	Menu(Resources* _res, function<void(bool, string)> _set_game_paused);
	Resources* resources;

	//callback to GameController to unpause game when neccessary.
	function<void(bool, string)> set_game_paused;

	bool visible = false;
	
	int screen_w = 800;
	int screen_h = 600;
	const int scale_x(const int val);
	const int scale_y(const int val);
};