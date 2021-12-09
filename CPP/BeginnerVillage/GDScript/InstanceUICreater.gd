extends Node

var progress_bar
var text_label
var world_manager
var godot_input

var instance_ui_manager
var character_node_parent

func _ready():
	progress_bar = load("res://Scene/Object/ProgressBar.tscn")
	text_label = load("res://Scene/TextEffect.tscn")
	world_manager = get_node("/root/Main/WorldManager")
	godot_input = get_node("/root/Main/GodotInput")
	
	instance_ui_manager = get_node("/root/Main/InstanceUIManager")
	character_node_parent = get_node("/root/Main/JanTestGDScript/TestTileCreater/Character")
	
func _process(delta):
	var progress_bars = get_tree().get_nodes_in_group("progress_bar")
	
	for pb in progress_bars:
		var id = pb.character_id
		var cur_var = instance_ui_manager.GetInstanceValueByID(id)
		pb._on_progress_updated(cur_var)
	
func CreateProgressBar(id, max_value):
	var progress_inst = progress_bar.instance()
	progress_inst.SetProgressBar(id, max_value,Color.gray)
	
	var children = character_node_parent.get_children()
	for child in children:
		if child.get_id() == id:
			child.add_child(progress_inst)
			progress_inst.rect_position = Vector2(-30,15)
			progress_inst.add_to_group("progress_bar")	
	
func DeleteProgressBar(id):
	var children = character_node_parent.get_children()
	for child in children:
		if child.get_id() == id:
			for n in child.get_children():
				if n.name == "ProgressBar":
					child.remove_child(n)
					n.queue_free()

func CreateTextUI(money_variation, pos):
	var text_inst = text_label.instance()
	add_child(text_inst)
	text_inst.rect_position = pos
	text_inst.add_to_group("text_effect")	

	var font_color
	var effect_type
	if money_variation>=0:
		font_color = Color.green
		effect_type = 'wave'
	else:
		font_color = Color.red
		effect_type = 'shake'
	
	text_inst.TextSetting(str(money_variation),effect_type, 20, font_color, 1.2)

func _on_InstanceUIManager_create_instance_ui(ID, max_var):
	CreateProgressBar(ID,max_var)
	
func _on_InstanceUIManager_delete_instance_ui(ID):
	DeleteProgressBar(ID)

func _on_UIManager_money_alert_effect(variation, position):
	CreateTextUI(variation, godot_input.convert_relative_position_by_camera(position))
