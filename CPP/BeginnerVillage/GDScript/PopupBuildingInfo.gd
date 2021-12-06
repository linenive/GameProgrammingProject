extends Control

var ui_control
var character_pool : Node

export var test_character_sprite : Texture
var employee_info_button_scene

var building_name_label
var building_name_text_edit

var employee_button_hbox : HBoxContainer
var available_resident_list : VBoxContainer

# Called when the node enters the scene tree for the first time.
func _ready():
	ui_control = get_node("/root/Main/UIConrtol")
	character_pool = get_node("/root/Main/JanTestGDScript/TestTileCreater/Character")
	building_name_label = $Container/VBoxContainer/PanelContainer/HSplitContainer/building_name_label
	building_name_text_edit = $Container/VBoxContainer/PanelContainer/HSplitContainer/building_name_label/building_name_text_edit
	employee_button_hbox = $Container/VBoxContainer/VBoxContainer2/employee_info_panel/ScrollContainer/HBoxContainer
	available_resident_list = $available_resident_list_panel/available_resident_list
	
	employee_info_button_scene = load("res://Scene/EmployeeInfoButton.tscn")
	
	confirm_building_name()

func window_setting_building_info(node_building, info):
	get_parent().set_title("Building Info")
	
	#shop_name~
	
	#shop_customer count~
	
	init_employee_list(test_employee_list())
	init_available_resident_list(test_resident_list())

func edit_building_name():
	building_name_text_edit.visible = true	
	$Container/VBoxContainer/PanelContainer/HSplitContainer/building_name_edit_button.text = "confirm"

func confirm_building_name():
	building_name_text_edit.visible = false
	$Container/VBoxContainer/PanelContainer/HSplitContainer/building_name_edit_button.text = "edit"
	
	building_name_label.text = $Container/VBoxContainer/PanelContainer/HSplitContainer/building_name_label/building_name_text_edit.text
	#apply new building name needed!

func is_editing_building_name():
	return building_name_text_edit.visible

func get_character_node_by_character_id(character_id):
	for character in character_pool.get_children():
		if character.get_id() == character_id:
			return character
	
	return null

func on_employee_info_button_pressed(character_id):
	var character_node = get_character_node_by_character_id(character_id)
	
	if character_node != null:
		ui_control.show_info_popup(character_node, "Character")
	else:
		print("Character Node is null")

#employee_info = ["name", "character_id", image]
func init_employee_list(employee_list : Array):
	delete_all_employee_button()
	
	var employee_button_instance
	
	for employee_info in employee_list:
		employee_button_instance = employee_info_button_scene.instance()
		employee_button_instance.init_button(employee_info)
		employee_button_instance.connect("pressed", self, "on_employee_info_button_pressed", [employee_info["character_id"]])
		employee_button_hbox.add_child(employee_button_instance)

func init_available_resident_list(resident_list : Array):
	var resident_count = resident_list.size()
	var resident_button : Button
	
	for i in range(resident_count):
		resident_button = available_resident_list.get_child(i)
		resident_button.visible = true
		resident_button.text = resident_list[i]["name"]
		
		if resident_button.get_signal_connection_list("pressed").size() != 0:
			resident_button.disconnect("pressed", self, "recruit_resident_to_employee")
		
		resident_button.connect("pressed", self, "recruit_resident_to_employee", [resident_list[i]["character_id"]])
	
	for i in range(resident_count, available_resident_list.get_child_count()):
		available_resident_list.get_child(i).visible = false

func delete_all_employee_button():
	for button in employee_button_hbox.get_children():
		employee_button_hbox.remove_child(button)

func test_employee_list():
	var list = []
	
	var employee1 = {}
	employee1["name"] = "employee1"
	employee1["character_id"] = 123
	employee1["image"] = test_character_sprite
	
	var employee2 = {}
	employee2["name"] = "employee2"
	employee2["character_id"] = 456
	employee2["image"] = test_character_sprite
	
	list.append(employee1)
	list.append(employee2)
	
	return list

func test_resident_list():
	var list = []
	
	var resident1 = {}
	resident1["name"] = "resident1"
	resident1["character_id"] = 123
	
	var resident2 = {}
	resident2["name"] = "resident2"
	resident2["character_id"] = 456
	
	list.append(resident1)
	list.append(resident2)
	
	return list

func _on_building_name_edit_button_pressed():
	if is_editing_building_name():
		confirm_building_name()
	else:
		edit_building_name()

func _on_recruit_button_toggled(button_pressed):
	if button_pressed:
		$available_resident_list_panel.visible = true
	else:
		$available_resident_list_panel.visible = false
