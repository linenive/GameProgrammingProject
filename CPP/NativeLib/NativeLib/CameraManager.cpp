#include "CameraManager.h"

void CameraManager::_register_methods() {

	register_method("SetScreenSize", &CameraManager::SetScreenSize);

	register_property<CameraManager, float>("screenBounds_left", &CameraManager::screenBounds_left, 0);
	register_property<CameraManager, float>("screenBounds_right", &CameraManager::screenBounds_right, 0);
	register_property<CameraManager, float>("screenBounds_up", &CameraManager::screenBounds_up, 0);
	register_property<CameraManager, float>("screenBounds_down", &CameraManager::screenBounds_down, 0);
}
void CameraManager::_init() {

}


void CameraManager::DetectScreenBounds(Vector2 newScreenSize)
{
	screenBounds_left = -newScreenSize.x;
	screenBounds_right = newScreenSize.x;
	screenBounds_up = -newScreenSize.y;
	screenBounds_down = newScreenSize.y;
}

void CameraManager::SetScreenSize(Vector2 nowScreenSize){
	DetectScreenBounds(nowScreenSize);
}

void CameraManager::SetTarget(Vector2 pos){
}

void CameraManager::ReleaseTarget(Vector2 pos){
}
