extends Control

var inventory_panel
var inventory_ui

var target_structure_id
var choice_button_data_maker

# Called when the node enters the scene tree for the first time.
func _ready():
	inventory_panel = $Container/VBoxContainer/VBoxContainer2
	inventory_ui = $Container/VBoxContainer/VBoxContainer2/PanelContainer/inventory_ui
	choice_button_data_maker = get_node("/root/Main/UIControl/ChoiceButtonControl/ChoiceButtonDataMaker")

func window_setting_structure_info(id, info):
	get_parent().set_title("Structure Info")
	
	target_structure_id = id
	
	$Container/VBoxContainer/structure_name_label.text = structure_type_int_to_string(info[2])
	
	#inventory
	if has_inventory(info):
		inventory_panel.visible = true
		inventory_ui.init_inventory(4, info)
	else:
		inventory_panel.visible = false

func structure_type_int_to_string(structure_type_int):
	if structure_type_int < 8:
		return choice_button_data_maker.furniture_name_arrray[structure_type_int]
	elif structure_type_int == 8:
		return "나무"
	
	return null

func has_inventory(info):
	if info[3] == 0:
		return false
	else:
		return true

func update_info(info):
	if has_inventory(info):
		inventory_ui.init_inventory(4, info)
