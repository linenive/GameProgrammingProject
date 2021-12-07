extends Node2D

var is_pressed
func _ready():
	is_pressed = false

#new game
func _on_NewGame_pressed():
	if DetectButtonClicked():
		print("new game clicked")
		get_tree().change_scene("res://Scene/MainGame.tscn")
	
#exit 
func _on_Exit_pressed():
	if DetectButtonClicked():
		print("exit clicked")
		get_tree().quit()

func DetectButtonClicked():
	if is_pressed == false:
		is_pressed = true
		return true
	return false
