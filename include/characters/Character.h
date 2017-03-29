#pragma once

#include "../core/Globals.h"
#include "../core/RandomGenerator.h"
#include "../core/Resources.h"
#include "../textures/Texture.h"
#include "Traits.h"
#include "Inventory.h"

#include <vector>

class Character
{
public:
	Character() = delete; // we don't want to create non-specific characters
	virtual ~Character() = default;
	
	const unsigned int id;	// unique id for easy access
	
	void render(int x, int y, float size = 1.0);

	int get_attack();
	int get_defense();
	int get_vitality();
	int get_strength();
	int get_intelligence();
	int get_level();
	int get_experience();
	int get_exp_next_rel();
	int get_hit_points_current();
	int get_hit_points_max();
	string get_name();
	
	virtual string get_character_type() = 0;
	
	int get_trait_bonus_attack();
	int get_trait_bonus_defense();
	int get_trait_bonus_vitality();
	int get_trait_bonus_strength();
	int get_trait_bonus_intelligence();
	
	void set_attack(int val);
	void set_defense(int val);
	void set_vitality(int val);
	void set_strength(int val);
	void set_intelligence(int val);
	void set_hp(int val);
	void add_hp(int val);
	void add_experience(int val);
	void increase_level();
	void set_name(string _name);
	
	void add_trait(string name);
	vector<tuple<string,string,array<int,5>>> get_traits();
	
	void add_item(string name);
	void remove_item(string name);
	vector<tuple<Texture*, string, string, string, int>> get_inventory(int item_type = 0);
	
	//TODO: Fix with inventory instead of int when possible
	void equip_weapon(int weapon);
	
	void load_stats(int _att, int _def, int _vit, int _str, int _int, int _level, int _exp);
	
protected:
	Character(Resources* _res, string _sprite_path, unsigned int _id, int ag, int dg, int vg, int sg, int ig, int _level = 0, int _experience = 0);
	
	// Name needs to be initialized outside constructor
	string name = "???";
	
	int attack, att_gain;
	int defense, def_gain;
	int vitality, vit_gain;
	int strength, str_gain;
	int intelligence, int_gain;
	
	int hit_points_max = 10;
	int hit_points_current = 10;
	
	int level = 1;
	int experience = 0;
	int exp_next = 50;		//absolute number to reach next level
	int exp_next_rel = 50;	//relative number to reach next from current
	
	Resources* resources;
	Texture* character_portrait;
	
	Traits traits;
	Inventory inventory;
	
	RandomGenerator generateRand;
};