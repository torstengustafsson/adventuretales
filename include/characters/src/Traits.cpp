#include "characters/inc/Traits.h"
#include <tuple>

void Traits::add_trait(string name)
{
	regex likes("(Likes )(Swords|Axes|Maces|Bows|Scrolls)");
	int like_counter = 0;
	for(auto& t : traits)
	{
		like_counter += regex_match(t.name, likes) ? 1 : 0;
		if( (name == "Brute" && t.name == "Scholar") ||
			(name == "Scholar" && t.name == "Brute") || 
			(name == "Reckless" && t.name == "Cautious") ||
			(name == "Cautious" && t.name == "Reckless") )
		{
			cout << "Error. Can't be both " << name << " and " << t.name << "!\n";
			return;
		}		
	}
	
	Trait trait;
	trait.name = name;
	
	if( regex_match(name, likes) && like_counter < 3 )
	{
		trait.description = "This character likes to use " + name.substr(6) + " in battle.";
		trait.bonuses[ATT] = 1;
		traits.push_back(trait);
	}
	else if( name == "Brute" )
	{
		trait.description = "A brutish character is generally stronger than others, but may lack in intelligence.";
		trait.bonuses[STR] = 1;
		trait.bonuses[INT] = -1;
		traits.push_back(trait);
	}
	else if( name == "Scholar" )
	{
		trait.description = "A scholar seeks knowledge, and thus have a higher intelligence than most, but is often weak when it comes to feats of strength.";
		trait.bonuses[INT] = 1;
		trait.bonuses[STR] = -1;
		traits.push_back(trait);
	}
	else if( name == "Reckless" )
	{
		trait.description = "A reckless character sacrifices defense for attack.";
		trait.bonuses[ATT] = 1;
		trait.bonuses[DEF] = -1;
		traits.push_back(trait);
	}
	else if( name == "Cautious" )
	{
		trait.description = "A cautious character sacrifices attack for defense.";
		trait.bonuses[DEF] = 1;
		trait.bonuses[ATT] = -1;
		traits.push_back(trait);
	}
	else
		cout << "Error. Bad trait '" << name << "'!\n";
		
}

void Traits::set_equipped_weapon(int val)
{
	equipped_weapon = val;
}

int Traits::get_bonus(int type)
{
	int res = 0;
	for ( auto& t : traits )
	{
		if( (t.name == "Likes Swords" && equipped_weapon != SWORD) ||
			(t.name == "Likes Axes" && equipped_weapon != AXE) ||
			(t.name == "Likes Maces" && equipped_weapon != MACE) ||
			(t.name == "Likes Bows" && equipped_weapon != BOW) ||
			(t.name == "Likes Scrolls" && equipped_weapon != SCROLL) )
				continue;
				
		res += t.bonuses[type];
	}
	return res;
}

int Traits::get_bonus_attack()
{
	return get_bonus(ATT);
}

int Traits::get_bonus_defense()
{
	return get_bonus(DEF);
}

int Traits::get_bonus_vitality()
{
	return get_bonus(VIT);
}

int Traits::get_bonus_strength()
{
	return get_bonus(STR);
}

int Traits::get_bonus_intelligence()
{
	return get_bonus(INT);
}

vector<tuple<string,string,array<int,5>>> Traits::get_traits()
{
	vector<tuple<string,string,array<int,5>>> v;
	
	for(auto& t : traits)
		v.push_back(std::make_tuple(t.name, t.description, t.bonuses));
	
	return v;
}