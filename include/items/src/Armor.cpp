#include "items/inc/Armor.h"

Armor::Armor(Texture* _icon, string _name, string _type, int _armor)
	: Item(_icon, _name)
{
	type = _type;
	armor = _armor;
}

string Armor::get_type()
{
	return type;
}

int Armor::get_value()
{
	return armor;
}