#pragma once

#include "MovingObject.h"

class Player : public MovingObject
{
public:
	Player(Texture* _tex, string _name, int _x_tile_index, int _y_tile_index, int _x_pos = 0, int _y_pos = 0, 
		int _x_pos_camera = 0, int _y_pos_camera = 0, SDL_Rect _clip = {0, 0, 0, 0}, bool game_loaded = false);
	
	void perform_actions(); // Called every frame to perfrom player animations
	void move(int val);	// Called whenever a movement key is pressed
	void set_direction(int val); // Used when player is attacked or interacted with
private:

};