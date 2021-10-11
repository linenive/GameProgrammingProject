extends Button


func _on_Button_button_down():
	print("down")
	get_node("/root/Main/UIManager").ShowPopupUI()	


func _on_Button_button_up():
	print("up")
	get_node("/root/Main/UIManager").ShowPopupUI()
