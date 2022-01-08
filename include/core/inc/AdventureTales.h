
#include "Globals.h"
#include "GameRenderer.h"
#include "GameController.h"
#include "GameEngine.h"
#include "Resources.h"
#include "world/inc/Object.h"
#include "world/inc/Player.h"
#include "world/inc/Camera.h"
#include "menu/inc/MenuWorld.h"
#include "menu/inc/MenuBattle.h"

#include <memory>

class AdventureTales
{
public:
	AdventureTales();

	void run();

private:
	//Game renderer class controls SDL window and renderer
	unique_ptr<GameRenderer> game_renderer;

	//Game controller handles game logic.
	unique_ptr<GameController> game_controller;

	//Game engine handles collisions and movement of objects
	unique_ptr<GameEngine> game_engine;

	//Resources handles storage of textures and sounds
	unique_ptr<Resources> resources;

	//The player object is passed around to handler classes so pointer type is recommended
	unique_ptr<Player> player;

	//Camera class handles viewport (centers player on screen)
	unique_ptr<Camera> camera;

	//Menu classes handles the different ingame menus
	unique_ptr<MenuWorld> menu_world;
	unique_ptr<MenuBattle> menu_battle;

	SDL_Event e;

	bool quit = false;
};
