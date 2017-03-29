#pragma once

#include "Globals.h"
#include "../world/Object.h"
#include "../world/NPC.h"
#include "../world/Player.h"

#include <vector>
#include <cmath>

class GameEngine
{
public:
	GameEngine(Player* _player);
	
	void frame(const vector<Object*>& v);
	
private:
	Player* player;
	bool collision(int x_tile, int y_tile, const vector<Object*>& v, bool enter_doors = true);
};