extends Control

onready var progress_bar = $Progress
#onready var update_tween = $UpdateTween
onready var styleBox = $Progress.get("custom_styles/fg")

var character_id = -1
	
func SetProgressBar(id, max_value, color):
	character_id = id
	$Progress.max_value = max_value
	$Progress.value = max_value
	$Progress.tint_progress = color
	print("set progress "+str(character_id))

func _on_progress_updated(new_value):
	$Progress.value = new_value
	

	
