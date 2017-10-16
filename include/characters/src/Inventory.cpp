#include "characters/inc/Inventory.h"
#include <string>

Inventory::Inventory(Resources* _res)
{
	resources = _res;
}

//TODO: Fix this ugly function
vector<tuple<Texture*, string, string, string, int>> Inventory::get_items(int item_type)
{
	vector<tuple<Texture*, string, string, string, int>> v;
	for( auto& i : items )
	{	
		if( (item_type == GENERAL_ITEM || item_type == SCROLL) && dynamic_cast<Scroll*>(i) )
			v.push_back(make_tuple(i->get_icon(), i->get_name(), "Scroll", i->get_type(), i->get_value()));

		else if( (item_type == GENERAL_ITEM || item_type == WEAPON) && dynamic_cast<Weapon*>(i) )
			v.push_back(make_tuple(i->get_icon(), i->get_name(), "Weapon", i->get_type(), i->get_value()));
		
		else if( (item_type == GENERAL_ITEM || item_type == ARMOR) && dynamic_cast<Armor*>(i) )
			v.push_back(make_tuple(i->get_icon(), i->get_name(), "Armor", i->get_type(), i->get_value()));
				
		else if( (item_type == GENERAL_ITEM || item_type == POTION) && dynamic_cast<Potion*>(i) )
			v.push_back(make_tuple(i->get_icon(), i->get_name(), "Potion", i->get_type(), i->get_value()));
	}
	
	return v;
}

void Inventory::add_item(string name)
{
	if(resources->get_item(name) != nullptr)
		items.push_back(resources->get_item(name));
	else
		cout << "Error. Item '" << name << "' does not exist.\n";
}

void Inventory::remove_item(string name)
{
	for(unsigned int i = 0; i < items.size(); i++)
	{
		if(name == items.at(i)->get_name())
		{
			items.erase(items.begin() + i);
			return;
		}
	}
	cout << "Error. Character does not have item '" << name << "'.\n";
}