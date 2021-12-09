extends Node

var progress_bar
var text_label
var world_manager
var instance_ui_manager
var character_node_parent

func _ready():
	progress_bar = load("res://Scene/Object/ProgressBar.tscn")
	text_label = load("res://Scene/ProgressBar.tscn")
	world_manager = get_node("/root/Main/WorldManager")
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
			progress_inst.rect_position = Vector2(-30,-50)
			progress_inst.add_to_group("progress_bar")	
	
func DeleteProgressBar(id):
	var children = character_node_parent.get_children()
	for child in children:
		if child.get_id() == id:
			for n in child.get_children():
				if n.name == "ProgressBar":
					child.remove_child(n)
					n.queue_free()

func CreateTextUI(id, pos):
	var text_inst = text_label.instance()
	#text_inst.Set 크기, 색, 
	
	var target_transform = world_manager.GetCharacterTransform(id)
	text_inst.transform = target_transform
	text_inst.position = pos
	text_inst.add_to_group("text_ui")
	
func DeleteTextUI(id):
	var target_transform = world_manager.GetCharacterTransform(id)
	if target_transform.has_node("TextUI"):
		target_transform.remove_child("TextUI")

func _on_InstanceUIManager_create_instance_ui(ID, max_var):
	CreateProgressBar(ID,max_var)
	
func _on_InstanceUIManager_delete_instance_ui(ID):
	DeleteProgressBar(ID)
