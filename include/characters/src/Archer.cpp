#include "characters/inc/Archer.h"

// Gain values: 1 = low. 2 = medium. 3 = high.
Archer::Archer(Resources* _res, int _id) 
	: Character(_res, data_path + "/sprites/battle/characters/archer.png", _id, 3, 1, 2, 3, 1)
{
	array<string, 10> archer_names = {"Brian", "Glen", "Arthur", "Kendall", "Tristan", "Marvin", "Nelson", "Oscar", "Alan", "Aodhan"};
	set_name(archer_names[generateRand() % 10]);
}

string Archer::get_character_type()
{
	return "Archer";
}