#include "core/inc/Globals.h"
#include "core/inc/Resources.h"
#include "items/inc/Armor.h"
#include "items/inc/Weapon.h"
#include "items/inc/Scroll.h"
#include "items/inc/Potion.h"

#include <vector>

class Inventory
{
public:
	Inventory(Resources* _res);
	
	//tuple = (icon, name, type, inner_type, value). item_type is used if a vector of only a specific
	//item type should be returned.
	vector<tuple<Texture*, string, string, string, int>> get_items(int item_type = 0);
	
	void add_item(string name);

	//removes the first item with a name equal to name argument
	void remove_item(string name);

private:
	Resources* resources;
	vector<Item*> items;
};