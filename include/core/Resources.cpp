#include "Resources.h"
#include <string>

Resources::Resources(SDL_Renderer* _renderer)
{
	renderer = _renderer;
	create_items();
}

Texture* Resources::get_texture(string path)
{
	//Create if not exist
	if ( texture_map.find(path) == texture_map.end() ) 
	  texture_map[path] = unique_ptr<Texture>( new Texture(renderer, path));
	
	return texture_map[path].get();
}

Text* Resources::get_text(string text, int size, bool bold)
{
	//size and bold need to be indexed to allow same text of differing sizes and boldness.
	string val = string(text) + to_string(size) + to_string(bold);
	
	//Create if not exist
	if ( text_map.find(val) == text_map.end() ) 
	  text_map[val] = unique_ptr<Text>( new Text(renderer, text, size, bold));
	
	//text_map[text]->set_font(size, bold);
	return text_map[val].get();
}

Item* Resources::get_item(string name)
{
	if ( items_map.find(name) != items_map.end() )
		return items_map[name].get();
	return nullptr;
}

void Resources::create_items()
{
	string path = "../data/sprites/items";
	items_map["Iron Sword"] = unique_ptr<Item>(new Weapon(get_texture(path + "/weapons/iron_sword.png"), "Iron Sword", "Sword", 5));
	items_map["Steel Helmet"] = unique_ptr<Item>(new Armor(get_texture(path + "/weapons/iron_sword.png"), "Steel Helmet", "Helmet", 1));
	items_map["Healing Potion"] = unique_ptr<Item>(new Potion(get_texture(path + "/weapons/iron_sword.png"), "Healing Potion", "HP Restore", 10));
	items_map["Fireball Scroll"] = unique_ptr<Item>(new Scroll(get_texture(path + "/weapons/iron_sword.png"), "Fireball Scroll", "Fireball"));
}