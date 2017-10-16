#pragma once

#include "Menu.h"
#include "core/inc/PlayerData.h"

class MainMenu : public Menu
{
public:
	MainMenu(Resources* _res, PlayerData* _pd, function<void(bool, string)> _set_game_paused);
	
	void render() override;
	
	void set_visible(const bool val) override;

	void handle_action();
private:
	PlayerData* player_data;
	
	//represents the currently active menu button.
	unsigned int marked_pos = 0;
	bool button_pressed = true;
	
	void handle_input();
};