extends WindowDialog

var uicontrol
var target_object_id

# Called when the node enters the scene tree for the first time.
func _ready():
	uicontrol = get_node("/root/Main/UIControl")

func show_popup(oid, position:Vector2, window_title, info_title, info_content):
	target_object_id = oid
	
	set_position(position)	
	set_title(window_title)
	$title.text = str(info_title)
	$content.text = str(info_content)
	
	var btn = get_close_button()
	btn.connect("pressed", self, "close_button_pressed")
	
	show()

func init_popup():
	target_object_id = 0

func close_button_pressed():
	init_popup()
	uicontrol.close_info_popup(self)

func get_target_object_id():
	return target_object_id

func set_target_object_id(oid):
	target_object_id = oid

func _gui_input(event):
	if event is InputEventMouseButton and event.pressed and event.button_index == BUTTON_LEFT:
		uicontrol.set_ui_top(self)
