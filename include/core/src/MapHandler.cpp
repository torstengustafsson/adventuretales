#include "core/inc/MapHandler.h"

MapHandler::MapHandler(Resources* _res, function<vector<Object*>()> _get_objects)
{
	resources = _res;
	get_objects = _get_objects;
	
	//Initialize array. Note that many elements are left empty. This is to allow extendibility.
	tiles.fill("BAD TILE"); 

	//Background tiles
	int bt = 0;
	tiles[bt++] = "../data/sprites/world/background/floor_wood.png";
	tiles[bt++] = "../data/sprites/world/background/ground_dirt.png";
	tiles[bt++] = "../data/sprites/world/background/ground_grass.png";
	tiles[bt++] = "../data/sprites/world/background/ground_grass_dirt_1.png";
	tiles[bt++] = "../data/sprites/world/background/ground_grass_dirt_2.png";
	tiles[bt++] = "../data/sprites/world/background/ground_grass_dirt_3.png";
	tiles[bt++] = "../data/sprites/world/background/ground_grass_dirt_4.png";
	tiles[bt++] = "../data/sprites/world/background/ground_grass_dirt_crossroad.png";
	tiles[bt++] = "../data/sprites/world/background/ground_grass_dirt_patch.png";
	tiles[bt++] = "../data/sprites/world/background/ground_grass_dirt_road_down.png";
	tiles[bt++] = "../data/sprites/world/background/ground_grass_dirt_road_right.png";
	tiles[bt++] = "../data/sprites/world/background/ground_grass_dirt_turn_1.png";
	tiles[bt++] = "../data/sprites/world/background/ground_grass_dirt_turn_2.png";
	tiles[bt++] = "../data/sprites/world/background/ground_grass_dirt_turn_3.png";
	tiles[bt++] = "../data/sprites/world/background/ground_grass_dirt_turn_4.png";
	tiles[bt++] = "../data/sprites/world/background/chair_left.png";
	tiles[bt++] = "../data/sprites/world/background/chair_right.png";
	tiles[bt++] = "../data/sprites/world/background/chair_down.png";
	
	//Collider tiles
	int ct = 100;
	tiles[ct++] = "../data/sprites/world/colliders/wall.png";
	tiles[ct++] = "../data/sprites/world/colliders/ground_bush.png";
	tiles[ct++] = "../data/sprites/world/colliders/ground_stump.png";
	tiles[ct++] = "../data/sprites/world/colliders/ground_tree_base.png";
	tiles[ct++] = "../data/sprites/world/colliders/house_bot.png";
	tiles[ct++] = "../data/sprites/world/colliders/house_bot_left.png";
	tiles[ct++] = "../data/sprites/world/colliders/house_bot_right.png";
	tiles[ct++] = "../data/sprites/world/colliders/house_left.png";
	tiles[ct++] = "../data/sprites/world/colliders/house_mid.png";
	tiles[ct++] = "../data/sprites/world/colliders/house_right.png";
	tiles[ct++] = "../data/sprites/world/colliders/house_top.png";
	tiles[ct++] = "../data/sprites/world/colliders/house_top_left.png";
	tiles[ct++] = "../data/sprites/world/colliders/house_top_right.png";
	tiles[ct++] = "../data/sprites/world/colliders/house_roof.png";
	tiles[ct++] = "../data/sprites/world/colliders/house_roof_left.png";
	tiles[ct++] = "../data/sprites/world/colliders/house_roof_right.png";
	tiles[ct++] = "../data/sprites/world/colliders/table_left.png";
	tiles[ct++] = "../data/sprites/world/colliders/table_middle.png";
	tiles[ct++] = "../data/sprites/world/colliders/table_right.png";
	tiles[ct++] = "../data/sprites/world/colliders/table_bardisk_down.png";
	tiles[ct++] = "../data/sprites/world/colliders/table_bardisk_edge_leftdown.png";
	tiles[ct++] = "../data/sprites/world/colliders/table_bardisk_edge_rightdown.png";
	tiles[ct++] = "../data/sprites/world/colliders/table_bardisk_left.png";
	tiles[ct++] = "../data/sprites/world/colliders/table_bardisk_leftup.png";
	tiles[ct++] = "../data/sprites/world/colliders/table_bardisk_middle.png";
	tiles[ct++] = "../data/sprites/world/colliders/table_bardisk_middle_down.png";
	tiles[ct++] = "../data/sprites/world/colliders/table_bardisk_right.png";
	tiles[ct++] = "../data/sprites/world/colliders/table_bardisk_rightup.png";
	tiles[ct++] = "../data/sprites/world/colliders/table_bardisk_up.png";
	
	//Foreground tiles
	int ft = 200;
	tiles[ft++] = "../data/sprites/world/foreground/ground_tree_bot_left.png";
	tiles[ft++] = "../data/sprites/world/foreground/ground_tree_bot_right.png";
	tiles[ft++] = "../data/sprites/world/foreground/ground_tree_top_left.png";
	tiles[ft++] = "../data/sprites/world/foreground/ground_tree_top_right.png";
	tiles[ft++] = "../data/sprites/world/colliders/ground_tree_bot.png";
	tiles[ft++] = "../data/sprites/world/colliders/ground_tree_trunk.png";
	tiles[ft++] = "../data/sprites/world/colliders/ground_tree_top.png";
	tiles[ft++] = "../data/sprites/world/foreground/house_roof_left.png";
	tiles[ft++] = "../data/sprites/world/foreground/house_roof_right.png";
	tiles[ft++] = "../data/sprites/world/foreground/house_roof_top.png";
	tiles[ft++] = "../data/sprites/world/foreground/sign_store.png";
	tiles[ft++] = "../data/sprites/world/foreground/sign_inn.png";
	
	//Door tiles
	tiles[300] = "../data/sprites/world/doors/door.png";
	tiles[301] = "../data/sprites/world/doors/house_door.png";
}

void delete_pointed_object(Object* const ptr)
{
	delete ptr;
}

void remove_map(pair<int, vector<Object*>> const map)
{
    for_each(map.second.begin(), map.second.end(), delete_pointed_object);
}

MapHandler::~MapHandler()
{
	for_each(maps.begin(), maps.end(), remove_map);
}

void MapHandler::add_tile(int val, string path, int x_tile, int y_tile, string name)
{
	maps[val].push_back( new Object(resources->get_texture(path), name, x_tile, y_tile) );
}

//each specific door have its own unique door_index
void MapHandler::add_door_tile(int val, int door_index, string path, int x_tile, int y_tile, string name)
{
	int leads_to_map = 1, leads_to_x = 20, leads_to_y = 20;

	if(val == 1)
	{
		if(door_index == 1)
		{
			//TODO
			leads_to_map = 1;
			leads_to_x = 20;
			leads_to_y = 20;
		}
		if(door_index == 1)
		{
			leads_to_map = 2;
			leads_to_x = 3;
			leads_to_y = 6;
		}
		if(door_index == 2)
		{
			leads_to_map = 3;
			leads_to_x = 3;
			leads_to_y = 8;
		}
	}
	else if(val == 2)
	{
		//all door lead to same spot
		leads_to_map = 1;
		leads_to_x = 28;
		leads_to_y = 12;
	}
	else if(val == 3)
	{
		//all door lead to same spot
		leads_to_map = 1;
		leads_to_x = 22;
		leads_to_y = 18;
	}
	else
	{
		leads_to_map = 1;
		leads_to_x = 20;
		leads_to_y = 20;
	}
	maps[val].push_back( new Door(resources->get_texture(path), name, x_tile, y_tile, 
		leads_to_map, leads_to_x, leads_to_y) );
}

void MapHandler::load_tiles(int val, string suffix)
{
	// Read map from .csv file
	string line;
	ifstream file;
	
	string filename = "../data/maps/map" + to_string(val) + "_" + suffix + ".csv";
	file.open(filename);
	
	
	if(file.is_open())
	{
		int counter_y = 0;
		int door_counter = 0;
		
		while(getline(file, line))
		{
			stringstream ss(line);
			int i;
			int counter_x = 0;
			
			while( ss >> i )
			{
				if( i >= 0 && i < 100)
				{
					add_tile(val, tiles[i],
						counter_x, counter_y, "background");
				}
				if( i >= 100 && i < 200)
				{
					add_tile(val, tiles[i],
						counter_x, counter_y, "tile_collider");
				}
				if( i >= 200 && i < 300)
				{
					add_tile(val, tiles[i],
						counter_x, counter_y, "foreground");
				}
				if( i >= 300 && i < 310)
				{
					add_door_tile(val, door_counter++, tiles[i],
						counter_x, counter_y, "door");
				}
				
				counter_x++;
				
				//Skip commas
				if (ss.peek() == ',')
					ss.ignore();
			}
			counter_y++;
		}
	}
	else
		cout << "Error. Can't open" << filename << ".\n";
	
	file.close();
}

vector<Object*> MapHandler::get_map(int val, int& start_x, int& start_y)
{
	//Create if not exist
	if ( maps.find(val) == maps.end() )
	{
		load_tiles(val, "background");
		load_tiles(val, "colliders");
		load_tiles(val, "foreground");
		
		string path1 = "../data/sprites/world/characters/NPC_villager1.png";
		string path2 = "../data/sprites/world/characters/NPC_nohair.png";
		string path3 = "../data/sprites/world/characters/base.png";
		
		if(val == 1)
		{
			for(int i = 0; i < 10; i++)
			for(int j = 0; j < 3; j++)
			{
				short int npc = generateRand() % 3;
				maps[val].push_back(
					new NPC(resources->get_texture(npc == 0 ? path1 : npc == 1 ? path2 : path3), 
						"NPC name will be generated later", 22 + i, 20 + j, 2)
				);
			}
			for(int i = 0; i < 10; i++)
			{
				maps[val].push_back(
				new Enemy(resources->get_texture("../data/sprites/world/characters/enemy_orc.png"), 
					"An Evil Greenskin", 60 + generateRand() % 20, generateRand() % 30, 2, get_objects)
				);
			}
		}
		if(val == 2)
		{
			maps[val].push_back(
				new NPC(resources->get_texture(path1), 
					"Kurt", 2, 2, 0, "Yo. I'm Kurt.")
			);
			maps[val].push_back(
				new NPC(resources->get_texture(path3), 
					"Awesome Tim", 5, 5, 1, "Hello. There are some who call me Tim. I may look like Super Mario, but i'm actually a Jedi Master from the lands of Mordor. When I'm not out in the night, preventing crime from hateful scumbags, I usually take a nap and play with my turtles.")
			);
		}
		if(val == 3)
		{
			maps[val].push_back(
				new NPC(resources->get_texture(path2), 
					"Tom", 7, 2, 0, "Sup? I'm Tom the Bartender. For 10 gold coins, I'll let you rent a room here, so you may rest your tired bones!")
			);
			maps[val].push_back(
				new NPC(resources->get_texture(generateRand() % 3 == 0 ? path1 : generateRand() % 3 == 1 ? path2 : path3), 
					"NPC name will be generated later", 2, 4, 0)
			);
			maps[val].push_back(
				new NPC(resources->get_texture(generateRand() % 3 == 0 ? path1 : generateRand() % 3 == 1 ? path2 : path3), 
					"NPC name will be generated later", 12, 4, 2)
			);
			maps[val].push_back(
				new NPC(resources->get_texture("../data/sprites/world/characters/character_knight.png"), 
					"A Cool Knight", 11, 7, 1, "Hello my dear comrade! I'm a knight!!")
			);
			maps[val].push_back(
				new NPC(resources->get_texture("../data/sprites/world/characters/character_viking.png"), 
					"A Dangerous Viking", 2, 7, 1, "Better watch your step, or you might find my axe buried in your skull!")
			);
			maps[val].push_back(
				new NPC(resources->get_texture("../data/sprites/world/characters/character_archer.png"), 
					"A Sharp-looking Archer", 3, 2, 1, "I can hit a mouse between the eyes from 1.26 miles away!")
			);
			maps[val].push_back(
				new NPC(resources->get_texture("../data/sprites/world/characters/enemy_orc.png"), 
					"A Greenskin", 11, 1, 1, "Waarrg! Hugha bugh!")
			);
		}
	}
	
	// For now, start positions are hardcoded. Maybe add them to the map file somehow?
	// Start positions refer to a specific tile index in the map.
	start_x = 1;
	start_y = 1;
	
	if(val == 1)
	{
		start_x = 3;
		start_y = 14;
	}
	if(val == 2)
	{
		start_x = 4;
		start_y = 8;
	}
	
	return maps[val];
}

void MapHandler::generate_map()
{
	//TODO
}