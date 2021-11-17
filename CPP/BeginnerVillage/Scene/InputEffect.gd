extends Node2D
var input_manager
var block_scene
var texture_db

func _ready():
	input_manager = get_node("/root/Main/InputManager")
	texture_db = get_node("/root/Main/TextureDB")
	block_scene = load("res://Scene/Block.tscn")

func _process(_delta):
	update()
	if input_manager.IsBuilding():
		draw_building_blueprint()
	
func _draw():
	if input_manager.IsDragging():
		draw_drag_box(input_manager.GetDragRect())
	if input_manager.IsTileHighlighting():
		draw_highlight_box(input_manager.GetTileHighlight())

func draw_drag_box(rect):
	draw_rect(rect, Color.white, false, 1.0, false)

func draw_highlight_box(rect):
	draw_rect(rect, Color.darkgray, false, 1.0, false)

func draw_building_blueprint():
	var blocks = input_manager.GetBuildingBluePrint()
	var i = 0
	for c in $Blueprint.get_children():
		c.transform.origin = blocks[i][1]
		i = i + 1

func create_building_blueprint():
	var blocks = input_manager.GetBuildingBluePrint()
	for b in blocks:
		var block_node = block_scene.instance()
		block_node.transform.origin = b[1]
		block_node.texture = texture_db.block_texture[b[0]]
		block_node.modulate.a = 0.5
		$Blueprint.add_child(block_node)

func delete_building_blueprint():
	for n in $Blueprint.get_children():
		$Blueprint.remove_child(n)
		n.queue_free()

func _on_InputManager_change_to_building_state():
	create_building_blueprint()
	
func _on_InputManager_change_to_normal_state():
	delete_building_blueprint()
