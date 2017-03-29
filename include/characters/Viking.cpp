#include "Viking.h"

// Gain values: 1 = low. 2 = medium. 3 = high.
Viking::Viking(Resources* _res, int _id)
	: Character(_res, "./data/sprites/battle/characters/viking.png", _id, 3, 1, 2, 3, 1)
{
	array<string, 10> viking_names = {"Harald", "Tor", "Ragnar", "Arvid", "Orm", "Bard", "Halvar", "Leif", "Olaf", "Sigurd"};
	set_name(viking_names[generateRand() % 10]);
}

string Viking::get_character_type()
{
	return "Viking";
}