extends Control

var inventory_panel
var inventory_ui

var target_structure_id

# Called when the node enters the scene tree for the first time.
func _ready():
	inventory_panel = $Container/VBoxContainer/VBoxContainer2
	inventory_ui = $Container/VBoxContainer/VBoxContainer2/PanelContainer/inventory_ui

func window_setting_structure_info(id, info):
	get_parent().set_title("Structure Info")
	
	target_structure_id = id
	
	$Container/VBoxContainer/structure_name_label.text = info[1]
	#$Container/VBoxContainer/structure_type_label.text = structure_type_int_to_string(info[2])
	
	#inventory
	if has_inventory(info):
		inventory_panel.visible = true
		inventory_ui.init_inventory(4, info)
	else:
		inventory_panel.visible = false

func structure_type_int_to_string(structure_type_int):
	if structure_type_int == 0:
		return "Single bed"
	elif structure_type_int == 1:
		return "Double bed"
	elif structure_type_int == 2:
		return "Box"
	elif structure_type_int == 3:
		return "Cooking table"
	elif structure_type_int == 4:
		return "Pot"
	elif structure_type_int == 5:
		return "Table"
	elif structure_type_int == 6:
		return "Counter"
	elif structure_type_int == 7:
		return "Chair"
	elif structure_type_int == 8:
		return "Tree"
	
	return null

func has_inventory(info):
	if info[3] == 0:
		return false
	else:
		return true

func update_info(info):
	if has_inventory(info):
		inventory_ui.init_inventory(4, info)
