#include "core/inc/GameRenderer.h"

bool GameRenderer::init()
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
	//Create window
	game_window = unique_ptr<SDL_Window, sdl_deleter>(
					SDL_CreateWindow( "Adventure Tales", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
						SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE ),
					sdl_deleter()
				  );
	
	if( game_window == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
	
	//Create renderer for window
	game_renderer =	unique_ptr<SDL_Renderer, sdl_deleter>(
						SDL_CreateRenderer( game_window.get(), -1, 
							SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ),
						sdl_deleter()
					);

	if( game_renderer.get() == NULL )
	{
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
		//Initialize renderer color
		SDL_SetRenderDrawColor( game_renderer.get(), 0x00, 0x00, 0x00, 0xFF );

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}
	
	//Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		return false;
	}

    return true;
}

GameRenderer::~GameRenderer()
{
	close();
}

void GameRenderer::close()
{
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Renderer* GameRenderer::get_renderer()
{
	return game_renderer.get();
}

int GameRenderer::get_width()
{
	return SCREEN_WIDTH;
}

int GameRenderer::get_height()
{
	return SCREEN_HEIGHT;
}

void GameRenderer::render_frame(vector<Object*> v, Menu* active_menu)
{
	SCREEN_WIDTH = SDL_GetWindowSurface(game_window.get())->w;
	SCREEN_HEIGHT = SDL_GetWindowSurface(game_window.get())->h;
	
	//Clear screen
	SDL_RenderClear( game_renderer.get() );

	vector<Object*> foreground_objects;
	//Render texture to screen
	for(auto o : v)
	{
		o->set_screen_dim(SCREEN_WIDTH, SCREEN_HEIGHT);
		if(o->get_name() == "foreground")
		{
			foreground_objects.push_back(o);
			continue;
		}
		//TODO: Pass width and height to allow resizing
		o->render();
	}
	for( auto o : foreground_objects )
		o->render();
	
	//Render menu last
	if(active_menu != nullptr && active_menu->is_visible())
	{
		active_menu->set_screen_dim(SCREEN_WIDTH, SCREEN_HEIGHT);
		active_menu->render();
	}

	//Update screen
	SDL_RenderPresent( game_renderer.get() );
}

void GameRenderer::clear_frame()
{
	SDL_RenderClear( game_renderer.get() );
}

void GameRenderer::update_screen()
{
	SDL_RenderPresent( game_renderer.get() );
}

void GameRenderer::render_object(Object* o)
{
	o->render();
}