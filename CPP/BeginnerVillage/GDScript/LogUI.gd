extends PanelContainer

var camera_manager
var log_ui_control

var tween

var duration_fade_out = 5.0

var tempint = 0

signal ui_click_signal

# Called when the node enters the scene tree for the first time.
func _ready():
	camera_manager = get_node("/root/Main/CameraManager")
	log_ui_control = get_node("/root/Main/UIControl/LogUIControl")
	tween = $Tween;
	
	self.connect("ui_click_signal", get_node("/root/Main/GodotInput"), "ui_entered")

func set_camera_position(position):
	if camera_manager.GetCurrentCameraStateInString() == "TRACE":
		camera_manager.SetCameraSetting_Default()
	
	camera_manager.SetCameraPosition(position)

func show_new_log(single_log):
	$HBoxContainer/LogContainer/log_text.text = single_log[0] + ": " + single_log[1]
	
	if $HBoxContainer/track_btn.get_signal_connection_list("pressed").size() != 0:
		$HBoxContainer/track_btn.disconnect("pressed", self, "set_camera_position")
		
	$HBoxContainer/track_btn.connect("pressed", self, "set_camera_position", [single_log[7]])
	tween_fade_out()

func left_clicked():
	if !log_ui_control.is_event_log_panel_visible() and is_visible():
			log_ui_control.show_event_log()

func _gui_input(event):
	if event is InputEventMouseButton and event.pressed and event.button_index == BUTTON_LEFT:
		if !log_ui_control.is_event_log_panel_visible() and is_visible():
			log_ui_control.show_event_log()
	
	emit_signal("ui_click_signal")

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
