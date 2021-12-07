extends Node

func _ready():
	print("pause manager called")
	$PauseScene.SetPanelPause(false)

func _input(event):
	if event.is_action_pressed("pause"):
		if $PauseScene.is_paused:
			restart_game()
		else:	
			pause_game()

func restart_game():
	$PauseScene.SetPanelPause(false)
	#get_tree().paused = false
	
func pause_game():
	#get_tree().paused = true
	$PauseScene.SetPanelPause(true)

	
	
