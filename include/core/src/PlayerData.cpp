#include "core/inc/PlayerData.h"

PlayerData::PlayerData(Resources* _res) : gold{0}, resources{_res}
	{}

Character* PlayerData::get_main_character()
{
	return characters.at(0).get();
}

unique_ptr<Character> const& PlayerData::get_character(unsigned int _id)
{
	static unique_ptr<Character> not_found;
	for( auto& c : characters )
	{
		if( c->id == _id )
			return c;
	}
	cout << "Error: character with id '" << _id << "' does not exist!\n";
	return not_found;
}

vector<unique_ptr<Character>> const& PlayerData::get_characters()
{
	sort_chars();
	return characters;
}

//Make sure that the highest level character is first.
void PlayerData::sort_chars()
{
	sort(begin(characters), end(characters), [](unique_ptr<Character>& lhs, unique_ptr<Character>& rhs)
	{ 
		return lhs->get_level() > rhs->get_level(); 
	});
}

//If no more characters can be created, id to the last created character will be returned.
int PlayerData::add_character(string type)
{
	if(characters.size() >= 3)
		cout << "Error: Can't have more than 3 characters!\n";
	else
	{
		if(type == "Viking")
		{
			characters.push_back(unique_ptr<Character>(new Viking(resources, char_id++)));
			sort_chars();
			return char_id - 1;
		}
		else if(type == "Archer")
		{
			characters.push_back(unique_ptr<Character>(new Archer(resources, char_id++)));
			sort_chars();
			return char_id - 1;
		}
		else
			cout << "Error. Character type '" << type << "' does not exist!\n";
	}
	
	if(characters.size() > 0)
		return characters.back()->id;
	return -1;
}

void PlayerData::remove_character(Character* _c)
{
	remove_character(_c->id);
}

void PlayerData::remove_character(unsigned int _id)
{
	for( auto it = characters.begin(); it != characters.end(); ++it )
	{
		if( _id == it->get()->id )
		{
			//cout << "removing character " << it->get()->get_name() << "\n";
			cout << characters.size() << "\n";
			characters.erase(it);
			cout << characters.size() << "\n";
			return;
		}
	}
}

void PlayerData::save_game(string path)
{
	
}

void PlayerData::load_game(string path)
{
	
}