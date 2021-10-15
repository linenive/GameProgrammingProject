extends Node

export var available_popups : Array
export var used_popups : Array

var world_manager
var input_manager

var MAXIMUM_POPUP_COUNT = 10
var center_pos = Vector2(340, 100)
var instantiate_padding = Vector2(20, 20)

func _ready():
	world_manager = get_node("/root/Main/WorldManager")
	input_manager = get_node("/root/Main/InputManager")
	
	for popup in get_node("Popups").get_children():
		available_popups.append(popup)

func show_info_popup(object_id, type, title, content):
	if is_already_shown(object_id):
		return
	
	var popup
	var instantiate_pos : Vector2
	var popup_title = convert_popup_title(type)
	
	if used_popups.size() == 0:
		instantiate_pos = center_pos
	else:
		instantiate_pos = get_top_ui_pos() + instantiate_padding
	
	if available_popups.size() == 0:
		popup = used_popups.front()
		used_popups.pop_front()
		available_popups.push_back(popup)	
		
		popup.set_visible(false)
	
	popup = available_popups.pop_front()
	set_ui_top(popup)
	
	popup.init_popup(object_id, instantiate_pos, popup_title, title, content)

func close_info_popup(popup):
	var index = used_popups.find(popup)
	used_popups.remove(index)
	available_popups.push_back(popup)

func convert_popup_title(type):
	var info
	
	if type == "Character":
		info = "Character Info"
	elif type == "Tile":
		info = "Tile Info"
		
	return info

func get_top_ui_pos():
	var popup = used_popups.back()
	return popup.get_position()

func set_ui_top(popup):
	var index = used_popups.find(popup)
	used_popups.remove(index)
	
	used_popups.push_back(popup)
	get_child(0).move_child(popup, MAXIMUM_POPUP_COUNT-1)

func is_already_shown(object_id):
	for popup in used_popups:
		if popup.get_target_object_id() == object_id:
			print("already shown! : ", object_id)
			set_ui_top(popup)
			return true
	
	return false

func show_tile_info(mouse_pos):
	#var tile_id = world_manager.GetTileNumberByVector2(mouse_pos)
	#var tile_type = world_manager.GetTileType(tile_id)
	#print(tile_type)
	pass

