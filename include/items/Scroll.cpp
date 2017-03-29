#include "Scroll.h"

Scroll::Scroll(Texture* _icon, string _name, string _type)
	: Weapon(_icon, _name, "Scroll", 0)
{
	type = _type;
}

string Scroll::get_type()
{
	return type;
}

int Scroll::get_value()
{
	return 0;
}