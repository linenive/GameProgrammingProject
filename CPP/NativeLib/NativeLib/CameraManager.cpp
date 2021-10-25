#include "CameraManager.h"

void CameraManager::_register_methods() {

	register_method("_ready", &CameraManager::_ready);
	register_method("SetLimit", &CameraManager::SetLimit);
	register_method("InitCameraSetting", &CameraManager::InitCameraSetting);
	register_method("CameraMovewithKey", &CameraManager::CameraMovewithKey);
	register_method("CameraMovewithMouse", &CameraManager::CameraMovewithMouse);
	register_method("SetCameraSetting_Default", &CameraManager::SetCameraSetting_Default);
	register_method("SetCameraSetting_Trace", &CameraManager::SetCameraSetting_Trace);
	register_method("ZoomOut", &CameraManager::ZoomOut);
	register_method("ZoomIn", &CameraManager::ZoomIn);

	register_property<CameraManager, eCameraState>("g_nowcamerastate", &CameraManager::g_nowcamerastate, eCameraState::DEFAULT);
	register_property<CameraManager, Node2D>("g_targetNode", &CameraManager::g_targetNode, Node2D());
	register_property<CameraManager, NodePath>("g_nowtarget_path", &CameraManager::g_nowtarget_path, NodePath());
	register_property<CameraManager, Vector2>("g_now_position", &CameraManager::g_now_position, Vector2());
	register_property<CameraManager, float>("g_now_scrollfactor", &CameraManager::g_now_scrollfactor, 0);
}
void CameraManager::_init() {

}

void godot::CameraManager::SetLimit(){
	g_screen_size = get_viewport_rect().size;
	g_unmoving_size = g_screen_size - Vector2(g_unmoving_interval, g_unmoving_interval);
}

void godot::CameraManager::SetCameraSetting_Default(){
	g_nowcamerastate = eCameraState::DEFAULT;
	g_nowtarget_path = "";
	g_targetNode = Node2D();
	Zoom(kzoom_default);
}

void godot::CameraManager::SetCameraSetting_Trace(NodePath newtracing_path){
	g_nowcamerastate = eCameraState::TRACE;
	g_nowtarget_path = newtracing_path;
	//g_targetNode = get_node(newtracing_path);
	Zoom(kzoom_in);
}

void godot::CameraManager::CameraMovewithKey(){
	//DetectKeyPress();
	if (g_velocity.length() > 0) {
		g_velocity = g_velocity.normalized() * g_speed;
		g_now_position += g_velocity;
	}
}

void godot::CameraManager::CameraMovewithMouse(Vector2 nowmousevector){
	Vector2 addPos = Vector2(0, 0);
	if (nowmousevector.x < g_unmoving_interval) {
		addPos.x = -g_speed;
	}
	else if (nowmousevector.x > g_unmoving_size.x) {
		addPos.x = g_speed;
	}
	if (nowmousevector.y < g_unmoving_interval) {
		addPos.y = -g_speed;
	}
	else if (nowmousevector.y > g_unmoving_size.y) {
		addPos.y = g_speed;
	}
	g_now_position += addPos;
}

void godot::CameraManager::InitCameraSetting(){
	SetCameraSetting_Default();
}

void godot::CameraManager::ZoomOut(float now_zoom){
	float next_scrollfactor = now_zoom + kzoom_scrollfactor;
	if (next_scrollfactor < kzoom_max)
		Zoom(next_scrollfactor);
}

void godot::CameraManager::ZoomIn(float now_zoom){
	float next_scrollfactor = now_zoom - kzoom_scrollfactor;
	if (next_scrollfactor > kzoom_min)
		Zoom(next_scrollfactor);
}

void godot::CameraManager::Zoom(float zoomfactor){
	g_now_scrollfactor = zoomfactor;
}
