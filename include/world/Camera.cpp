#include "Camera.h"

Camera::Camera(Player* _player)
{
	player = _player;
	corners = new int[4];
}

void Camera::set_view(const vector<Object*>& v, float screen_w, float screen_h)
{
	for(auto& o : v)
	{
		if(!dynamic_cast<Player*>(o))
		{
			//384 and 284 comes from middle of screen (800 / 2 - 16 and 600 / 2 -16)
			o->set_x_camera( (o->get_x() - player->get_x() + 384) * screen_w / 800 );
			o->set_y_camera( (o->get_y() - player->get_y() + 284) * screen_h / 600 );
		}
	}
	//On resize, player also need to get new camera position
	player->set_x_camera( screen_w / 2 - 16 * screen_w / 800 );
	player->set_y_camera( screen_h / 2 - 16 * screen_h / 600 );
}

void Camera::set_view(Object* o, float screen_w, float screen_h)
{	
	o->set_x_camera(o->get_x() - player->get_x() + player->get_x_camera());
	o->set_y_camera(o->get_y() - player->get_y() + player->get_y_camera());
}