extends Node

var is_pressed

func _ready():
	is_pressed = false

func _on_GoTitle_pressed():
	print("go title clicked")
	if DetectButtonClicked():
		get_tree().change_scene("res://Scene/Title.tscn")


func _on_Exit_pressed():
	if DetectButtonClicked():
		print("exit clicked2")
		get_tree().quit()

func DetectButtonClicked():
	if is_pressed == false:
		is_pressed = true
		return true
	return false

func _on_Exit2_pressed():
	if DetectButtonClicked():
		print("close screen")
