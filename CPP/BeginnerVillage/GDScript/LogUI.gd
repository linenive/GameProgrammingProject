extends PanelContainer

var event_log_panel
var tween

var time_fade_in = 0.5
var time_fade_out = 1.0

# Called when the node enters the scene tree for the first time.
func _ready():
	event_log_panel = get_node("/root/Main/HUD/LogUI/EventLogPanel")
	tween = $Tween;
	
	#tween_fade_out()
	#tween_fade_in()	

func _gui_input(event):
	if event is InputEventMouseButton and event.pressed and event.button_index == BUTTON_LEFT:
		if event_log_panel.visible == false:
			print("Open Log Panel")
			event_log_panel.show()

func tween_fade_out():
	tween.interpolate_property(self, "modulate:a", modulate.a, 0.0, 1.0, Tween.TRANS_LINEAR, time_fade_out)
	tween.start()

func tween_fade_in():
	tween.interpolate_property(self, "modulate:a", modulate.a, 1.0, 0.0, Tween.TRANS_LINEAR, time_fade_in)
	tween.start()
