#pragma once

#include "Item.h"

class Armor : public Item
{
public:
	Armor(Texture* _icon, string _name, string _type, int _armor);
	
	string get_type() override;
	int get_value() override;
	
private:
	string type;
	
	int armor;
};