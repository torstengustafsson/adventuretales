#include "core/inc/AdventureTales.h"


AdventureTales::AdventureTales()
{
	game_renderer = unique_ptr<GameRenderer>(new GameRenderer());
	
	if( !game_renderer->init() )
    {
        printf( "Failed to initialize!\n" );
		quit = true;
    }
	
	resources = unique_ptr<Resources>(new Resources(game_renderer->get_renderer()));
	
	//The player object is the only object that is not bound to any map
	player = unique_ptr<Player>(new Player(
		resources->get_texture("../data/sprites/world/characters/character_archer.png"), 
		"player",	//name
		0,0,0,0,	//positions are set after map loaded
		game_renderer->get_width() / 2 - 16,	//camera x position
		game_renderer->get_height() / 2 - 16,	//camera y position
		SDL_Rect{0,0,32,32}	//coordinates for spritesheet
	));
	
	
	camera = unique_ptr<Camera>(new Camera(player.get()));
	game_controller = unique_ptr<GameController>(new GameController(player.get(), resources.get()));
	game_engine = unique_ptr<GameEngine>(new GameEngine(player.get()));
}

void AdventureTales::run()
{
	//While application is running
	while( !quit )
	{
		//User requests quit
		while( SDL_PollEvent( &e ) != 0 )
			if( e.type == SDL_QUIT )
				quit = true;

		//Handle game logic such as spawning new objects and events
		game_controller->frame();
		
		//Handle object movements and collisions
		if( !game_controller->paused() )
			game_engine->frame(game_controller->get_objects());
		
		//Transform objects to fit player camera
		camera->set_view(game_controller->get_objects(), game_renderer->get_width(), game_renderer->get_height());
		
		//Render scene
		if(!game_controller->loadtime())
			game_renderer->render_frame(game_controller->get_objects(), game_controller->get_active_menu());
		
		//cout << "FPS: " << 1 / curr_dt << "\n"; 
	}
	
    return;
}