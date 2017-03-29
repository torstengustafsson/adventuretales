#pragma once

#include "../core/Globals.h"
#include <SDL_ttf.h>
#include "../core/sdl_deleter.h"

#include <memory>

//Texture wrapper class
class Text
{
public:
	//Initializes variables
	Text( SDL_Renderer* _renderer, std::string path, int size, bool bold );

	//Creates image from font string
	bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

	//Renders texture at given point
    void render( int x, int y, SDL_Point* center = NULL, 
			SDL_RendererFlip flip = SDL_FLIP_NONE );
	
	//Gets image dimensions
	int getWidth();
	int getHeight();
	
	void set_screen_dim(int w, int h);
	
	void set_font(int size, bool bold);

private:	
	//The actual hardware texture
	unique_ptr<SDL_Texture, sdl_deleter> texture;
	SDL_Renderer* renderer;
	
	//The text string
	string text;
	
	//Image dimensions
	int width;
	int height;
	
	int screen_width = 800;
	int screen_height = 600;
	
	//Globally used font
	TTF_Font *gFont = TTF_OpenFont( "./data/fonts/imperator/Imperator.ttf", 24 );
};
