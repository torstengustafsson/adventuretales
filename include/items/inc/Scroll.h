#pragma once
#include "Weapon.h"

class Scroll : public Weapon
{
public:
	Scroll(Texture* _icon, string _name, string _type);
	
	string get_type() override;
	int get_value() override;
	
private:
	string type;
};