#include "world/inc/MovingObject.h"

MovingObject::MovingObject(Texture* _tex, string _name, int _x_tile_index, int _y_tile_index, int _x_pos,
	int _y_pos, int _x_pos_camera, int _y_pos_camera, SDL_Rect _clip, float* curr_dt) :
		Object(_tex, _name, _x_tile_index, _y_tile_index, _x_pos, _y_pos, _x_pos_camera, _y_pos_camera, _clip),
		curr_dt(curr_dt)
{}

int MovingObject::get_direction()
{
	return direction;
}

bool MovingObject::get_moving()
{
	return moving;
}

bool MovingObject::get_want_to_move()
{
	return want_to_move;
}

void MovingObject::set_moving(bool val, int from_x, int from_y)
{
	moving = val;
	move_from_x = 32 * from_x;
	move_from_y = 32 * from_y;
}



void MovingObject::animate()
{
	if( ++anim_timer >= 6 )	//animate every sixth frame
	{
		animation_cycle++;
		anim_timer = 0;
	}

	// TODO: animation counts are currently hardcoded to 1 sprite for idle and 2 sprites for walking.
	// Fix by looping animation_cycle using ANIM_XXXX_FRAMES. Sprite sheet coordinates need to match though.
	switch( animation_state )
	{
		case ANIM_IDLE:
			animation_cycle = animation_cycle % ANIM_IDLE_FRAMES;
			if( direction == 1 )	// Left
			{
				if(animation_cycle == 0)
					change_clip(SDL_Rect{32,0,32,32});
			}
			if( direction == 2 )	// Right
			{
				if(animation_cycle == 0)
					change_clip(SDL_Rect{64,0,32,32});
			}
			if( direction == 3 )	// Down
			{
				if(animation_cycle == 0)
					change_clip(SDL_Rect{0,0,32,32});

			}
			if( direction == 4 )	// Up
			{
				if(animation_cycle == 0)
					change_clip(SDL_Rect{96,0,32,32});
			}

			break;
		case ANIM_WALK:
			animation_cycle = animation_cycle % ANIM_WALK_FRAMES;
			if( direction == 1 )	// Left
			{
				if(animation_cycle == 0)
					change_clip(SDL_Rect{32,32,32,32});
				if(animation_cycle == 1)
					change_clip(SDL_Rect{32,64,32,32});
			}
			if( direction == 2 )	// Right
			{
				if(animation_cycle == 0)
					change_clip(SDL_Rect{64,32,32,32});
				if(animation_cycle == 1)
					change_clip(SDL_Rect{64,64,32,32});
			}
			if( direction == 3 )	// Down
			{
				if(animation_cycle == 0)
					change_clip(SDL_Rect{0,32,32,32});
				if(animation_cycle == 1)
					change_clip(SDL_Rect{0,64,32,32});
			}
			if( direction == 4 )	// Up
			{
				if(animation_cycle == 0)
					change_clip(SDL_Rect{96,32,32,32});
				if(animation_cycle == 1)
					change_clip(SDL_Rect{96,64,32,32});
			}

			break;
		default:
			cout << "Error: Bad object animation state!\n";
	}
}