#pragma once

#include "core/inc/Globals.h"

#include <vector>
#include <array>
#include <regex>

/*
	Accepted Traits:
	 * "Likes Swords" 	- +10% attack when using sword
	 * "Likes Axes" 	- +10% attack when using axe
	 * "Likes Maces" 	- +10% attack when using mace
	 * "Likes Bows" 	- +10% attack when using bow
	 * "Likes Scrolls" 	- +10% attack when using scrolls
	 * "Brute" 			- +1 strength, -1 intelligence
	 * "Scholar" 		- -1 strength, +1 intelligence
	 * "Reckless" 		- +1 attack, -1 defense
	 * "Cautious" 		- -1 attack, +1 defense
*/

class Traits
{
public:
	Traits() = default;
	
	void add_trait(string name);
	
	int get_bonus_attack();
	int get_bonus_defense();
	int get_bonus_vitality();
	int get_bonus_strength();
	int get_bonus_intelligence();
	
	void set_equipped_weapon(int val);
	
	vector<tuple<string,string,array<int,5>>> get_traits();
	
private:

	enum stat_types { ATT, DEF, VIT, STR, INT };

	struct Trait 
	{
		string name;
		string description;
		array<int, 5> bonuses{ { 0, 0, 0, 0, 0 } };
	};
	
	vector<Trait> traits;
	
	int get_bonus(int type);
	
	enum weapon_types { NO_WEAPON, SWORD, AXE, MACE, BOW, SCROLL };
	int equipped_weapon = NO_WEAPON;
};