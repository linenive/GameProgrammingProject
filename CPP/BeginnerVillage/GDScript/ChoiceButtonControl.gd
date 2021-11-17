
extends CanvasLayer

export var imamge1 : Texture
export var imamge2 : Texture

var choice_button_ui = []
var choice_button_count = 16;

var choice_result

var input_manager

# Called when the node enters the scene tree for the first time.
func _ready():
	input_manager = get_node("/root/Main/InputManager")
	var hbox_containers = [$VBoxContainer/HBoxContainer, $VBoxContainer/HBoxContainer2]
	
	for hbox_container in hbox_containers:
		for child in hbox_container.get_children():
			choice_button_ui.append(child)
	
	close()

func test():
	var test_array = [["building1", imamge1, 0], ["building2", imamge2, 1]]
	show_choice_buttons(test_array)

# display choice buttons according to array
# array = [[object_name, object_image, target_node, signal], ... ]
func show_choice_buttons(array):
	open()
	
	var array_size = array.size()
	
	#array.size() must be under 16 -> will be modified in future
	for i in range(array_size):
		choice_button_ui[i].init_choice_button(array[i], self)
	
	if array_size < choice_button_count:
		for i in range(array_size, choice_button_count):
			choice_button_ui[i].set_visible(false)

func get_result_from_choice_button(choice_result):
	self.choice_result = choice_result
	print(self.choice_result)
	input_manager.ChangeStateToBuild(choice_result[2])

func close():
	#input_manager.ChangeStateToNormal() #imsy for 2nd presentation
	get_child(0).visible = false

func open():
	get_child(0).visible = true

func is_open():
	return get_child(0).visible
