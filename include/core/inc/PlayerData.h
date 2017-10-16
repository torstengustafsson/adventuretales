#pragma once

#include "Globals.h"
#include "Resources.h"
#include "characters/inc/Viking.h"
#include "characters/inc/Archer.h"

#include <vector>

class PlayerData
{
public:
	PlayerData(Resources* _res);
	
	Character* get_main_character();
	unique_ptr<Character> const& get_character(unsigned int _id);
	vector<unique_ptr<Character>> const& get_characters();
	
	// Returns the id of the newly created character
	int add_character(string type);
	
	void remove_character(Character* _c);
	void remove_character(unsigned int _id);
	
	void add_gold(int val);
	bool remove_gold(int val);	// if gold < val no gold is removed and function returns false.
	
	// saves/loads a game to/from the file accessed by the path argument
	void save_game(string path);
	void load_game(string path);
	
private:
	vector<unique_ptr<Character>> characters;
	int gold;
	
	Resources* resources;
	
	// char_id should always be a new unique value each time it is used. Maybe create data structure
	// to handle this? int for now though.
	unsigned int char_id = 0;
	
	void sort_chars();
};