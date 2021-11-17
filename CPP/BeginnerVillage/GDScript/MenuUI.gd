extends CanvasLayer

var main_btns = []
var current_clicked_btn

var choice_button_control
var people_ui_control

func _ready():
	choice_button_control = get_node("/root/Main/UIControl/ChoiceButtonControl")
	people_ui_control = get_node("/root/Main/UIControl/PeopleUIControl")
	
	for child in self.get_child(0).get_children():
		main_btns.append(child)
		
	for btn in main_btns:
		btn.connect("pressed", self, "button_clicked", [btn])
	
	$HBoxContainer/ArchitectureBtn/Node/ConstructionBtn.connect("pressed", self, "construction_pressed")
	$HBoxContainer/PeopleBtn/Node/ManageBtn.connect("pressed", self, "manage_pressed")

func button_clicked(clicked_btn):
	for btn in main_btns:
		if clicked_btn == btn:
			if current_clicked_btn == btn:
				current_clicked_btn = null
				fold_menu(btn)
			else:
				current_clicked_btn = btn
				unfold_menu(btn)
		else:
			fold_menu(btn)
			pass

#menu_index = 0(people), 1(architecture), 2(research), 3(menu)
func fold_menu(btn):
	btn.get_child(0).visible = false

func fold_all_menu():
	current_clicked_btn = null
	for btn in main_btns:
		fold_menu(btn)

func unfold_menu(btn):
	btn.get_child(0).visible = true

func memu_clicked():
	print("menu")
	pass

func manage_pressed():
	print("manage_pressed")
	people_ui_control.open()
	fold_all_menu()
	pass

func construction_pressed():
	print("construction_pressed")
	choice_button_control.test()
	fold_all_menu()
	pass

func research_clicked():
	print("research")
	pass
