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
	return control_context->GetInputStatus()->is_dragging;
}

bool InputManager::IsBuilding() {
	return control_context->GetInputStatus()->is_building;
}

Array InputManager::GetBuildingBluePrint() {
	Array block_array = Array();
	Building* scheduled_building = control_context->GetInputStatus()->scheduled_building;
	Vector2 building_position = scheduled_building->ocupation_area.position;
	for (Block* b : scheduled_building->blocks) {
		Array arr = Array();
		arr.append((int)b->block_type);
		Vector2 new_position = Vector2(b->GetPhysics().GetPosition());
		new_position = new_position + building_position;
		arr.append(new_position);
		block_array.push_back(arr);
	}

	return block_array;
}


void InputManager::ChangeStateToBuild(int building_type) {
	control_context->SwitchToBulidState(building_type);
	EmitStateSignal();
}

Rect2 InputManager::GetDragRect() {
	Vector2 drag_left_top = Vector2();
	Vector2 drag_size = Vector2();
	Vector2 drag_start_point = control_context->GetInputStatus()->drag_start_point;

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
	return control_context->GetInputStatus()->is_area_highlighted;
}

Rect2 InputManager::GetTileHighlight() {
	return control_context->GetInputStatus()->highlighted_area;
}

void InputManager::EmitStateSignal(){
	emit_signal(String("change_to_building_state"));
}

void InputManager::EmitBuildSignal(int building_id) {
	emit_signal(String("build_building"), building_id);
}

void InputManager::_register_methods() {
	register_method("_init", &InputManager::_init);
	register_method("_ready", &InputManager::_ready);
	register_method("_process", &InputManager::_process);
	register_method("MouseClick", &InputManager::MouseClick);
	register_method("MouseRelease", &InputManager::MouseRelease);
	register_method("MouseHover", &InputManager::MouseHover);
	register_method("IsDragging", &InputManager::IsDragging);
	register_method("GetDragRect", &InputManager::GetDragRect);
	register_method("IsBuilding", &InputManager::IsBuilding);
	register_method("GetBuildingBluePrint", &InputManager::GetBuildingBluePrint);
	
	register_method("ChangeStateToBuild", &InputManager::ChangeStateToBuild);
	register_method("IsTileHighlighting", &InputManager::IsTileHighlighting);
	register_method("GetTileHighlight", &InputManager::GetTileHighlight);
	register_method("MouseRightClick", &InputManager::MouseRightClick);
	register_method("GetNowMouseRightClickPoint", &InputManager::GetNowMouseRightClickPoint);
	register_signal<InputManager>(String("change_to_building_state"), Dictionary());
	register_signal<InputManager>(String("build_building"), "ID", GODOT_VARIANT_TYPE_INT);
}

void InputManager::_init() {

}

void InputManager::_ready() {
	LoadGameWorld();
	static_unit_service.SetGameWorld((GameWorld*)game_world);
	control_context = new ControlContext(game_world, &static_unit_service);
}

void InputManager::_process(float delta) {
	FetchInputQueue();
}

void InputManager::LoadGameWorld() {
	Node* node = get_node(NodePath(SCENEPATH_GAMEMANAGER.c_str()));
	ERR_FAIL_COND(node == nullptr);
	GameManager* child = node->cast_to<GameManager>(node);
	ERR_FAIL_COND(child == nullptr);
	game_world = child->GetGameWorld();
}

void InputManager::FetchInputQueue() {
	// 현재 새로 건설된 건물만 있지만, 이후 다른 것들에 대해서도 추가할 예정임
	queue<int>* new_building_ids = &(control_context->GetInputStatus()->new_building_ids);
	while (!new_building_ids->empty()) {
		int new_id = new_building_ids->front();
		new_building_ids->pop();
		EmitBuildSignal(new_id);
	}
	
}