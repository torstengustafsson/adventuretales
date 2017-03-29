#include "Door.h"

Door::Door( Texture* _tex, string _name, int _x_tile_index, int _y_tile_index, int _door_map, 
		int _door_x_tile, int _door_y_tile, SDL_Rect _clip )
	: Object(_tex, _name, _x_tile_index, _y_tile_index, 0, 0, 0, 0, _clip),
	  door_map{_door_map}, 
	  door_x_tile{_door_x_tile}, 
	  door_y_tile{_door_y_tile}
{}

const int Door::get_door_x_tile()
{
	return door_x_tile;
}

const int Door::get_door_y_tile()
{
	return door_y_tile;
}

const int Door::get_door_map()
{
	return door_map;
}