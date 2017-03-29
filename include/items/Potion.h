#pragma once
#include "Item.h"

class Potion : public Item
{
public:
	Potion(Texture* _icon, string _name, string _type, int _power);
	
	string get_type() override;
	int get_value() override;
	
private:
	string type;
	
	//power represents the potions potency. A healing potion with power 5 heals 5 hp, an 
	//intelligence potion with power 2 increases intelligence by 2, etc.
	int power;
};