#pragma once

#include "world/inc/MovingObject.h"
#include "core/inc/RandomGenerator.h"

#include <functional>
#include <set>
#include <map>
#include <stack>
#include <queue>

class Enemy : public MovingObject
{
public:
	Enemy( Texture* _tex, string _name, int _x_tile_index, int _y_tile_index, float* curr_dt, int _behaviour,
		function<vector<Object*>()> _get_objects);


	string interact(int dir) override;

	void frame(int player_x, int player_y);

	//Used by pathfinding algorithm to store positions
	struct node
	{
		node(int _x, int _y, node* _p = nullptr) : x{_x}, y{_y}, dist{0}, prev{_p} {}
		node(const node & n) : x{n.x}, y{n.y}, dist{n.dist} { prev = &(*(n.prev)); }
		bool operator==(const node& n) const { return x == n.x && y == n.y; }
		bool operator!=(const node& n) const { return x != n.x || y != n.y; }
		bool operator<(const node& n) const { return y < n.y || (y == n.y && x < n.x); }
		int x;
		int y;
		int dist; //used by heuristic function
		node* prev; //used to find path
	};

private:
	RandomGenerator generateRand;

	enum behaviours
	{
		PASSIVE,
		LOOKER,
		MOVER
	};

	int behaviour = PASSIVE;

	bool hunting_player = false; //enemy start moving towards player, when close enough

	//timer to limit NPC actions
	float action_timer = 0;


// **********************
// PATHFINDING STUFF ****
// **********************

	function<vector<Object*>()> get_objects;

	//utility functions
	bool collision(node n, vector<Object*> v);
	static const int dist(const node& n1, const node& n2)
		{ return abs(n1.x - n2.x) + abs(n1.y - n2.y); }

	//Heuristic function used by the A* algorithm (based on Manhattan distance)
	struct h_fun
	{
		bool operator()(const node* h1, const node* h2) const;
	};

	//Uses the A* algorithm to find the shortest path from its current position to goal position (x,y).
	//Returns direction to move first step. Because player may move each frame, a new path is
	//recalculated each frame.
	int find_path(int x, int y);
};