#include "InputManager.h"
#include "GodotScenePath.h"

void InputManager::StartDrag(Vector2 start_pos) {
	drag_start_point = start_pos;
	is_dragging = true;
}

void InputManager::EndDrag(Vector2 end_pos) {
	is_dragging = false;
}

void InputManager::MouseClick(Vector2 position) {
	Godot::print("[InputManager]Mouse Click: " + position);

	StartDrag(position);
}

void InputManager::MouseRelease(Vector2 position) {
	Godot::print("[InputManager]Mouse Release: " + position);

	EndDrag(position);

}

void InputManager::MouseHover(Vector2 position) {
	now_mouse_point = position;
}

bool InputManager::IsDragging()
{
	return is_dragging;
}

Rect2 InputManager::GetDragRect()
{
	Vector2 drag_left_top = Vector2();
	Vector2 drag_size = Vector2();

	if (drag_start_point.x > now_mouse_point.x) {
		drag_left_top.x = now_mouse_point.x;
		drag_size.x = drag_start_point.x - now_mouse_point.x;
	}else {
		drag_left_top.x = drag_start_point.x;
		drag_size.x = now_mouse_point.x - drag_start_point.x;
	}
	if (drag_start_point.y > now_mouse_point.y) {
		drag_left_top.y = now_mouse_point.y;
		drag_size.y = drag_start_point.y - now_mouse_point.y;
	}
	else {
		drag_left_top.y = drag_start_point.y;
		drag_size.y = now_mouse_point.y - drag_start_point.y;
	}

	return Rect2(drag_left_top, drag_size);
}

void InputManager::_register_methods() {
	register_method("_init", &InputManager::_init);
	register_method("_ready", &InputManager::_ready);
	register_method("MouseClick", &InputManager::MouseClick);
	register_method("MouseRelease", &InputManager::MouseRelease);
	register_method("MouseHover", &InputManager::MouseHover);
	register_method("IsDragging", &InputManager::IsDragging);
	register_method("GetDragRect", &InputManager::GetDragRect);
}

void InputManager::_init() {
	is_dragging = false;

}

void InputManager::_ready() {
	InputManager();
}

void InputManager::LoadGameWorld() {
	Node* node = get_node(NodePath(SCENEPATH_GAMEMANAGER.c_str()));
	ERR_FAIL_COND(node == nullptr);
	GameManager* child = node->cast_to<GameManager>(node);
	ERR_FAIL_COND(child == nullptr);
	game_world = child->GetGameWorld();

}