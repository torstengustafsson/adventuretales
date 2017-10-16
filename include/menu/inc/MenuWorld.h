#pragma once

#include "Menu.h"
#include "core/inc/PlayerData.h"

//The in-game menu accessible from 'world' mode.
class MenuWorld : public Menu
{
public:
	MenuWorld(Resources* _res, PlayerData* _pd, function<void(bool, string)> _set_game_paused);
	
	void render() override;

	void resize() override;

	void set_visible(const bool val) override;
	void handle_action();
	
private:
	PlayerData* player_data;
	
	//Maps that contain all menu buttons and text
	map<string, Texture*> textures;
	map<string, Text*> texts;
	
	// 0 = main world menu. 1 = character menu. 2 = character inventory menu.
	int submenu = 0;
	
	void render_main_world_menu();
	void render_character_menu();
	void render_character_inventory_menu();
	
	//represents the currently active menu button.
	unsigned int marked_pos = 0;
	bool button_pressed = true;
	//index of the currently selected character, when submenu is either 1 or 2.
	unsigned int character_selected_index;
	
	void handle_input();
};