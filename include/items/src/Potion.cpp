#include "items/inc/Potion.h"

Potion::Potion(Texture* _icon, string _name, string _type, int _power)
	: Item(_icon, _name)
{
	type = _type;
	power = _power;
}

string Potion::get_type()
{
	return type;
}

int Potion::get_value()
{
	return power;
}