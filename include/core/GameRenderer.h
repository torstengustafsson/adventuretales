#pragma once

#include "Globals.h"
#include "sdl_deleter.h"
#include "../world/Object.h"
#include "../menu/Menu.h"

#include <vector>
#include <memory>



class GameRenderer
{
public:
	GameRenderer() = default;
	~GameRenderer();
	
	int get_width();
	int get_height();
	
	bool init();
	void close();
	
	SDL_Renderer* get_renderer();
	
	void render_frame(vector<Object*> v, Menu* active_menu = nullptr);

	void clear_frame();
	void update_screen();

	void render_object(Object* o);

private:
	unique_ptr<SDL_Window, sdl_deleter> game_window;
	unique_ptr<SDL_Renderer, sdl_deleter> game_renderer;
	
	int SCREEN_WIDTH = 800;
	int SCREEN_HEIGHT = 600;
};