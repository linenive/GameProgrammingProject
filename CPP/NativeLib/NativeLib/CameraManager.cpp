#include "CameraManager.h"

void CameraManager::_register_methods() {
	register_method("CameraMove_Left", &CameraManager::CameraMove_Left);
	register_method("CameraMove_Right", &CameraManager::CameraMove_Right);
	register_method("CameraMove_Up", &CameraManager::CameraMove_Up);
	register_method("CameraMove_Down", &CameraManager::CameraMove_Down);

	register_method("SetScreenSize", &CameraManager::SetScreenSize);

	register_property<CameraManager, float>("screenBounds_left", &CameraManager::screenBounds_left, 0);
	register_property<CameraManager, float>("screenBounds_right", &CameraManager::screenBounds_right, 0);
	register_property<CameraManager, float>("screenBounds_up", &CameraManager::screenBounds_up, 0);
	register_property<CameraManager, float>("screenBounds_down", &CameraManager::screenBounds_down, 0);
}
void godot::CameraManager::DetectScreenBounds(Vector2 newScreenSize)
{
	screenBounds_left = -newScreenSize.x;
	screenBounds_right = newScreenSize.x;
	screenBounds_up = -newScreenSize.y;
	screenBounds_down = newScreenSize.y;
}

void godot::CameraManager::SetScreenSize(Vector2 nowScreenSize)
{
	DetectScreenBounds(nowScreenSize);
}

void godot::CameraManager::CameraMove_Left()
{
	nowAddVector.x = -1;
}

void godot::CameraManager::CameraMove_Right()
{
	nowAddVector.x = 1;
}

void godot::CameraManager::CameraMove_Up()
{
	nowAddVector.y = -1;
}

void godot::CameraManager::CameraMove_Down()
{
	nowAddVector.y = 1;
}
