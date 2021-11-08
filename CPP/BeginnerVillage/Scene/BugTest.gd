extends Node2D
var input_manager

func _ready():
	input_manager = get_node("/root/Main/InputManager")
	
func _process(_delta):
	update()
	
func _draw():
	if input_manager.IsDragging():
		draw_drag_box(input_manager.GetDragRect())
	if input_manager.IsTileHighlighting():
		draw_highlight_box(input_manager.GetTileHighlight())
	
func draw_drag_box(rect):
	draw_rect(rect, Color.white, false, 1.0, false)

func draw_highlight_box(rect):
	draw_rect(rect, Color.darkgray, false, 1.0, false)
