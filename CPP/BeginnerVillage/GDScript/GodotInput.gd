extends Control
var input_manager
var world_manager
var camera_manager
var tile_info_label
var uicontrol

var character_node_parent

func _ready():
	input_manager = get_node("/root/Main/InputManager")
	world_manager = get_node("/root/Main/WorldManager")
	camera_manager = get_node("/root/Main/CameraManager/CameraCPP")
	tile_info_label = get_node("/root/Main/UIControl/HUD/TileInfoTest")
	uicontrol = get_node("/root/Main/UIControl");
	
	character_node_parent = get_node("/root/Main/JanTestGDScript/TestTileCreater/Character")

func _input(event):
	input_process_for_ui(event)
	input_process_for_game_world(event)

func input_process_for_ui(event):
	# To-do: ui 입력 처리
	if event is InputEventMouseMotion:
		var mouse_pos = convert_position_by_camera(event.position)
		update_tile_info(mouse_pos)

func input_process_for_game_world(event):
	if event is InputEventMouseButton:
		var mouse_pos = convert_position_by_camera(event.position)
		if event.button_index == BUTTON_LEFT: 
			if event.pressed:
				left_mouse_button_pressed(mouse_pos)
			else:
				left_mouse_button_released(mouse_pos)
		elif event.button_index ==BUTTON_RIGHT:
			if event.pressed:
				right_mouse_button_pressed(event.position)
				uicontrol.MouseRightClickLabelUpdate(event.position)
				
	if event is InputEventMouseMotion:
		var mouse_pos = convert_position_by_camera(event.position)
		mouse_motion(mouse_pos)

func convert_position_by_camera(position):
	var camera_pos = camera_manager.GetCurrentCameraPosition()
	var camera_zoom = camera_manager.GetCurrentZoom()
	var camera_relative_pos = position - get_viewport_rect().size / 2
	var new_pos = camera_pos + camera_relative_pos * camera_zoom
	
	return new_pos

func convert_relative_position_by_camera(position):
	var ratio = Vector2(1024,600) - get_viewport_rect().size
	ratio = ratio/2
	return position + Vector2(ratio.x,0)
	
func left_mouse_button_pressed(position):
	input_manager.MouseClick(position)

func left_mouse_button_released(position):
	input_manager.MouseRelease(position)
	
func right_mouse_button_pressed(position):
	input_manager.MouseRightClick(position)
	
func mouse_motion(position):
	input_manager.MouseHover(position)
	#update_tile_info(position)
	#uicontrol.show_tile_info(position)

func update_tile_info(mouse_vector):
	var tile_coord = world_manager.GetTileCoordinate(mouse_vector)
	if tile_coord.x >= 0:
		tile_info_label.text \
			= String(tile_coord.x)+","+String(tile_coord.y)+": "\
			+ world_manager.GetSurfaceName(tile_coord) \
			+ ", scale: (" \
			+ String(world_manager.GetSurfaceScale().x) + "," \
			+ String(world_manager.GetSurfaceScale().y) + ")" \
			+ ", pass speed: "\
			+ String(world_manager.GetTilePassSpeed(tile_coord))
	else:
		tile_info_label.text = ""

func _on_InputManager_click_character(ID):
	var children = character_node_parent.get_children();
	for child in children:
		if child.get_id() == ID:
			uicontrol.show_info_popup(ID, "Character")
	#camera_manager.SetCameraSetting_Trace(character_path)

func _on_InputManager_click_structure(ID):
	print("Structrue click: "+ String(ID))
	uicontrol.show_info_popup(ID, "Structure")
	# show_info_popup
	pass

func _on_InputManager_click_building(ID):
	print("Building click: "+ String(ID))
	uicontrol.show_info_popup(ID, "Building")
	# show_info_popup

