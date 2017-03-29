#include "GameEngine.h"

GameEngine::GameEngine(Player* _player)
{
	player = _player;
}

void GameEngine::frame(const vector<Object*>& v)
{	
	for(auto& o : v)
	{
		if( MovingObject* mo = dynamic_cast<MovingObject*>(o) )
		{
			if(!mo->get_moving() && mo->get_want_to_move())
			{
				if( mo->get_direction() == 1 && !collision(mo->get_x_tile() - 1, mo->get_y_tile(), v, 
					dynamic_cast<NPC*>(o) ? false : true) )
				{
					mo->set_moving(true, mo->get_x_tile(), mo->get_y_tile());
					mo->set_x_tile( mo->get_x_tile() - 1 );
				}
					
				if( mo->get_direction() == 2 && !collision(mo->get_x_tile() + 1, mo->get_y_tile(), v, 
					dynamic_cast<NPC*>(o) ? false : true) )
				{
					mo->set_moving(true, mo->get_x_tile(), mo->get_y_tile());
					mo->set_x_tile( mo->get_x_tile() + 1 );
				}
					
				if( mo->get_direction() == 3 && !collision(mo->get_x_tile(), mo->get_y_tile() + 1, v, 
					dynamic_cast<NPC*>(o) ? false : true) )
				{
					mo->set_moving(true, mo->get_x_tile(), mo->get_y_tile());
					mo->set_y_tile( mo->get_y_tile() + 1 );
				}
					
				if( mo->get_direction() == 4 && !collision(mo->get_x_tile(), mo->get_y_tile() - 1, v,
					dynamic_cast<NPC*>(o) ? false : true) )
				{
					mo->set_moving(true, mo->get_x_tile(), mo->get_y_tile());
					mo->set_y_tile( mo->get_y_tile() - 1 );
				}
			}
		}
	}
}

//Checks if there is a collider object in tile (x_tile, y_tile)
bool GameEngine::collision(int x_tile, int y_tile, const vector<Object*>& v, bool enter_doors)
{
	//if position is outside of local bounds (no object loaded at position) it counts as a collision
	int limits = true;
	for(auto& o : v)
	{
		//As long as there is a tile at collision-position we may return no collision (false)
		if(o->get_x_tile() == x_tile && o->get_y_tile() == y_tile)
				limits = false;
		
		if(o->get_name() == "background" || o->get_name() == "foreground" || (enter_doors && o->get_name() == "door"))
			continue;
		
		if(o->get_x_tile() == x_tile && o->get_y_tile() == y_tile)
			return true;
	}
	
	return limits;
}