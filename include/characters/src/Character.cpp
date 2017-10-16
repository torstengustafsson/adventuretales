#include "characters/inc/Character.h"

// Initialize EVERYTHING!
Character::Character(Resources* _res, string sprite_path, unsigned int _id, int ag, int dg, int vg, int sg, int ig, int _level, int _experience)
	: id{_id}, att_gain{ag}, def_gain{dg}, vit_gain{vg}, str_gain{sg}, int_gain{ig}, inventory(_res)
{
	// gain = 1: 4-5. gain = 2: 5-7. gain = 3: 6-7
	set_attack( 3 + ag + generateRand() % (2 + (ag == 2 ? 1 : 0)) );
	set_defense( 3 + dg + generateRand() % (2 + (dg == 2 ? 1 : 0)) );
	set_vitality( 3 + vg + generateRand() % (2 + (vg == 2 ? 1 : 0)) );
	set_strength( 3 + sg + generateRand() % (2 + (sg == 2 ? 1 : 0)) );
	set_intelligence( 3 + ig + generateRand() % (2 + (ig == 2 ? 1 : 0)) );
	resources = _res;
	character_portrait = resources->get_texture(sprite_path);
}

void Character::render(int x, int y, float size)
{
	character_portrait->render(x, y, size);
}

int Character::get_attack()
{
	return attack;
}
int Character::get_defense()
{
	return defense;
}
int Character::get_vitality()
{
	return vitality;
}
int Character::get_strength()
{
	return strength;
}
int Character::get_intelligence()
{
	return intelligence;
}

int Character::get_level()
{
	return level;
}

int Character::get_experience()
{
	return experience;
}

int Character::get_exp_next_rel()
{
	return exp_next_rel;
}

string Character::get_name()
{
	return name;
}

int Character::get_trait_bonus_attack()
{
	return traits.get_bonus_attack();
}

int Character::get_trait_bonus_defense()
{
	return traits.get_bonus_defense();
}

int Character::get_trait_bonus_vitality()
{
	return traits.get_bonus_vitality();
}

int Character::get_trait_bonus_strength()
{
	return traits.get_bonus_strength();
}

int Character::get_trait_bonus_intelligence()
{
	return traits.get_bonus_intelligence();
}

int Character::get_hit_points_current()
{
	return hit_points_current;
}

int Character::get_hit_points_max()
{
	return hit_points_max;
}

void Character::set_attack(int val)
{
	attack = val;
}

void Character::set_defense(int val)
{
	defense = val;
}

void Character::set_vitality(int val)
{
	vitality = val;
	
	//Recalculate hit points
	hit_points_max = 10;
	for(int i = 1; i < vitality; i++)
		hit_points_max += i;
	hit_points_current = hit_points_max;
}

void Character::set_strength(int val)
{
	strength = val;
}

void Character::set_intelligence(int val)
{
	intelligence = val;
}

void Character::set_hp(int val)
{
	hit_points_current = max(min(val, hit_points_max), 0);
}

void Character::add_hp(int val)
{
	hit_points_current = max(min(hit_points_current + val, hit_points_max), 0);
}

void Character::add_experience(int val)
{
	experience += val;
	while(experience >= exp_next)
	{
		int diff = experience - exp_next;
		increase_level();
		experience += diff;
	}
	exp_next_rel = exp_next - experience;
}

void Character::increase_level()
{
	level++;
	
	//Set experience to its right value to prevent mistakes
	experience = 0;
	for(int i = 1; i < level; i++)
		experience += 30 + 20 * i;
	exp_next_rel = 30 + 20 * level;
	exp_next = exp_next + exp_next_rel;
	
	// gain = 1: +1-2. gain = 2: +2-3. gain = 3: +2-4
	set_attack(attack + (att_gain < 2 ? 1 : 2) + generateRand() % (2 + (att_gain == 3 ? 1 : 0)));
	set_defense(defense + (def_gain < 2 ? 1 : 2) + generateRand() % (2 + (def_gain == 3 ? 1 : 0)));
	set_vitality(vitality + (vit_gain < 2 ? 1 : 2) + generateRand() % (2 + (vit_gain == 3 ? 1 : 0)));
	set_strength(strength + (str_gain < 2 ? 1 : 2) + generateRand() % (2 + (str_gain == 3 ? 1 : 0)));
	set_intelligence(intelligence + (int_gain < 2 ? 1 : 2) + generateRand() % (2 + (int_gain == 3 ? 1 : 0)));
}

void Character::set_name(string _name)
{
	name = _name;
}

void Character::add_trait(string name)
{
	traits.add_trait(name);
}

void Character::add_item(string name)
{
	inventory.add_item(name);
}

void Character::remove_item(string name)
{
	inventory.remove_item(name);
}

vector<tuple<string,string,array<int,5>>> Character::get_traits()
{
	return traits.get_traits();
}

vector<tuple<Texture*, string, string, string, int>> Character::get_inventory(int item_type)
{
	return inventory.get_items(item_type);
}

void Character::equip_weapon(int weapon)
{
	traits.set_equipped_weapon(weapon);
}

// Loads a previously saved character instead of using the newly generated values
//TODO: add traits and inventory
void Character::load_stats(int _att, int _def, int _vit, int _str, int _int, int _level, int _exp)
{
	attack = _att;
	defense = _def;
	vitality = _vit;
	strength = _str;
	intelligence = _int;
	level = _level;
	experience = _exp;
}