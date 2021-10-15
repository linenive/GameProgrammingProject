extends WindowDialog

var uicontrol
var target_object_id

# Called when the node enters the scene tree for the first time.
func _ready():
	uicontrol = get_node("/root/Main/UIControl")

func init_popup(oid, position:Vector2, panel_title, title, content):
	target_object_id = oid
	
	set_position(position)	
	set_title(panel_title)
	$title.text = str(title)
	$content.text = str(content)
	
	var btn = get_close_button()
	btn.connect("pressed", self, "close_button_pressed")
	
	show()


func close_button_pressed():
	print("awefaef")
	target_object_id = 0
	uicontrol.close_info_popup(self)

func get_target_object_id():
	return target_object_id

func set_target_object_id(oid):
	target_object_id = oid

func _gui_input(event):
	if event is InputEventMouseButton and event.pressed and event.button_index == BUTTON_LEFT:
		uicontrol.set_ui_top(self)
