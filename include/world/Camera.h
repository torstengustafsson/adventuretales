#include "../core/Globals.h"
#include "Player.h"
#include "Object.h"

#include <vector>

class Camera
{
public:
	Camera(Player* player);
	
	void set_view(const vector<Object*>& v, float screen_w, float screen_h);
	
	void set_view(Object* o, float screen_w, float screen_h);
	
private:
	Player* player;

	int* corners;
	int screen_width = 800, screen_height = 600;
};