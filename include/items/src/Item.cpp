#include "items/inc/Item.h"

Item::Item(Texture* _icon, string _name)
{
	icon = _icon;
	name = _name;
}

Texture* Item::get_icon()
{
	return icon;
}

string Item::get_name()
{
	return name;
}