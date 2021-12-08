extends Node

func _ready():
	$PauseScene.SetPanelPause(false)

func _input(event):
	if event.is_action_pressed("pause"):
		if $PauseScene.is_paused:
			restart_game()
		else:	
			pause_game()

func restart_game():
	$PauseScene.SetPanelPause(false)
	
func pause_game():
	$PauseScene.SetPanelPause(true)

	
	
