#pragma once

#include "Globals.h"
#include "Resources.h"
#include "MapHandler.h"
#include "PlayerData.h"
#include "InputHandler.h"
#include "DialogueGenerator.h"
#include "../world/Object.h"
#include "../world/NPC.h"
#include "../world/Enemy.h"
#include "../world/Door.h"
#include "../menu/MenuWorld.h"
#include "../menu/InteractionMenu.h"
#include "../world/Player.h"

#include <algorithm>
#include <vector>
#include <memory>
#include <map>
#include <functional>

using namespace std::placeholders;

class GameController
{
friend class InputHandler;
public:
	GameController(Player* _player, Resources* _res);
	
	void frame();
	void set_map(int val);
	vector<Object*> get_objects();
	Menu* get_active_menu();
	bool paused();
	
	bool loadtime();
	
private:
	vector<Object*> object_list;
	vector<Door*> door_locations; //instead of searching the whole object list every frame
	Resources* resources;
	
	enum game_states
	{
		WORLD,
		BATTLE
	};
	
	bool game_paused = false; //becomes true when menu is open etc.
	bool world_or_battle = WORLD; //decides which game mode is currently active
	bool load_time = false;	//used to prevent ugly visuals during map change, for example. Pauses game for one frame.
	
	unique_ptr<MapHandler> map_handler;
	unique_ptr<InputHandler> input_handler;
	unique_ptr<PlayerData> player_data;
	unique_ptr<Character> const& get_character(int i);
	
	map<string, unique_ptr<Menu>> menus;
	unique_ptr<MenuWorld> menu_world;
	
	Player* player;
	
	//when player will teleport to the location stored in these variables, after entering a door
	int door_teleport_x = -1;
	int door_teleport_y = -1;
		
	DialogueGenerator diag;
	
	void interact(int x, int y);
	void set_game_paused(bool val, string caller);
};