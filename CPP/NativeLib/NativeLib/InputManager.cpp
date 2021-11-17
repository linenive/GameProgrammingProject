#include "InputManager.h"
#include "GodotScenePath.h"

void InputManager::MouseClick(Vector2 position) {
	control_context->MouseClick(position);
}

void InputManager::MouseRelease(Vector2 position) {
	control_context->MouseRelease(position);
}

void InputManager::MouseHover(Vector2 position) {
	control_context->MouseHover(position);
	now_mouse_point = position;
}

void InputManager::MouseRightClick(Vector2 position) {
	now_mouse_right_click_point = position;
}

bool InputManager::IsDragging() {
	return control_context->GetInputStatus().is_dragging;
}

bool InputManager::IsBuilding() {
	return control_context->GetInputStatus().is_building;
}


void InputManager::ChangeStateToBuild(int building_type) {
	control_context->SwitchToBulidState(building_type);
}

Rect2 InputManager::GetDragRect() {
	Vector2 drag_left_top = Vector2();
	Vector2 drag_size = Vector2();
	Vector2 drag_start_point = control_context->GetInputStatus().drag_start_point;

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

bool InputManager::IsTileHighlighting() {
	return control_context->GetInputStatus().is_area_highlighted;
}

Rect2 InputManager::GetTileHighlight() {
	return control_context->GetInputStatus().highlighted_area;
}

void InputManager::_register_methods() {
	register_method("_init", &InputManager::_init);
	register_method("_ready", &InputManager::_ready);
	register_method("MouseClick", &InputManager::MouseClick);
	register_method("MouseRelease", &InputManager::MouseRelease);
	register_method("MouseHover", &InputManager::MouseHover);
	register_method("IsDragging", &InputManager::IsDragging);
	register_method("IsBuilding", &InputManager::IsBuilding);
	register_method("GetDragRect", &InputManager::GetDragRect);
	
	register_method("ChangeStateToBuild", &InputManager::ChangeStateToBuild);
	register_method("IsTileHighlighting", &InputManager::IsTileHighlighting);
	register_method("GetTileHighlight", &InputManager::GetTileHighlight);
	register_method("MouseRightClick", &InputManager::MouseRightClick);
	register_method("GetNowMouseRightClickPoint", &InputManager::GetNowMouseRightClickPoint);

}

void InputManager::_init() {

}

void InputManager::_ready() {
	LoadGameWorld();
	// control_context = new ControlContext(game_world, static_unit_service);
	static_unit_service.SetGameWorld((GameWorldForStaticUnit*)game_world);
	control_context = new ControlContext(game_world, &static_unit_service);
	printf("ready end\n");
}

void InputManager::LoadGameWorld() {
	Node* node = get_node(NodePath(SCENEPATH_GAMEMANAGER.c_str()));
	ERR_FAIL_COND(node == nullptr);
	GameManager* child = node->cast_to<GameManager>(node);
	ERR_FAIL_COND(child == nullptr);
	game_world = child->GetGameWorld();
}