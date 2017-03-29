#pragma once

#include "../core/Globals.h"
#include "../core/sdl_deleter.h"

#include <memory>

//Texture wrapper class
class Texture
{
public:
	//Initializes variables
	Texture( SDL_Renderer* _renderer );
	Texture( SDL_Renderer* _renderer, std::string path );

	//Loads image at specified path
	bool loadFromFile( std::string path );

	//Renders texture at given point
	void render( int x, int y, float size = 1.0 );
	
	//Same as above, but renders a part of a sprite sheet
	void render( int x, int y, SDL_Rect* clip, float size = 1.0 );

	void set_screen_dim(int w, int h);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:	
	//The actual hardware texture
	unique_ptr<SDL_Texture, sdl_deleter> texture;
	SDL_Renderer* renderer;
	//Image dimensions
	int width;
	int height;
	
	int screen_width = 800;
	int screen_height = 600;
};
