extends Control
var input_manager

func _ready():
	input_manager = get_node("/root/Main/InputManager")

func _input(event):
	if event is InputEventMouseButton:
		if event.button_index == BUTTON_LEFT: 
			if event.pressed:
				input_manager.MouseClick(event.position)
			else:
				input_manager.MouseRelease(event.position)
	if event is InputEventMouseMotion:
		input_manager.MouseHover(event.position)

func _process(delta):
	update()
				
func _draw():
	if input_manager.IsDragging():
		draw_drag_box(input_manager.GetDragRect())
	
func draw_drag_box(rect):
	draw_rect(rect, Color.white, false, 1.0, false)
	
