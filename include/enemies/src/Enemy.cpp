#include "enemies/inc/Enemy.h"

Enemy::Enemy(Texture* _tex, string _name, int _x_tile_index, int _y_tile_index, int _behaviour,
	function<vector<Object*>()> _get_objects)
	: MovingObject(_tex, _name, _x_tile_index, _y_tile_index, 0, 0, 0, 0, SDL_Rect{0,0,32,32}),
	  behaviour{_behaviour}
{
	get_objects = _get_objects;
}

void Enemy::frame(int player_x, int player_y)
{
	want_to_move = false;
	animation_state = moving ? ANIM_WALK : ANIM_IDLE;
	
	//Perform NPC motion between tiles
	if(moving)
	{
		if(move_counter++ < 8)
		{
			if(direction == 1) set_x(move_from_x - 4 * move_counter);
			if(direction == 2) set_x(move_from_x + 4 * move_counter);
			if(direction == 3) set_y(move_from_y + 4 * move_counter);
			if(direction == 4) set_y(move_from_y - 4 * move_counter);
		}
		else
		{
			move_counter = 0;
			set_x(get_x_tile() * 32);
			set_y(get_y_tile() * 32);
			moving = false;
		}
	}
	
	animate();
	
	action_timer += curr_dt;
	
	int player_distance = dist(node(player_x, player_y), node(get_x_tile(), get_y_tile()));
	hunting_player = player_distance < 8 && player_distance != 1 ? true : false;
	
	if(!hunting_player)
	{
		if(behaviour == LOOKER && action_timer > 3.0 && !moving && generateRand() % 100 < 1)
		{
			direction = generateRand() % 4 + 1;
			action_timer = 0.0;
		}
		
		if(behaviour == MOVER && action_timer > 3.0 && !moving && generateRand() % 100 < 1)
		{
			direction = generateRand() % 4 + 1;
			want_to_move = true;
			animation_state = ANIM_WALK;
			action_timer = 0.0;
		}
	}
	else if(!moving)
	{
		//A* search
		direction = find_path(player_x, player_y);
		want_to_move = true;
	}
}

string Enemy::interact(int dir)
{
	if(!moving)
		direction = dir;
	return generateRand() % 2 == 0  ? "BATTLE ME!" : "FIGHT ME!";
}

//Returns true if node collides with o, and o is not a collider object (enemy may walk through it)
bool Enemy::collision(node n, vector<Object*> v)
{
	bool collision = false;
	bool collider = false;
	for(auto& o : v)
	{
		if( n.x == o->get_x_tile() && n.y == o->get_y_tile())
		{
			collision = true;
			if(o->get_name() != "background" && o->get_name() != "foreground" && o->get_name() != "player" )
				collider = true;
		}
	}
	
	return ( collision && !collider );
}

//needs to be declared global in this context to be used by h_fun
Enemy::node player_pos(0, 0);

bool Enemy::h_fun::operator()(const node* h1, const node* h2) const
{ 
	return dist(*h1, player_pos) + h1->dist > dist(*h2, player_pos) + h2->dist;
}

//A* Algorithm. Searches for shortest path from enemy position to player position.
int Enemy::find_path(int x, int y)
{
	//maps x coordinate as x*10000. So if y > 10000 duplicates will be found and pathfinding will break.
	//nodes map is required because otherwise standard containers will remove actual elements on pop(), 
	//breaking path.
	map<int, unique_ptr<node>> nodes;
	
	player_pos = node(x, y);
	priority_queue<node*, vector<node*>, h_fun> sorted_nodes;
	set<node*> visited_nodes;
	
	nodes[get_x_tile()*10000 + get_y_tile()] = unique_ptr<node>(new node(get_x_tile(), get_y_tile()));
	sorted_nodes.push( nodes[get_x_tile()*10000 + get_y_tile()].get() );

	int C = 0;
	while(!sorted_nodes.empty())
	{
		if( C++ > 17 ) return 0; //'endless loop' breaker
		node* current = sorted_nodes.top();
		visited_nodes.emplace(current);
		
		
		sorted_nodes.pop();
		
		if(*current == player_pos)
		{
			//Found! Remove path elements until we only have first step left
			node* path = current;
			while( path->prev && *(path->prev) != node(get_x_tile(), get_y_tile()))
			{
				path = path->prev;
			}
			
			if(path->x == get_x_tile()-1 && path->y == get_y_tile())
				return 1;	//left
			else if(path->x == get_x_tile()+1 && path->y == get_y_tile())
				return 2;	//right
			else if(path->x == get_x_tile() && path->y == get_y_tile()+1)
				return 3;	//down
			else
				return 4;	//up
		}
		else //not found. Keep searching
		{
			vector<node> new_nodes = {
				node(current->x+1, current->y, nodes[current->x*10000 + current->y].get()),
				node(current->x-1, current->y, nodes[current->x*10000 + current->y].get()),
				node(current->x, current->y+1, nodes[current->x*10000 + current->y].get()),
				node(current->x, current->y-1, nodes[current->x*10000 + current->y].get())
			};
			
			//check which new nodes we can add (we don't want to re-add nodes, and no colliders)
			for(auto n : new_nodes)
			{
				if(collision(n, get_objects()) && nodes.find(n.x*10000 + n.y) == nodes.end() )
				{
					n.dist = current->dist + dist(n, player_pos);
					nodes[n.x*10000 + n.y] = unique_ptr<node>(new node(n));
					node* temp = nodes[n.x*10000 + n.y].get();
					sorted_nodes.push(temp);
				}
			}
		}
		
	}
	
	return 0;
}