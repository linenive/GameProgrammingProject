extends PanelContainer

var camera_manager
var log_ui_control

var tween

var duration_fade_out = 5.0

var tempint = 0

# Called when the node enters the scene tree for the first time.
func _ready():
	camera_manager = get_node("/root/Main/CameraManager")
	log_ui_control = get_node("/root/Main/UIControl/LogUI")
	tween = $Tween;
	
	#set_visible(true)
	#tween_fade_out()
	#tween_fade_in()	

func set_camera_position(position):
	camera_manager.SetCameraPosition(position)

func show_new_log(single_log):
	$HBoxContainer/LogContainer/log_text.text = single_log[0] + ": " + single_log[1]
	$HBoxContainer/track_btn.connect("pressed", self, "set_camera_position", [single_log[7]])
	tween_fade_out()

func left_clicked():
	if !log_ui_control.is_event_log_panel_visible() and is_visible():
			log_ui_control.show_event_log()

func _gui_input(event):
	if event is InputEventMouseButton and event.pressed and event.button_index == BUTTON_LEFT:
		if !log_ui_control.is_event_log_panel_visible() and is_visible():
			log_ui_control.show_event_log()

func set_visible(value):
	if value == true:
		self.modulate.a = 1.0
	else:
		self.modulate.a = 0.0

func is_visible():
	if self.modulate.a == 0.0:
		return false
	else:
		return true

func tween_fade_out():
	tween.interpolate_property(self, "modulate", Color(1,1,1,1), Color(1,1,1,0), duration_fade_out, Tween.TRANS_EXPO, Tween.EASE_IN)
	tween.start()
