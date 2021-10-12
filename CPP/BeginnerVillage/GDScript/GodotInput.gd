extends Control
var input_manager
var tile_info_label
var world_manager

func _ready():
	input_manager = get_node("/root/Main/InputManager")
	world_manager = get_node("/root/Main/WorldManager")
	tile_info_label = get_node("/root/Main/JanTestGDScript/TileInfoTest")

func _input(event):
	if event is InputEventMouseButton:
		if event.button_index == BUTTON_LEFT: 
			if event.pressed:
				input_manager.MouseClick(event.position)
			else:
				input_manager.MouseRelease(event.position)
	if event is InputEventMouseMotion:
		input_manager.MouseHover(event.position)
		update_tile_info(event.position)

func update_tile_info(mouse_vector):
	if world_manager.CheckTileInVector2(mouse_vector):
		var tile_id = world_manager.GetTileIdByVector2(mouse_vector)
		tile_info_label.text \
			= String(tile_id)+": "+world_manager.GetTileName(tile_id) \
			+ ", scale: (" \
			+ String(world_manager.GetTileScale().x) + "," \
			+ String(world_manager.GetTileScale().y) + ")"

func _process(_delta):
	update()
		
func _draw():
	if input_manager.IsDragging():
		draw_drag_box(input_manager.GetDragRect())
	
func draw_drag_box(rect):
	draw_rect(rect, Color.white, false, 1.0, false)
	
