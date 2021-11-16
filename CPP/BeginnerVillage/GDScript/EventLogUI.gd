extends PanelContainer


# Declare member variables here. Examples:
# var a = 2
# var b = "text"
var camera_manager

# Called when the node enters the scene tree for the first time.
func _ready():
	camera_manager = get_node("/root/Main/CameraManager")
	pass

func set_camera_position(position):
	camera_manager.SetCameraPosition(position)

func show_log(single_log):
	$HBoxContainer/VBoxContainer/content_log.text = single_log[0] + ": " + single_log[1]
	$HBoxContainer/VBoxContainer/content_date.text = String(single_log[2])+"년 "+String(single_log[3])+"월 "+\
			String(single_log[4])+"일 "+ String(single_log[5])+":"+\
			String(single_log[6])
			
	if $HBoxContainer/track_btn.get_signal_connection_list("pressed").size() != 0:
		$HBoxContainer/track_btn.disconnect("pressed", self, "set_camera_position")
	$HBoxContainer/track_btn.connect("pressed", self, "set_camera_position", [single_log[7]])
