extends Sprite

var uicontrol
var godot_input
var character_id : int
var character_path

# Called when the node enters the scene tree for the first time.
func _ready():
	uicontrol = get_node("/root/Main/UIControl")
	godot_input = get_node("/root/Main/GodotInput")

func _input(event):
	if event is InputEventMouseButton and event.pressed and event.button_index == BUTTON_LEFT:
		if get_rect().has_point(to_local(godot_input.convert_position_by_camera(event.position))):
			uicontrol.show_info_popup(self, "Character")
			#camera_manager.SetCameraSetting_Trace(character_path)

func init_character(character_id):
	self.character_id = character_id
