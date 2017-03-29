#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

//The types of items available in the game
enum item_types { GENERAL_ITEM, WEAPON, ARMOR, SCROLL, POTION };

//Exit game when quit is true
extern bool quit;

//Stores the current runtime, as well as delta time between each frame in seconds.
//Initialized by main and then handled by GameController class.
extern float curr_time;
extern float curr_dt;