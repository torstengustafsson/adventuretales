#pragma once

#include "Object.h"

class MovingObject : public Object
{
public:
	MovingObject( Texture* _tex, string _name, int _x_tile_index, int _y_tile_index, int _x_pos = 0, 
		int _y_pos = 0, int _x_pos_camera = 0, int _y_pos_camera = 0, SDL_Rect _clip = { 0, 0, 0, 0 } );

	bool get_moving();
	int get_direction();
	bool get_want_to_move();
	void set_moving(bool val, int from_x, int from_y);
	
	// Called every frame to perfrom player animations. May be called from outside sources, for example 
	// during NPC interactions, to animate before game pause.
	void animate();
protected:
	enum animation_states
	{
		ANIM_IDLE,
		ANIM_WALK
	};
	
	unsigned int animation_state = ANIM_IDLE;
	const int ANIM_IDLE_FRAMES = 1;
	const int ANIM_WALK_FRAMES = 2;
	
	
	//Keeps track of where in the current animation cycle we are. Resets when cycle is complete.
	unsigned int animation_cycle;
	short int anim_timer = 0;
	
	//1 = left, 2 = right, 3 = down, 4 = up
	short int direction = 3;
	//when player begins a move from one tile to another, moving becomes true. Player
	//can not begin a new move until moving is false again.
	bool moving = false;
	//becomes true whenever a movement key is pressed
	bool want_to_move = false;
	//counter for the 8 frames player is moving from one tile to the next
	short int move_counter = 0;
	int move_from_x, move_from_y;
};