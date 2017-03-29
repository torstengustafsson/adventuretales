#include "GameController.h"

GameController::GameController(Player* _player, Resources* _res)
{
	resources = _res;
	player = _player;
	
	map_handler = unique_ptr<MapHandler>(new MapHandler(resources, bind(&GameController::get_objects, this)));
	player_data = unique_ptr<PlayerData>(new PlayerData(resources));
	menus["worldmenu"] = unique_ptr<Menu>(new MenuWorld(
						resources,
						player_data.get(), 
						bind(&GameController::set_game_paused, this, _1, _2 )
				 ) );
	menus["interactionmenu"] = unique_ptr<Menu>(new InteractionMenu(
						resources,
						bind(&GameController::set_game_paused, this, _1, _2 )
				 ) );
	
	input_handler = unique_ptr<InputHandler>(new InputHandler(
						bind(&GameController::set_game_paused, this, _1, _2),
						bind(&GameController::interact, this, _1, _2),
						player )
	);
	
	set_map(1);
	
	//Generate two test characters
	int id = player_data->add_character("Archer");
	for(int i = 0; i++ < 7;)
		get_character(id)->increase_level();
	id = player_data->add_character("Viking");
	get_character(id)->add_experience(4700);
	get_character(id)->add_trait("Likes Axes");
	get_character(id)->add_item("Iron Sword");
	get_character(id)->add_item("Steel Helmet");
	get_character(id)->add_item("Healing Potion");
	get_character(id)->add_item("Fireball Scroll");
	get_character(id)->remove_item("Steel Helmet");
	get_character(id)->add_hp(-get_character(id)->get_hit_points_max() / 3);
	cout << get_character(id)->get_name() << "'s inventory:\n";
	Texture* item_icon;
	string item_name;
	string item_type;
	string item_inner_type;
	int item_value;
	for( auto& i : get_character(id)->get_inventory() )
	{
		tie(item_icon, item_name, item_type, item_inner_type, item_value) = i;
		cout << "  '" << item_name << "' Type: " << item_type << " - " << item_inner_type << "\n"; 
	}
	const auto& characters = player_data->get_characters();
	if(dynamic_cast<Viking*>(characters[0].get()))
		player->change_texture(resources->get_texture("../data/sprites/world/characters/character_viking.png"));
	if(dynamic_cast<Archer*>(characters[0].get()))
		player->change_texture(resources->get_texture("../data/sprites/world/characters/character_archer.png"));
	//if(dynamic_cast<Knight*>(characters[0].get()))
	//	player->change_texture(resources->get_texture("../data/sprites/world/characters/character_knight.png"));
	cout << "\n";
}

// Change the currently loaded map to the map specified by the argument val.
// Objects state in previously loaded maps are still stored in the MapHandler object. 
void GameController::set_map(int val)
{
	load_time = true;
	int player_start_x, player_start_y;
	
	//Load the current map
	vector<Object*> v = map_handler->get_map(val, player_start_x, player_start_y);
	
	//Check if player comes from a door
	if(door_teleport_x != -1)
	{
		player->set_x_tile(door_teleport_x);
		player->set_y_tile(door_teleport_y);
	}
	else
	{
		player->set_x_tile(player_start_x);
		player->set_y_tile(player_start_y);
	}
	
	player->set_x(player->get_x_tile() * 32);
	player->set_y(player->get_y_tile() * 32);
	
	object_list.clear(); //MapHandler handles removal of the actual objects. We just need to clear pointers.
	copy(v.begin(), v.end(), back_inserter(object_list));
	object_list.push_back(player);
	
	door_locations.clear();
	for (auto& o : object_list)
		if(Door* d = dynamic_cast<Door*>(o))
			door_locations.push_back(d);
}

// Returns a vector containing the objects close enough to player to fit the screen.
vector<Object*> GameController::get_objects()
{
	vector<Object*> nearby_objects;
	
	copy_if(object_list.begin(), object_list.end(), back_inserter(nearby_objects),
		[this](Object* const & o)
		{
			return player->get_x_tile() > o->get_x_tile() - 15 &&
				   player->get_x_tile() < o->get_x_tile() + 15 &&
				   player->get_y_tile() > o->get_y_tile() - 12 &&
				   player->get_y_tile() < o->get_y_tile() + 12;
		});
	
	return nearby_objects;
}

Menu* GameController::get_active_menu()
{
	for( auto& m : menus )
		if( m.second->is_visible() )
		{
			return m.second.get();
		}
	return nullptr;
}

// Interact with the object at position (x, y).
void GameController::interact(int x, int y)
{
	//a moving player is busy
	if(player->get_moving())
		return;
	for(auto o : get_objects())
	{
		if(x == o->get_x_tile() && y == o->get_y_tile())
		{
			//send opposite direction as argument
			int dir = player->get_direction();
			auto npc = dynamic_cast<NPC*>(o);
			if(npc && npc->generates_dialogues())
			{
				npc->set_dialogue(diag.generate_dialogue(o->get_name(), npc->get_personality(), 
						npc->get_annoyed_level(), player_data->get_main_character()));
			}
			string interaction = o->interact(dir + (dir % 2 == 0 ? -1 : 1) );
			if(interaction != "")
			{
				if(auto mo = dynamic_cast<MovingObject*>(o))
				{
					//a moving object (that is currently moving) is busy
					if(mo->get_moving())
						return;
					mo->animate();
				}
				auto interaction_menu = dynamic_cast<InteractionMenu*>(menus["interactionmenu"].get());
				interaction_menu->set_text(o->get_name(), interaction);
				set_game_paused(true, "InteractionMenu");
			}
			if(auto enemy = dynamic_cast<Enemy*>(o))
			{
				enemy->set_x(enemy->get_x());
				//TODO: Initiate battle
				cout << "Battle commencing!\n";
			}
		}
	}
}

// caller can be: "GameController", "MenuWorld", "InteractionMenu"
void GameController::set_game_paused(bool val, string caller)
{
	player->animate();
	game_paused = val;
	input_handler->reset_state();
	if(caller == "GameController" || caller == "MenuWorld")
		menus["worldmenu"]->set_visible(val);
	if(caller == "InteractionMenu")
		menus["interactionmenu"]->set_visible(val);
}

// Helper function to shorten get character command
unique_ptr<Character> const& GameController::get_character(int i)
{
	return player_data->get_character(i);
}

bool GameController::paused()
{
	return game_paused;
}

bool GameController::loadtime()
{
	return load_time;
}

void GameController::frame()
{
	//one frame load time is enough
	load_time = false;
	
	//check if player entered a door
	for(auto& d : door_locations)
	{
		if(!player->get_moving() && player->get_x_tile() == d->get_x_tile() && player->get_y_tile() == d->get_y_tile())
		{
			player->move(0); //override player movement
			door_teleport_x = d->get_door_x_tile();
			door_teleport_y = d->get_door_y_tile();
			set_map(d->get_door_map());
		}
	}
	
	
	if(!game_paused && !load_time)
	{
		player->perform_actions();
		
		//handle keyboard input
		input_handler->handle_input();
		
		//handle per-frame computation for NPCs
		for(auto& o : get_objects())
		{
			if( NPC* n = dynamic_cast<NPC*>(o) )
				n->frame();
			else if( Enemy* e = dynamic_cast<Enemy*>(o) )
			{
				int p_x = player->get_x_tile();
				int p_y = player->get_y_tile();
				int e_x = e->get_x_tile();
				int e_y = e->get_y_tile();
				//check if enemy is adjacent to player
				if( (p_x == e_x && ( p_y == e_y-1 || p_y == e_y+1 )) || ((p_x == e_x-1 || p_x == e_x+1) && p_y == e_y) )
				{
					player->set_direction( p_x > e_x ? 1 : ( p_x < e_x ? 2: ( p_y < e_y ? 3 : 4 ) ) );
					interact(e_x, e_y);
				}
				e->frame(player->get_x_tile(), player->get_y_tile());
			}
		}
	}
	
	curr_dt = static_cast<float>(SDL_GetTicks()) / 1000 - curr_time;
	curr_time = static_cast<float>(SDL_GetTicks()) / 1000;
	//cout << curr_dt << "\n";
}