#pragma once

#include "Object.h"

class Door : public Object
{
public:
	Door( Texture* _tex, string _name, int _x_tile_index, int _y_tile_index, int _door_map, 
		int _door_x_tile, int _door_y_tile, SDL_Rect _clip = { 0, 0, 0, 0 } );
	
	const int get_door_map();
	const int get_door_x_tile();
	const int get_door_y_tile();
	
private:

	//the map the door leads to
	const int door_map;
	
	//the position the door leads to
	const int door_x_tile, door_y_tile;
};