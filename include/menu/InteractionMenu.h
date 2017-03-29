#pragma once

#include "Menu.h"

using namespace std::placeholders;

//Displays the text returned when player interacts with certain objects
class InteractionMenu : public Menu
{
public:
	InteractionMenu(Resources* _res, function<void(bool, string)> _set_game_paused);

	void render() override;
	void resize() override;
	
	void set_text(string _header, string _text);
	
private:
	string header;	//usually the name of an NPC
	string text;	//the text to display
	
	bool key_pressed = true;
	
	const unsigned int ROW_CHAR_LIMIT = 65;
};