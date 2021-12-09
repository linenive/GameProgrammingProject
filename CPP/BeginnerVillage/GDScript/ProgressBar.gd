extends Control

onready var progress_bar = $Progress
onready var update_tween = $UpdateTween

export (Color) var progress_bar_color = Color.gray
var character_id
	
func SetProgressBar(id, max_value):
	character_id = id
	$Progress.max_value = max_value
	$Progress.value = max_value

func _on_progress_updated(new_value):
	$UpdateTween.interpolate_property($Progress,"value", $Progress.value,
	0.4,Tween.TRANS_SINE, Tween.EASE_IN_OUT)
	$UpdateTween.start()

	
