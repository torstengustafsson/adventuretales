#pragma once

#include "Character.h"

class Viking : public Character
{
public:
	Viking() = delete;
	
	Viking(Resources* _res, int _id);
	
	string get_character_type() override;
private:

};