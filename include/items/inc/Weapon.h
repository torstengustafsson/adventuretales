#pragma once

#include "Item.h"

class Weapon : public Item
{
public:
	Weapon(Texture* _icon, string _name, string _type, int _damage);
	
	string get_type() override;
	int get_value() override;
	
private:
	string type;
	int damage;
};