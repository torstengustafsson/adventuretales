#include "Player.h"

Player::Player(Texture* _tex, string _name, int _x_tile_index, int _y_tile_index, int _x_pos, int _y_pos, 
		int _x_pos_camera, int _y_pos_camera, SDL_Rect _clip, bool game_loaded)
	: MovingObject(_tex, _name, _x_tile_index, _y_tile_index, _x_pos, _y_pos, _x_pos_camera, _y_pos_camera, _clip)
{}

void Player::move(int val)
{
	if(!moving)
	{
		if(val >= 1 && val <= 4)
		{
			if(!moving)
			{
				direction = val;
				animation_state = ANIM_WALK;
			}
			want_to_move = true;
		}
		else // usually 0
		{
			animation_state = ANIM_IDLE;
			set_x(get_x_tile() * 32);
			set_y(get_y_tile() * 32);
			want_to_move = false;
		}
	}
}

void Player::set_direction(int val)
{
	direction = val;
}

void Player::perform_actions()
{	
	//Perform player motion between tiles
	if(moving)
	{
		if(move_counter++ < 8)
		{
			if(direction == 1) set_x(move_from_x - 4 * move_counter);
			if(direction == 2) set_x(move_from_x + 4 * move_counter);
			if(direction == 3) set_y(move_from_y + 4 * move_counter);
			if(direction == 4) set_y(move_from_y - 4 * move_counter);
		}
		else
		{
			move_counter = 0;
			set_x(get_x_tile() * 32);
			set_y(get_y_tile() * 32);
			moving = false;
		}
	}
	
	animate();
}