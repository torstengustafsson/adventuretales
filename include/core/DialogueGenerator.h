#include "Globals.h"
#include "RandomGenerator.h"
#include "../characters/Character.h"

#include <vector>
#include <array>

// The main purpose of this class is to generate NPC dialogues randomly.
class DialogueGenerator
{
public:
	DialogueGenerator();
	
	//Personality consists of: nice/mean, talkative/reserved, intelligent/dumb, knows player/don't.
	string generate_dialogue(string my_name, array<bool, 4> personality, float annoyed_level, Character* player);
private:
	RandomGenerator generateRand;

	enum personality_types { NICE, TALKATIVE, INTELLIGENT, KNOWSPLAYER };
	
	struct node;
	struct node_value
	{
		node_value(string v, node* n = nullptr, float p = 0.0)
			: value{v}, next{n}, probability{p} {}
		string value;
		node* next;
		float probability;
	};
	struct node
	{
		vector<node_value> values;
	};
	
	////Initialized in construction
	node greetings;
	node before_names;
	node random_trivia;
	node relevant_trivia;
	node questions;
	node colors;
	node exclamation_mark;
	node question_mark;
	node dot;	//ugly solution for now, fix so these can be added instead of just appended.
	node annoyed;	
	
	//gains values dynamically
	node name;
	
	float percent();
};