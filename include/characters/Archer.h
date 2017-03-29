#pragma once

#include "Character.h"

class Archer : public Character
{
public:
	Archer() = delete;
	Archer(Resources* _res, int _id);
	
	string get_character_type() override;
private:

};