extends Node

var is_pause
func _ready():
	print("pause manager called")
	is_pause = false
	set_pause_scene_visible(false)

func _process(delta):
	if Input.is_action_just_pressed("pause"):
		if is_pause:
			restart_game()
		else:	
			pause_game()

func restart_game():
	set_pause_scene_visible(false)
	is_pause=false
	
func pause_game():
	is_pause = true
	set_pause_scene_visible(true)
	
func set_pause_scene_visible(active):
	$PauseScene/TitleCanvas/TitlePanel.visible = active
	$PauseScene/ButtonCanvas/Control.visible = active
	
	
