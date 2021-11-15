#include "CameraManager.h"

void CameraManager::_register_methods() {

	register_method("_init", &CameraManager::_init);

	register_method("SetCurrentCameraPosition", &CameraManager::SetCurrentCameraPosition);
	register_method("GetCurrentCameraPosition", &CameraManager::GetCurrentCameraPosition);

	register_method("CameraMoveWithKey", &CameraManager::CameraMoveWithKey);
	register_method("CameraMoveWithMouse", &CameraManager::CameraMoveWithMouse);

	register_method("ZoomOut", &CameraManager::ZoomOut);
	register_method("ZoomIn", &CameraManager::ZoomIn);

	register_method("SetCurrentZoom", &CameraManager::SetCurrentZoom);
	register_method("GetCurrentZoom", &CameraManager::GetCurrentZoom);

	register_method("SetCurrentZoomMax", &CameraManager::SetCurrentZoomMax);
	register_method("GetCurrentZoomMax", &CameraManager::GetCurrentZoomMax);

	register_method("SetCurrentZoomMin", &CameraManager::SetCurrentZoomMin);
	register_method("GetCurrentZoomMin", &CameraManager::GetCurrentZoomMin);

	register_property<CameraManager, float>("g_speed", &CameraManager::camera_moving_speed, 3);
	register_property<CameraManager, float>("g_mouse_moving_interval", &CameraManager::mouse_moving_bound_size, 100);
	register_property<CameraManager, float>("g_zoom_max", &CameraManager::zoom_max, 1.5);
	register_property<CameraManager, float>("g_zoom_min", &CameraManager::zoom_min, 0.5);
	register_property<CameraManager, float>("g_zoom_scroll_factor", &CameraManager::zoom_scroll_factor, 0.2);
}
void CameraManager::_init() {
}

void godot::CameraManager::CameraMoveWithKey(Vector2 velocity) {
	if (velocity.length() > 0) {
		velocity = velocity.normalized() * camera_moving_speed * camera.GetZoomDegree();
		camera.CameraMove(CalcNewPosition(velocity));
	}
}

void godot::CameraManager::CameraMoveWithMouse(Vector2 now_mouse_vector) {
	Vector2 add_pos = Vector2(0, 0);

	if (now_mouse_vector.x < mouse_moving_bound_size) {
		add_pos.x = -camera_moving_speed * camera.GetZoomDegree();
	}
	else if (now_mouse_vector.x > get_viewport_rect().size.x - mouse_moving_bound_size) {
		add_pos.x = camera_moving_speed * camera.GetZoomDegree();
	}
	if (now_mouse_vector.y < mouse_moving_bound_size) {
		add_pos.y = -camera_moving_speed * camera.GetZoomDegree();
	}
	else if (now_mouse_vector.y > get_viewport_rect().size.y - mouse_moving_bound_size) {
		add_pos.y = camera_moving_speed * camera.GetZoomDegree();
	}
	camera.CameraMove(CalcNewPosition(add_pos));
}

Vector2 godot::CameraManager::CalcNewPosition(Vector2 new_position) {
	new_position += camera.GetPosition();

	Vector2 restrict_bound_min = get_viewport_rect().size / 2;
	Vector2 restrict_bound_max = Vector2(DEFAULT_TILE_NUMBER_X * TILE_WIDTH, DEFAULT_TILE_NUMBER_Y * TILE_HEIGHT) - restrict_bound_min;
	if (new_position.x < restrict_bound_min.x) {
		new_position.x = restrict_bound_min.x;
	}
	else if (new_position.x > restrict_bound_max.x) {
		new_position.x = restrict_bound_max.x;
	}
	if (new_position.y < restrict_bound_min.y) {
		new_position.y = restrict_bound_min.y;
	}
	else if (new_position.y > restrict_bound_max.y) {
		new_position.y = restrict_bound_max.y;
	}
	return new_position;
}

void godot::CameraManager::ZoomOut() {
	float next_scrollfactor = camera.GetZoomDegree() + zoom_scroll_factor;
	float zoom_max_current = zoom_max;
	//Godot::print("[CameraManager] zoom max current: " + Vector2(next_scrollfactor, zoom_max_current));// +" / new_position :  " + new_position);
	if (next_scrollfactor < zoom_max_current)
		SetCurrentZoom(next_scrollfactor);
}

void godot::CameraManager::ZoomIn() {
	float next_scrollfactor = camera.GetZoomDegree() - zoom_scroll_factor;
	if (next_scrollfactor > zoom_min)
		SetCurrentZoom(next_scrollfactor);
}

void godot::CameraManager::SetCurrentZoom(float new_zoom) {
	camera.SetZoomDegree(new_zoom);
}



