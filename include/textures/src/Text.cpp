#include "textures/inc/Text.h"

Text::Text( SDL_Renderer* _renderer, string _text, int size, bool bold )
{
    //Initialize
    texture = NULL;
	renderer = _renderer;
	text = _text;
	
	set_font(size, bold);
	
    width = 0;
    height = 0;
	
	SDL_Color textColor = { 0, 0, 0 };
	loadFromRenderedText(text, textColor);
}

bool Text::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	texture.reset();
    
	//Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Blended( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        texture = unique_ptr<SDL_Texture, sdl_deleter>(
						SDL_CreateTextureFromSurface( renderer, textSurface ),
						sdl_deleter()
					 );
		
        if( texture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            width = textSurface->w;
            height = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    
    //Return success
    return texture != NULL;
}

void Text::render( int x, int y, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, 
			static_cast<int>( ceil(width * screen_width / 800) ), 
			static_cast<int>( ceil(height * screen_height / 600) ) 
	};
	SDL_RendererFlip flipType = SDL_FLIP_NONE;
    SDL_RenderCopyEx( renderer, texture.get(), NULL, &renderQuad, 0, NULL, flipType );
}

void Text::set_font(int size, bool bold)
{
	string path;
	if(!bold) path = data_path + "/fonts/imperator/Imperator.ttf";
	else 	  path = data_path + "/fonts/imperator/Imperator Bold.ttf";
	gFont = TTF_OpenFont( path.c_str(), size );
	
	if( gFont == NULL )
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
}

void Text::set_screen_dim(int w, int h)
{
	screen_width = w;
	screen_height = h;
}

int Text::getWidth()
{
    return width;
}

int Text::getHeight()
{
    return height;
}