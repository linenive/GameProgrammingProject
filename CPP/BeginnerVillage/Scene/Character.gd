extends Sprite

var uicontrol
var camera_manager
var character_id : int
var character_path

# Called when the node enters the scene tree for the first time.
func _ready():
	uicontrol = get_node("/root/Main/UIControl")
	camera_manager = get_node("/root/Main/CameraManager")
	character_path = get_path()
	
func _input(event):
	if event is InputEventMouseButton and event.pressed and event.button_index == BUTTON_LEFT:
		if get_rect().has_point(to_local(event.position)):
			#uicontrol.show_info_popup(get_instance_id(), "Character", get_instance_id(), get_position())
			uicontrol.show_info_popup(self, "Character")
			#camera_manager.SetCameraSetting_Trace(character_path)

func init_character(character_id):
	self.character_id = character_id
