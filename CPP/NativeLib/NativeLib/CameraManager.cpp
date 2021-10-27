#include "CameraManager.h"

void CameraManager::_register_methods() {

	register_method("_init", &CameraManager::_init);
	register_method("SetMouseMovingBound", &CameraManager::SetMouseMovingBound);

	register_method("SetNowCameraPosition", &CameraManager::SetNowCameraPosition);
	register_method("GetNowCameraPosition", &CameraManager::GetNowCameraPosition);

	register_method("CameraMoveWithKey", &CameraManager::CameraMoveWithKey);
	register_method("CameraMoveWithMouse", &CameraManager::CameraMoveWithMouse);

	register_method("ZoomOut", &CameraManager::ZoomOut);
	register_method("ZoomIn", &CameraManager::ZoomIn);

	register_method("SetNowZoom", &CameraManager::SetNowZoom);
	register_method("GetNowZoom", &CameraManager::GetNowZoom);

	register_method("SetNowZoomMax", &CameraManager::SetNowZoomMax);
	register_method("GetNowZoomMax", &CameraManager::GetNowZoomMax);

	register_method("SetNowZoomMin", &CameraManager::SetNowZoomMin);
	register_method("GetNowZoomMin", &CameraManager::GetNowZoomMin);

	register_property<CameraManager, float>("g_speed", &CameraManager::g_speed, 3);
	register_property<CameraManager, float>("g_mouse_moving_interval", &CameraManager::g_mouse_moving_interval, 100);
	register_property<CameraManager, float>("g_zoom_max", &CameraManager::g_zoom_max, 1.5);
	register_property<CameraManager, float>("g_zoom_min", &CameraManager::g_zoom_min, 0.5);
}
void CameraManager::_init() {
}

void godot::CameraManager::SetMouseMovingBound(){
	float interval = g_mouse_moving_interval * g_now_zoom;
	g_mouse_moving_bound = get_viewport_rect().size - Vector2(interval, interval);
}

void godot::CameraManager::CameraMoveWithKey(Vector2 velocity){
	if (velocity.length() > 0) {
		velocity = velocity.normalized() * g_speed;
		g_now_position += velocity;
	}
}

void godot::CameraManager::CameraMoveWithMouse(Vector2 now_mouse_vector){
	Vector2 add_pos = Vector2(0, 0);
	if (now_mouse_vector.x < g_mouse_moving_interval) {
		add_pos.x = -g_speed;
	}
	else if (now_mouse_vector.x > g_mouse_moving_bound.x) {
		add_pos.x = g_speed;
	}
	if (now_mouse_vector.y < g_mouse_moving_interval) {
		add_pos.y = -g_speed;
	}
	else if (now_mouse_vector.y > g_mouse_moving_bound.y) {
		add_pos.y = g_speed;
	}
	g_now_position += add_pos;
}

void godot::CameraManager::ZoomOut(){
	float next_scrollfactor = g_now_zoom + kzoom_scrollfactor;
	if (next_scrollfactor < g_zoom_max)
		SetNowZoom(next_scrollfactor);
}

void godot::CameraManager::ZoomIn(){
	float next_scrollfactor = g_now_zoom - kzoom_scrollfactor;
	if (next_scrollfactor > g_zoom_min)
		SetNowZoom(next_scrollfactor);
}

void godot::CameraManager::SetNowZoom(float new_zoom){
	g_now_zoom = new_zoom;
	SetMouseMovingBound();
}



