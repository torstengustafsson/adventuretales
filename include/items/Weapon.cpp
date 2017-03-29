#include "Weapon.h"

Weapon::Weapon(Texture* _icon, string _name, string _type, int _damage)
	: Item(_icon, _name)
{
	type = _type;
	damage = _damage;
}

string Weapon::get_type()
{
	return type;
}

int Weapon::get_value()
{
	return damage;
}