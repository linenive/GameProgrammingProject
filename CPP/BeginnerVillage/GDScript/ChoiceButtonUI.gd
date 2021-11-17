extends Button

var current_target

func _ready():
	pass # Replace with function body.

# array = [object_name, obejct_image ,signal]
func init_choice_button(array, target_node):
	set_visible(true)
	$object_name_label.text = array[0]
	$object_image.texture = array[1]
	
	if self.get_signal_connection_list("pressed").size() != 0:
		self.disconnect("pressed", current_target, "get_result_from_choice_button")
	
	current_target = target_node
	self.connect("pressed", target_node, "get_result_from_choice_button", [array])

func set_visible(value):
	visible = value
