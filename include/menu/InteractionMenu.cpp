#include "InteractionMenu.h"

InteractionMenu::InteractionMenu(Resources* _res, function<void(bool, string)> _set_game_paused)
	: Menu(_res, _set_game_paused) {}

void InteractionMenu::set_text(string _header, string _text)
{
	header = _header;
	text = _text;
}

//InteractionMenu is simple enough that texture pointers don't need to be stored in class.
//Must still override resize function because other menu types uses it (Called by Menu::set_screen_dim())
void InteractionMenu::resize()
	{}

void InteractionMenu::render()
{
	//Background box
	Texture* menu = resources->get_texture("../data/sprites/menu/interaction_menu.png");
	menu->set_screen_dim(screen_w, screen_h);
	menu->render(scale_x(0), scale_y(400));
	
	Text* header_text = resources->get_text(header, 32, true);
	header_text->set_screen_dim(screen_w, screen_h);
	
	string temp_text = text;
	vector<Text*> rows;
	while(temp_text.length() > ROW_CHAR_LIMIT)
	{
		string row_text = temp_text.substr(0, ROW_CHAR_LIMIT);
		temp_text = temp_text.substr(ROW_CHAR_LIMIT);			//remove the added text from string
		int q = temp_text.find(" ");	//fix for when a line ends at the last word (no space character)
		row_text += temp_text.substr(0, q != -1 ? q : temp_text.back());	//if we cut a word, add it
		temp_text = temp_text.substr((q != -1 ? q : temp_text.length()));	//remove that word too, plus the space
		rows.push_back(resources->get_text(row_text, 22));
		rows.back()->set_screen_dim(screen_w, screen_h);
	}
	if(temp_text.length() > 0)	//add last row if there is still text to print
	{
		rows.push_back(resources->get_text(temp_text, 22));
		rows.back()->set_screen_dim(screen_w, screen_h);
	}
	
	//Render text
	header_text->render(scale_x(40), scale_y(440));
	int count = 0;
	for(auto& row : rows)
	{
		row->render(scale_x(40), scale_y(480 + count * 24));
		count++;
	}
	
	
	// InteractionMenu is only concerned about closing input, so it handles it own input, instead of 
	// relying on an external input handler.
	const Uint8 *keyState = SDL_GetKeyboardState(NULL);
	if( keyState[SDL_SCANCODE_SPACE] || keyState[SDL_SCANCODE_RETURN] )
	{
		if ( !key_pressed )
		{
			text = "";
			key_pressed = true;
			set_game_paused(false, "InteractionMenu");
		}
	}
	else
		key_pressed = false;
}