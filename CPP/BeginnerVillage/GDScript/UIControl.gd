extends CanvasLayer

export var available_popups : Array
export var used_popups : Array

var clicked_position_label : Label

var world_manager
var input_manager
var camera_manager

var MAXIMUM_POPUP_COUNT = 10
var screen_center_pos = Vector2(362, 100)
var next_ui_pos_offset = Vector2(20, 20)

func _ready():
	world_manager = get_node("/root/Main/WorldManager")
	input_manager = get_node("/root/Main/InputManager")
	camera_manager = get_node("/root/Main/CameraManager")
	
	clicked_position_label = $HUD/CharacterMove/ClickPositionLabel
	
	for popup in get_node("ObjectInfoUI").get_children():
		available_popups.append(popup)

func show_info_popup(node, type):
	var node_id = node.get_instance_id()
	
	if is_already_shown(node_id):
		set_ui_top(get_popup_by_node_id(node_id))
		return
	
	var instantiate_pos = get_instantiate_pos()
	var popup = get_available_popup()
	var info = get_object_info(node.get_id(), type)
	popup.show_popup(node, type, info, instantiate_pos)

func get_object_info(id, type):
	var info
	
	if type == "Character":
		info = get_character_info(id)
	elif type == "Building":
		info = get_building_info(id)
		
	return info

func get_character_info(id):
	var inventory_size : int
	var item_info_array : Array
	var character_info = {}
	
	character_info["first_name"] = world_manager.GetCharacterFirstName(id)
	character_info["last_name"] = world_manager.GetCharacterLastName(id)
	character_info["gender"] = world_manager.GetCharacterGender(id)
	inventory_size = world_manager.GetCharacterInventorySize(id)
			
	for j in inventory_size:
		item_info_array = world_manager.GetCharacterItem(id, j);
		character_info["item" + str(j+1)] = item_info_array
	return character_info

func get_building_info(id):
	pass

func get_available_popup():
	if available_popups.empty():
		set_oldest_used_popup_available()
	
	var popup = available_popups.pop_front()
	set_ui_top(popup)
	
	return popup

func set_oldest_used_popup_available():
	var popup = used_popups.front()
	used_popups.pop_front()
	available_popups.push_back(popup)

func get_instantiate_pos():
	if used_popups.empty():
		return screen_center_pos
	else:
		return get_top_ui_pos() + next_ui_pos_offset

func close_info_popup(popup):
	used_popups.erase(popup)
	available_popups.push_back(popup)

func get_top_ui_pos():
	var popup = used_popups.back()
	return popup.get_position()

func set_ui_top(popup):
	used_popups.erase(popup)
	used_popups.push_back(popup)
	popup.get_parent().move_child(popup, 9)

func get_popup_by_node_id(node_id):
	for popup in used_popups:
		if popup.get_target_node_id() == node_id:
			return popup
	return null

func is_already_shown(object_id):
	if get_popup_by_node_id(object_id) != null:
		return true
	
	return false

func is_used_popup(popup_):
	for popup in used_popups:
		if popup == popup_:
			return true
	
	return false

func MouseRightClickLabelUpdate(new_click_position):
	clicked_position_label.text = str(new_click_position)

func popup_ui_track_btn_pressed(character_path):
	$HUD/StopTracingBtn.visible = true
	camera_manager.SetCameraSetting_Trace(character_path)

func _on_CharacterMove_pressed():
	var game_manager = get_node("/root/Main").AIClickUpdate(input_manager.GetNowMouseRightClickPoint())

func _on_StopTracingBtn_pressed():
	$HUD/StopTracingBtn.visible = false
	camera_manager.SetCameraSetting_Default()

"""
func _on_Main_delete_character(ID):
	var popup_target_node
	
	for popup in used_popups:
		if popup..get_target_object_id() == ID:
			popup_target_node = popup.get_target_node()
			popup.hide()
			close_info_popup(popup)
			
			if camera_manager.GetCurrentCameraStateInString() == "TRACE" and camera_manager.IsTargetNode(popup_target_node):
				_on_StopTracingBtn_pressed()
			break
"""
