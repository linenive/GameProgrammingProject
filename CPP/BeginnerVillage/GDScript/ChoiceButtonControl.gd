
extends CanvasLayer

var choice_button_ui = []
var choice_button_count = 16;

var choice_state
var choice_result

var input_manager
var choice_button_data_maker

# Called when the node enters the scene tree for the first time.
func _ready():
	input_manager = get_node("/root/Main/InputManager")
	choice_button_data_maker = get_node("/root/Main/UIControl/ChoiceButtonControl/ChoiceButtonDataMaker")
	var hbox_containers = [$VBoxContainer/HBoxContainer, $VBoxContainer/HBoxContainer2]
	
	for hbox_container in hbox_containers:
		for child in hbox_container.get_children():
			choice_button_ui.append(child)
	
	close()

# display choice buttons according to array
# array = [[object_name, object_image, target_node, signal], ... ]
func show_choice_buttons(choice_state, array):
	open()
	
	self.choice_state = choice_state
	
	var array_size = array.size()
	
	#array.size() must be under 16 -> will be modified in future
	for i in range(array_size):
		choice_button_ui[i].init_choice_button(array[i], self)
	
	if array_size < choice_button_count:
		for i in range(array_size, choice_button_count):
			choice_button_ui[i].set_visible(false)

func get_result_from_choice_button(choice_result):
	self.choice_result = choice_result
	
	if choice_state == "Construction":
		input_manager.ChangeStateToBuild(choice_result[2])
	elif choice_state == "Install":
		input_manager.ChangeStateToInstall(choice_result[2])
		pass

func close():
	#input_manager.ChangeStateToNormal() #imsy for 2nd presentation
	get_child(0).visible = false

func open():
	get_child(0).visible = true

func is_open():
	return get_child(0).visible

#button test
func test_construction():
	show_choice_buttons("Construction", choice_button_data_maker.get_building_data_array())

func test_furniture():
	show_choice_buttons("Install", choice_button_data_maker.get_furniture_data_array())
