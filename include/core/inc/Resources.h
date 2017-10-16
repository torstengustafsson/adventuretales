#pragma once

#include "Globals.h"
#include "textures/inc/Texture.h"
#include "textures/inc/Text.h"
#include "items/inc/Weapon.h"
#include "items/inc/Armor.h"
#include "items/inc/Potion.h"
#include "items/inc/Scroll.h"

#include <map>
#include <memory>

class Resources
{
public:
	Resources(SDL_Renderer* _game_renderer);
	
	Texture* get_texture(string path);
	Text* get_text(string text, int size = 24, bool bold = false);
	Item* get_item(string name);
	
private:
	SDL_Renderer* renderer;
	map<string, unique_ptr<Texture>> texture_map;
	map<string, unique_ptr<Text>> text_map;
	map<string, unique_ptr<Item>> items_map;
	
	void create_items();
};