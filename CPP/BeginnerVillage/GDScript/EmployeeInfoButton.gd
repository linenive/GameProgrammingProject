extends Button

var ui_control
var character_pool

var character_info

# Called when the node enters the scene tree for the first time.
func _ready():
	character_pool = get_node("/root/Main/JanTestGDScript/TestTileCreater/Character")
	ui_control = get_node("/root/Main/UIControl")

func init_button(employee_info):
	$employee_name_lable.text = str(employee_info["name"])
	$employee_texture.texture = employee_info["image"]

func _on_fire_button_pressed():
	pass # Replace with function body.

func _on_employee_info_ui_button_pressed():
	ui_control.show_info_popup(get_character_node_by_character_id(character_info["character_id"]), "Character")

func get_character_node_by_character_id(character_id):
	for character in character_pool.get_children():
		if character.get_id() == character_id:
			return character
	
	return null

func get_character_node():
	character_pool.get_child(0)
