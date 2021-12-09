extends Control

var ui_control
var world_manager
var static_unit_manager
var character_pool : Node

var target_building_id

export var test_character_sprite : Texture
var employee_info_button_scene
var resident_button_scene

var building_name_label : Label
var building_name_text_edit : TextEdit

var building_type_label : Label

var monthly_guest_count : Label
var total_guest_count : Label

var employee_info_panel : VBoxContainer

var employee_button_hbox : HBoxContainer
var available_resident_panel : PanelContainer
var available_resident_list : VBoxContainer

var no_available_resident_label : Label

# Called when the node enters the scene tree for the first time.
func _ready():
	ui_control = get_node("/root/Main/UIControl")
	static_unit_manager = get_node("/root/Main/StaticUnitManager")
	world_manager = get_node("/root/Main/WorldManager")
	character_pool = get_node("/root/Main/JanTestGDScript/TestTileCreater/Character")
	building_name_label = $Container/VBoxContainer/PanelContainer/HSplitContainer/building_name_label
	building_name_text_edit = $Container/VBoxContainer/PanelContainer/HSplitContainer/building_name_label/building_name_text_edit
	building_type_label = $Container/VBoxContainer/building_type_label
	monthly_guest_count = $Container/VBoxContainer/VBoxContainer/HBoxContainer/monthly_guest_count_value_label
	total_guest_count = $Container/VBoxContainer/VBoxContainer/HBoxContainer2/total_guest_count_value_label
	employee_info_panel = $Container/VBoxContainer/VBoxContainer2
	employee_button_hbox = $Container/VBoxContainer/VBoxContainer2/employee_info_panel/ScrollContainer/HBoxContainer
	available_resident_panel = $Container/VBoxContainer/VBoxContainer2/employee_info_panel/available_resident_list_panel
	available_resident_list = $Container/VBoxContainer/VBoxContainer2/employee_info_panel/available_resident_list_panel/available_resident_list
	no_available_resident_label = $Container/VBoxContainer/VBoxContainer2/employee_info_panel/available_resident_list_panel/available_resident_list/no_available_resident_label
	
	employee_info_button_scene = load("res://Scene/EmployeeInfoButton.tscn")
	resident_button_scene = load("res://Scene/ResidentButton.tscn")
	
	confirm_building_name()

func window_setting_building_info(id, info):
	get_parent().set_title("Building Info")
	
	target_building_id = id
	
	#shop name
	building_name_label.text = info[1]
	building_name_text_edit.text = building_name_label.text
	
	building_type_label.text = building_type_int_to_string(info[2])
	
	monthly_guest_count.text = str(info[3]) + "명"
	total_guest_count.text = str(info[4]) + "명"
	
	if info[2] == 1:
		employee_info_panel.visible = true
		init_employee_list(make_employee_list(info))
	else:
		employee_info_panel.visible = false		

func building_type_int_to_string(building_type_int):
	if building_type_int == 0:
		return "House"
	elif building_type_int == 1:
		return "WorkSpace"
	
	return null

func edit_building_name():
	building_name_text_edit.visible = true	
	building_name_text_edit.text = building_name_label.text
	$Container/VBoxContainer/PanelContainer/HSplitContainer/building_name_edit_button.text = "confirm"

func confirm_building_name():
	building_name_text_edit.visible = false
	$Container/VBoxContainer/PanelContainer/HSplitContainer/building_name_edit_button.text = "edit"
	building_name_label.text = building_name_text_edit.text
	#apply new building name needed!

func is_editing_building_name():
	return building_name_text_edit.visible

func get_character_node_by_character_id(character_id):
	var result = null
	for character in character_pool.get_children():
		if character.get_id() == character_id:
			result = character
	
	return result

func on_employee_info_button_pressed(character_id):
	var character_node = get_character_node_by_character_id(character_id)
	
	ui_control.show_info_popup(character_id, "Character")	

func delete_all_employee_button():
	for button in employee_button_hbox.get_children():
		employee_button_hbox.remove_child(button)

func make_employee_list(info):
	var result_list = []
	
	var max_employee_count = info[5]
	var temp_character_info
	var temp_dictionary
	
	for i in range(max_employee_count):
		if info[6+i] == -1:
			continue
		
		temp_dictionary = {}
		temp_character_info = ui_control.get_character_info(info[6+i])
		
		temp_dictionary["name"] = temp_character_info["full_name"]
		temp_dictionary["character_id"] = info[6+i]
		temp_dictionary["image"] = (get_character_node_by_character_id(info[6+i]) as Sprite).texture
		
		result_list.append(temp_dictionary)
	
	return result_list

#employee_info = ["name", "character_id", image]
func init_employee_list(employee_list : Array):
	delete_all_employee_button()
	
	var employee_button_instance
	
	for employee_info in employee_list:
		employee_button_instance = employee_info_button_scene.instance()
		employee_button_instance.init_button(employee_info)
		employee_button_instance.connect("pressed", self, "on_employee_info_button_pressed", [employee_info["character_id"]])
		employee_button_hbox.add_child(employee_button_instance)

func delete_all_resident_button():
	for button in available_resident_list.get_children():
		if button != no_available_resident_label:
			available_resident_list.remove_child(button)

func make_available_resident_list():
	return world_manager.GetRecruitableResidentArray()

func init_available_resident_list(resident_list : Array):
	delete_all_resident_button()
	
	if resident_list.size() == 0:
		no_available_resident_label.visible = true
	else:
		no_available_resident_label.visible = false
	
	var resident_button_instance
	
	for resident_info in resident_list:
		resident_button_instance = resident_button_scene.instance()
		resident_button_instance.text = resident_info["name"]
		resident_button_instance.connect("pressed", self, "recruit_resident_to_employee", [resident_info["character_id"]])
		available_resident_list.add_child(resident_button_instance)
	
	available_resident_panel.rect_size.y = 0

func recruit_resident_to_employee(character_id):
	static_unit_manager.AssignResidentToWorkSpace(character_id, target_building_id)
	$Container/VBoxContainer/VBoxContainer2/HSplitContainer/recruit_button.pressed = false
	_on_recruit_button_toggled(false)

func _on_building_name_edit_button_pressed():
	if is_editing_building_name():
		confirm_building_name()
	else:
		edit_building_name()

func _on_recruit_button_toggled(button_pressed):
	if button_pressed:
		init_available_resident_list(make_available_resident_list())
		available_resident_panel.visible = true
	else:
		available_resident_panel.visible = false
