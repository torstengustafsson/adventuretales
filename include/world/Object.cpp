#include "Object.h"

Object::Object(Texture* _tex, string _name, int _x_tile_index, int _y_tile_index, int _x_pos, int _y_pos, 
	int _x_pos_camera, int _y_pos_camera, SDL_Rect _clip)
{
	texture = _tex;
	name = _name;
	x_tile_index = _x_tile_index;
	y_tile_index = _y_tile_index;
	x_pos_world = _x_pos != 0 ? _x_pos : 32 * _x_tile_index;
	y_pos_world = _y_pos != 0 ? _y_pos : 32 * _y_tile_index;
	x_pos_camera = _x_pos_camera;
	y_pos_camera = _y_pos_camera;
	
	if( _clip.w == 0 && _clip.h == 0 )
	{
		_clip.w = texture->getWidth();
		_clip.h = texture->getHeight();
	}
	clip = _clip;
	
	angle = 0;
	
	//Currently uses simple box colliders based on texture size
	collision_box[0] = texture->getWidth();
	collision_box[1] = texture->getHeight();
}

void Object::render()
{
	texture->render(x_pos_camera, y_pos_camera, &clip, 1.0);
}

int Object::get_x()
{
	return x_pos_world;
}

int Object::get_y()
{
	return y_pos_world;
}

int Object::get_x_camera()
{
	return x_pos_camera;
}

int Object::get_y_camera()
{
	return y_pos_camera;
}

int Object::get_x_tile()
{
	return x_tile_index;
}

int Object::get_y_tile()
{
	return y_tile_index;
}

string Object::get_name()
{
	return name;
}

int* Object::get_collision_box()
{
	return collision_box;
}

void Object::set_x(int val)
{
	x_pos_world = val;
}

void Object::set_y(int val)
{
	y_pos_world = val;
}

void Object::set_x_camera(int val)
{
	x_pos_camera = val;
}

void Object::set_y_camera(int val)
{
	y_pos_camera = val;
}

void Object::set_x_tile(int val)
{
	x_tile_index = val;
}

void Object::set_y_tile(int val)
{
	y_tile_index = val;
}

void Object::set_rotation(float val)
{
	angle = val;
}

void Object::set_name(string _name)
{
	name = _name;
}

void Object::set_screen_dim(int w, int h)
{
	texture->set_screen_dim(w, h);
}

void Object::change_texture(Texture* _tex)
{
	texture = _tex;
}

void Object::change_clip(SDL_Rect c)
{
	clip = c;
}

string Object::interact(int dir)
{
	return "";}