#include "world/inc/NPC.h"

NPC::NPC(Texture* _tex, string _name, int _x_tile_index, int _y_tile_index, float* curr_dt, int _behaviour, string _dialogue)
	: MovingObject(_tex, _name, _x_tile_index, _y_tile_index, 0, 0, 0, 0, SDL_Rect{0,0,32,32}, curr_dt),
	  behaviour{_behaviour}
{
	if(_dialogue == "")
	{
		set_name(generateRand.name());
		should_generate_dialogues = true;
	}
	dialogue = _dialogue;

	//initialize random personality
	personality = { (bool)(generateRand() % 2), (bool)(generateRand() % 2), (bool)(generateRand() % 2) };
}

void NPC::frame()
{
	want_to_move = false;
	animation_state = moving ? ANIM_WALK : ANIM_IDLE;

	//Perform NPC motion between tiles
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

	action_timer += *curr_dt;

	if(behaviour == LOOKER && action_timer > 3.0 && !moving && generateRand() % 100 < 1)
	{
		direction = generateRand() % 4 + 1;
		action_timer = 0.0;
	}

	if(behaviour == MOVER && action_timer > 3.0 && !moving && generateRand() % 100 < 1)
	{
		direction = generateRand() % 4 + 1;
		want_to_move = true;
		animation_state = ANIM_WALK;
		action_timer = 0.0;
	}

	if(annoyed_level > 0)
		annoyed_level = max(annoyed_level - *curr_dt / 2, 0.0f);
}

bool NPC::generates_dialogues()
{
	return should_generate_dialogues;
}

array<bool, 4> NPC::get_personality()
{
	return personality;
}

void NPC::set_behaviour(int val)
{
	behaviour = val;
}

void NPC::set_dialogue(string text)
{
	dialogue = text;
}

float NPC::get_annoyed_level()
{
	return annoyed_level;
}

string NPC::interact(int dir)
{
	annoyed_level += 1.0;
	if(!moving)
		direction = dir;

	return dialogue;
}