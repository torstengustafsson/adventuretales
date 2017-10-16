#pragma once

#include "textures/inc/Texture.h"

#include <memory>

class Object
{
public:
	virtual ~Object() = default;
	Object( Texture* _tex, string _name, int _x_tile_index, int _y_tile_index, int _x_pos = 0, int _y_pos = 0, 
		int _x_pos_camera = 0, int _y_pos_camera = 0, SDL_Rect _clip = { 0, 0, 0, 0 } );
	
	void render();
	
	int get_x();
	int get_y();
	int get_x_camera();
	int get_y_camera();
	int get_x_tile();
	int get_y_tile();
	
	int* get_collision_box();
	int* get_center_of_mass();
	bool is_in_air();
	string get_name();
	
	void set_x(int val);
	void set_y(int val);
	void set_x_camera(int val);
	void set_y_camera(int val);
	void set_x_tile(int val);
	void set_y_tile(int val);
	void set_rotation(float val);
	void set_name(string _name);
	
	void set_screen_dim(int w, int h);
	
	void change_clip(SDL_Rect c);
	void change_texture(Texture* _tex);
	
	//Every object is interactable, but for most of them nothing happens. Returns a string of interaction text.
	virtual string interact(int dir);
	
private:
	Texture* texture;
	
	string name;	//the name that will be displayed during player interaction etc.
	
	//Real screen positions in world coordinates and camera coordinates
	int x_pos_world, y_pos_world;
	int x_pos_camera, y_pos_camera;
	
	//Index positions used for collision handling
	int x_tile_index, y_tile_index;

	float angle; //rotation angle
	int collision_box[2]; //width and height
	
	SDL_Rect clip;
};