#pragma once

#include "MovingObject.h"
#include "core/inc/RandomGenerator.h"
#include <array>

class NPC : public MovingObject
{
public:
	NPC( Texture* _tex, string _name, int _x_tile_index, int _y_tile_index, float* curr_dt, int _behaviour = 0, string _dialogue = "" );

	void set_behaviour(int val);
	void set_dialogue(string text);
	bool generates_dialogues();
	string get_name();
	array<bool, 4> get_personality();
	float get_annoyed_level();

	string interact(int dir) override;

	void frame();
private:
	RandomGenerator generateRand;

	enum behaviours
	{
		PASSIVE,
		LOOKER,
		MOVER
	};

	int behaviour = PASSIVE;

	//Increases by one for every interaction. Dissipates with time
	float annoyed_level = 0;

	//Personality consists of: nice/mean, talkative/reserved, intelligent/dumb, knows player/don't.
	array<bool, 4> personality;

	//The text that player will se when interacting with this particular NPC
	string dialogue;
	bool should_generate_dialogues = false;

	//timer to limit NPC actions
	float action_timer = 0;
};