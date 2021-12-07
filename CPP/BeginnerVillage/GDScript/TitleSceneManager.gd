extends Node2D

var is_pressed
func _ready():
	get_tree().paused=false
	is_pressed = false

func _on_NewGame_pressed():
	if DetectButtonClicked():
		get_tree().change_scene("res://Scene/MainGame.tscn")
	
func _on_Exit_pressed():
	if DetectButtonClicked():
		get_tree().quit()

func DetectButtonClicked():
	if is_pressed == false:
		is_pressed = true
		return true
	return false
