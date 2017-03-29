#pragma once

#include "../core/Globals.h"
#include "../textures/Texture.h"

enum weapon_types { SWORD, AXE, MACE, BOW, SCROLL_WEAPON };
enum armor_types { CHEST, HELMET, SHIELD };
enum scroll_types { EMPTY_SCROLL, FIREBALL_SCROLL, ARMOR_SCROLL };
enum potion_types { HP_RESTORE, STRENGTH_INCREASE, INTELLIGENCE_INCREASE };

class Item
{
public:
	Texture* get_icon();
	string get_name();
	
	virtual string get_type() = 0;
	virtual int get_value() = 0;

protected:
	Item(Texture* _icon, string _name);
	
	Texture* icon;
	string name;
};