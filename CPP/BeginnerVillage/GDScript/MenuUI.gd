extends CanvasLayer

var main_btns = []
var sub_btns = []
var current_clicked_btn

var choice_button_control
var people_ui_control

signal ui_click_signal

func _ready():
	choice_button_control = get_node("/root/Main/UIControl/ChoiceButtonControl")
	people_ui_control = get_node("/root/Main/UIControl/PeopleUIControl")
	
	self.connect("ui_click_signal", get_node("/root/Main/GodotInput"), "ui_entered")
	
	for child in self.get_child(0).get_children():
		main_btns.append(child)
	
	for btn in main_btns:
		btn.connect("pressed", self, "button_clicked", [btn])
		btn.connect("gui_input", self, "emit_ui_click_signal")
		#print(btn.get_signal_connection_list("gui_input"))
	
	$HBoxContainer/ArchitectureBtn/Node/ConstructionBtn.connect("pressed", self, "construction_pressed")
	$HBoxContainer/PeopleBtn/Node/ManageBtn.connect("pressed", self, "manage_pressed")
	$HBoxContainer/ArchitectureBtn/Node/InstallBtn.connect("pressed", self, "furniture_pressed")
	
	self.connect("ui_click_signal", get_node("/root/Main/GodotInput"), "ui_entered")

func emit_ui_click_signal():
	print("poison")
	emit_signal("ui_click_signal")

func button_clicked(clicked_btn):
	for btn in main_btns:
		if clicked_btn == btn:
			if current_clicked_btn == btn:
				current_clicked_btn = null
				fold_menu(btn)
			else:
				#current_clicked_btn = btn #must be not joosuck someday! imsy for 2nd presentation
				unfold_menu(btn)
		else:
			fold_menu(btn)

#menu_index = 0(people), 1(architecture), 2(research), 3(menu)
func fold_menu(btn):
	btn.get_child(0).visible = false

func fold_all_menu():
	current_clicked_btn = null
	for btn in main_btns:
		fold_menu(btn)

func unfold_menu(btn):
	#imsy, will be modified with control_context of input_manager <- for 2nd presentation!
	if btn == main_btns[1] and choice_button_control.is_open():
		choice_button_control.close()
	else:
		current_clicked_btn = btn #must be in line 29 someday! it is imsy for 2nd presentation!
		btn.get_child(0).visible = true

func memu_clicked():
	print("menu")

func manage_pressed():
	print("manage_pressed")
	people_ui_control.open()
	fold_all_menu()

func construction_pressed():
	choice_button_control.test_construction()
	fold_all_menu()

func furniture_pressed():
	choice_button_control.test_furniture()
	fold_all_menu()

func research_clicked():
	pass
	
func _on_ArchitectureBtn_gui_input(event):
	emit_signal("ui_click_signal")

func _on_PeopleBtn_gui_input(event):
	emit_signal("ui_click_signal")

func _on_ConstructionBtn_gui_input(event):
	emit_signal("ui_click_signal")	

func _on_InstallBtn_gui_input(event):
	emit_signal("ui_click_signal")	
