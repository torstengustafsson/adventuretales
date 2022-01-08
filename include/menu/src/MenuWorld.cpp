#include "menu/inc/MenuWorld.h"

MenuWorld::MenuWorld(Resources* _res, PlayerData* _pd, function<void(bool, string)> _set_game_paused)
	: Menu(_res, _set_game_paused)
{
	player_data = _pd;

	textures["menu"] = resources->get_texture("../data/sprites/menu/menu_world.png");
	textures["button"] = resources->get_texture("../data/sprites/menu/menu_world_item.png");
	textures["button_flat"] = resources->get_texture("../data/sprites/menu/menu_world_item_flat.png");
	textures["button_marked"] = resources->get_texture("../data/sprites/menu/menu_world_item_marked.png");
	textures["button_flat_marked"] = resources->get_texture("../data/sprites/menu/menu_world_item_flat_marked.png");

	//main world menu
	texts["button1_text"] = resources->get_text("Continue", 22, true);
	texts["button2_text"] = resources->get_text("Enter Tavern", 22, true);
	texts["button3_text"] = resources->get_text("Exit Game", 22, true);
	textures["char_item"] = resources->get_texture("../data/sprites/menu/menu_world_item_character.png");
	textures["empty_item"] = resources->get_texture("../data/sprites/menu/menu_world_item_character_empty.png");
	texts["empty_text"] = resources->get_text("Empty Slot", 22, true);
	texts["empty_tips"] = resources->get_text("(Hire a new character in the Tavern)", 12, false);
	textures["character_marked"] = resources->get_texture("../data/sprites/menu/menu_world_item_character_marked.png");

	textures["char_item_big"] = resources->get_texture("../data/sprites/menu/menu_world_character_box.png");
	textures["hp_bar_back_red"] = resources->get_texture("../data/sprites/menu/health_bar_big_back_red.png");
	textures["hp_bar_back"] = resources->get_texture("../data/sprites/menu/health_bar_big_back.png");
	textures["hp_bar"] = resources->get_texture("../data/sprites/menu/health_bar_big.png");
}

//Used when user resizes the window
void MenuWorld::resize()
{
	for(auto& tex : textures)
		tex.second->set_screen_dim(screen_w, screen_h);
	for(auto& t : texts)
		t.second->set_screen_dim(screen_w, screen_h);
}



void MenuWorld::render()
{
	//always render base menu
	textures["menu"]->render(scale_x(160), 0);

	if(submenu == 0)
		render_main_world_menu();
	if(submenu == 1)
		render_character_menu();
	if(submenu == 2)
		render_character_inventory_menu();
	handle_input();
}

void MenuWorld::render_main_world_menu()
{
	const int y_adj = 20, button_y_start = 320, button_size = 64 , y_separation = 12;
	const int button1_pos = y_adj + button_y_start;
	const int button2_pos = y_adj + button_y_start + (button_size + y_separation);
	const int button3_pos = y_adj + button_y_start + 2 * (button_size +y_separation);

	//Button setup
	textures["button"]->render(scale_x(180), scale_y(button1_pos));
	texts["button1_text"]->render(scale_x(210), scale_y(button1_pos + 22));
	textures["button"]->render(scale_x(180), scale_y(button2_pos));
	texts["button2_text"]->render(scale_x(195), scale_y(button2_pos + 22));
	textures["button"]->render(scale_x(180), scale_y(button3_pos));
	texts["button3_text"]->render(scale_x(205), scale_y(button3_pos + 22));

	//Right side character portraits. Prints every character, moving downwards.
	int x = 380, y = 128, counter = 0;
	for(auto& c : player_data->get_characters() )
	{
		textures["char_item"]->render( scale_x(x), scale_y(y_adj + y + counter * y_separation) );
		c->render( scale_x(x + 20), scale_y(y_adj + y + counter * y_separation + 15), 0.5 * screen_h / 600 );

		//Stats
		texts["char_name"] = resources->get_text(c->get_name() + " the " + c->get_character_type(), 16, true);
		texts["char_level"] = resources->get_text("Level: " + to_string(c->get_level()), 12, true);
		texts["char_name"]->render(scale_x(x + 70), scale_y(y_adj + y + counter * y_separation + 10));
		texts["char_level"]->render(scale_x(x + 70), scale_y(y_adj + y + counter * y_separation + 30));

		texts["char_stats_att"] = resources->get_text("Attack: " + to_string(c->get_attack()), 10, true);
		texts["char_stats_def"] = resources->get_text("Defense: " + to_string(c->get_defense()), 10, true);
		texts["char_stats_vit"] = resources->get_text("Vitality: " + to_string(c->get_vitality()), 10, true);
		texts["char_stats_str"] = resources->get_text("Strength: " + to_string(c->get_strength()), 10, true);
		texts["char_stats_int"] = resources->get_text("Intelligence: " + to_string(c->get_intelligence()), 10, true);
		texts["char_stats_att"]->render(scale_x(x + 15), scale_y(y_adj + y + counter * y_separation + 70 + 0 * 10));
		texts["char_stats_def"]->render(scale_x(x + 15), scale_y(y_adj + y + counter * y_separation + 70 + 1 * 10));
		texts["char_stats_vit"]->render(scale_x(x + 15), scale_y(y_adj + y + counter * y_separation + 70 + 2 * 10));
		texts["char_stats_str"]->render(scale_x(x + 15), scale_y(y_adj + y + counter * y_separation + 70 + 3 * 10));
		texts["char_stats_int"]->render(scale_x(x + 15), scale_y(y_adj + y + counter * y_separation + 70 + 4 * 10));

		//extra call to resize neccessary to prevent only last character being resized
		resize();

		y += 128;
		counter++;
	}
	//Empty character portraits
	for(int i = 0; i < 3; i++)
		if(counter <= i)
		{
			textures["empty_item"]->render( scale_x(380), scale_y(128 + (128 + y_separation) * i + y_adj ));
			texts["empty_text"]->render(scale_x(430), scale_y(128 + (128 + y_separation) * i + y_adj + 45));
			texts["empty_tips"]->render(scale_x(395), scale_y(128 + (128 + y_separation) * i + y_adj + 75));
		}

	//Button highlighting (to show the currently marked button)
	if(marked_pos == 0) textures["button_marked"]->render(scale_x(176), scale_y(button1_pos-4));
	if(marked_pos == 1) textures["button_marked"]->render(scale_x(176), scale_y(button2_pos-4));
	if(marked_pos == 2) textures["button_marked"]->render(scale_x(176), scale_y(button3_pos-4));
	if(marked_pos == 3) textures["character_marked"]->render(scale_x(376), scale_y(128 + y_adj - 4));
	if(marked_pos == 4) textures["character_marked"]->render(scale_x(376), scale_y(256 + y_adj + y_separation - 4));
	if(marked_pos == 5) textures["character_marked"]->render(scale_x(376), scale_y(384 + y_adj + 2 * y_separation - 4));
}

void MenuWorld::render_character_menu()
{
	//used to access character stats
	Character* active_character =  player_data->get_characters()[character_selected_index].get();

	//Upper character portrait
	texts["character_name"] = resources->get_text(active_character->get_name() + " the " +
			active_character->get_character_type(), 22, true);
	texts["character_name"]->render(scale_x(400 - texts["character_name"]->getWidth() / 2), scale_y(140));
	textures["char_item_big"]->render( scale_x(336), scale_y(170) );
	active_character->render( scale_x(366), scale_y(190), 1.0 * screen_h / 600 );

	//Button setup
	int inv_size = active_character->get_inventory().size();
	int traits_size = active_character->get_traits().size();
	string inventory_text = string("Inventory (") + to_string(inv_size) + string(")");
	string traits_text = string("Traits (") + to_string(traits_size) + string(")");
	texts["button1_char_text"] = resources->get_text(inventory_text , 18, true);
	texts["button2_char_text"] = resources->get_text(traits_text, 18, true);
	texts["button3_char_text"] = resources->get_text("Back", 22, true);
	textures["button_flat"]->render(scale_x(430), scale_y(420));
	texts["button1_char_text"]->render(scale_x(460), scale_y(428));
	textures["button_flat"]->render(scale_x(430), scale_y(460));
	texts["button2_char_text"]->render(scale_x(460), scale_y(468));
	textures["button"]->render(scale_x(320), scale_y(504));
	texts["button3_char_text"]->render(scale_x(370), scale_y(526));

	//Stats
	texts["char_level"] = resources->get_text("Level: " + to_string(active_character->get_level()), 18, true);
	texts["experience"] = resources->get_text("Experience: " + to_string(active_character->get_experience()), 14, true);
	texts["next_level"] = resources->get_text("Next level: " + to_string(active_character->get_exp_next_rel()), 14, true);
	texts["line"] = resources->get_text("--------------------", 18, true);
	texts["char_level"]->render(scale_x(200), scale_y(320));
	texts["experience"]->render(scale_x(200), scale_y(340));
	texts["next_level"]->render(scale_x(200), scale_y(360));
	texts["line"]->render(scale_x(200), scale_y(370));

	texts["char_stats_att"] = resources->get_text("Attack: " + to_string(active_character->get_attack()), 14, true);
	texts["char_stats_def"] = resources->get_text("Defense: " + to_string(active_character->get_defense()), 14, true);
	texts["char_stats_vit"] = resources->get_text("Vitality: " + to_string(active_character->get_vitality()), 14, true);
	texts["char_stats_str"] = resources->get_text("Strength: " + to_string(active_character->get_strength()), 14, true);
	texts["char_stats_int"] = resources->get_text("Intelligence: " + to_string(active_character->get_intelligence()), 14, true);
	texts["char_stats_att"]->render(scale_x(200), scale_y(390 + 20 * 0));
	texts["char_stats_def"]->render(scale_x(200), scale_y(390 + 20 * 1));
	texts["char_stats_vit"]->render(scale_x(200), scale_y(390 + 20 * 2));
	texts["char_stats_str"]->render(scale_x(200), scale_y(390 + 20 * 3));
	texts["char_stats_int"]->render(scale_x(200), scale_y(390 + 20 * 4));

	string hp_string = string("Hit points: ") + to_string(active_character->get_hit_points_current()) +
			string(" / ") + to_string(active_character->get_hit_points_max());
	texts["hp_text"] = resources->get_text(hp_string, 12, true);
	textures["hp_bar_back_red"]->render(scale_x(370), scale_y(340));
	float percent = static_cast<float>(active_character->get_hit_points_current()) / static_cast<float>(active_character->get_hit_points_max());
	SDL_Rect hp_bar_clip = SDL_Rect{0,0,static_cast<int>(percent*192),32};
	textures["hp_bar_back"]->render(scale_x(370), scale_y(340), &hp_bar_clip);
	textures["hp_bar"]->render(scale_x(370), scale_y(340));
	texts["hp_text"]->render(scale_x(400), scale_y(350));

	//Button highlighting (to show the currently marked button)
	if(marked_pos == 0) textures["button_flat_marked"]->render(scale_x(426), scale_y(416));
	if(marked_pos == 1) textures["button_flat_marked"]->render(scale_x(426), scale_y(456));
	if(marked_pos == 2) textures["button_marked"]->render(scale_x(316), scale_y(500));
}

void MenuWorld::render_character_inventory_menu()
{
	//used to access character stats
	Character* active_character =  player_data->get_characters()[character_selected_index].get();;

	//Button setup
	texts["button1_inv_text"] = resources->get_text("All" , 18, true);
	texts["button2_inv_text"] = resources->get_text("Weapons" , 18, true);
	texts["button3_inv_text"] = resources->get_text("Armor" , 18, true);
	texts["button4_inv_text"] = resources->get_text("Scrolls" , 18, true);
	texts["button5_inv_text"] = resources->get_text("Potions" , 18, true);
	texts["button6_inv_text"] = resources->get_text("Back" , 22, true);
	textures["button_flat"]->render(scale_x(200), scale_y(140));
	texts["button1_inv_text"]->render(scale_x(200 + (textures["button_flat"]->getWidth() - texts["button1_inv_text"]->getWidth()) / 2), scale_y(148));
	textures["button_flat"]->render(scale_x(200), scale_y(180));
	texts["button2_inv_text"]->render(scale_x(200 + (textures["button_flat"]->getWidth() - texts["button2_inv_text"]->getWidth()) / 2), scale_y(188));
	textures["button_flat"]->render(scale_x(200), scale_y(220));
	texts["button3_inv_text"]->render(scale_x(200 + (textures["button_flat"]->getWidth() - texts["button3_inv_text"]->getWidth()) / 2), scale_y(228));
	textures["button_flat"]->render(scale_x(200), scale_y(260));
	texts["button4_inv_text"]->render(scale_x(200 + (textures["button_flat"]->getWidth() - texts["button4_inv_text"]->getWidth()) / 2), scale_y(268));
	textures["button_flat"]->render(scale_x(200), scale_y(300));
	texts["button5_inv_text"]->render(scale_x(200 + (textures["button_flat"]->getWidth() - texts["button5_inv_text"]->getWidth()) / 2), scale_y(308));
	textures["button"]->render(scale_x(320), scale_y(504));
	texts["button6_inv_text"]->render(scale_x(370), scale_y(526));

	//TODO: Render the inventory
	active_character->get_inventory();

	//Button highlighting (to show the currently marked button)
	if(marked_pos == 0) textures["button_flat_marked"]->render(scale_x(196), scale_y(136));
	if(marked_pos == 1) textures["button_flat_marked"]->render(scale_x(196), scale_y(176));
	if(marked_pos == 2) textures["button_flat_marked"]->render(scale_x(196), scale_y(216));
	if(marked_pos == 3) textures["button_flat_marked"]->render(scale_x(196), scale_y(256));
	if(marked_pos == 4) textures["button_flat_marked"]->render(scale_x(196), scale_y(296));
	if(marked_pos == 5) textures["button_marked"]->render(scale_x(316), scale_y(500));
}

void MenuWorld::handle_action()
{
	if( submenu == 0 )
	{
		if(marked_pos == 0)
		{
			//exit menu
			set_visible(false);
			set_game_paused(false, "MenuWorld");
		}
		if(marked_pos == 2)
		{
			//quit = true;
		}

		for(unsigned int i = 0; i < player_data->get_characters().size(); i++)
		{
			if(marked_pos == 3 + i)
			{
				character_selected_index = i;
				marked_pos = 0;
				submenu = 1;
			}
		}
	}

	else if( submenu == 1 )
	{
		if(marked_pos == 0)
		{
			marked_pos = 0;
			submenu = 2;
		}
		if(marked_pos == 2)
		{
			//return to last position
			marked_pos = 3 + character_selected_index;
			submenu = 0;
		}
	}

	else if( submenu == 2 )
	{
		if(marked_pos == 5)
		{
			//return to last position
			marked_pos = 0;
			submenu = 1;
		}
	}
}

void MenuWorld::handle_input()
{
	const Uint8 *keyState = SDL_GetKeyboardState(NULL);
	if( keyState[SDL_SCANCODE_LEFT] )
	{
		if(!button_pressed && marked_pos >= 3)
		{
			if(submenu == 0)
			{
				marked_pos -= 3;
			}
		}
		button_pressed = true;
	}
	else if( keyState[SDL_SCANCODE_RIGHT] )
	{
		if(!button_pressed && marked_pos < 3)
		{
			if(submenu == 0)
			{
				marked_pos += 3;
			}
		}
		button_pressed = true;
	}
	else if( keyState[SDL_SCANCODE_DOWN] )
	{
		if(!button_pressed)
		{
			if( (submenu == 0 && marked_pos != 2 && marked_pos != 5) ||
				(submenu == 1 && marked_pos != 2) ||
				(submenu == 2 && marked_pos != 5) )
			{
				marked_pos++;
			}
		}
		button_pressed = true;
	}
	else if( keyState[SDL_SCANCODE_UP] )
	{
		if(!button_pressed)
		{
			if( (submenu == 0 && marked_pos != 0 && marked_pos != 3) ||
				(submenu == 1 && marked_pos != 0) ||
				(submenu == 2 && marked_pos != 0) )
			{
				marked_pos--;
			}
		}
		button_pressed = true;
	}
	else if( keyState[SDL_SCANCODE_SPACE] )
	{
		if(!button_pressed)
		{
			handle_action();

		}
		button_pressed = true;
	}
	else if( keyState[SDL_SCANCODE_RETURN] )
	{
		if(!button_pressed)
		{
			//exit menu
			set_visible(false);
			set_game_paused(false, "MenuWorld");
		}
	}
	else
	{
		button_pressed = false;
	}
}

void MenuWorld::set_visible(bool val)
{
	submenu = 0;
	marked_pos = 0;
	button_pressed = true;
	visible = val;
}