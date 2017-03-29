#pragma once

#include "Globals.h"
#include "Resources.h"
#include "RandomGenerator.h"
#include "../world/Object.h"
#include "../world/NPC.h"
#include "../world/Enemy.h"
#include "../world/Door.h"

#include <map>
#include <vector>
#include <array>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

//During development, Tiled Map Editor (http://www.mapeditor.org/) was used to generate the .csv files.
//As long as the tile mapping is correct, any map generation method is usable though. Tileset file can 
//be found in ./data/spites/AdventureTales_tileset.tsx (file paths may need to be adjusted).
class MapHandler
{
public:
	MapHandler(Resources* _res, function<vector<Object*>()> _get_objects);
	~MapHandler();
	
	vector<Object*> get_map(int val, int& start_x, int& start_y);
	
	void generate_map();
	
private:
	//Contains all maps in the game. Every map contains its own set of objects.
	map<int ,vector<Object*>> maps;
	Resources* resources;
	
	//Required to be passed to some more advanced pathfinding objects
	function<vector<Object*>()> get_objects;
	
	//Array of tile indexes:
	//0-99 = background
	//100-199 = colliders
	//200-299 = foreground
	//300-309 = doors
	array<string, 310> tiles;
	
	RandomGenerator generateRand;
	
	void add_tile(int val, string path, int x, int y, string name = "tile_collider");
	void add_door_tile(int val, int door_index, string path, int x_tile, int y_tile, string name);
	void load_tiles(int val, string suffix);
};