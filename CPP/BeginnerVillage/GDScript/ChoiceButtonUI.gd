extends Button

var current_target

signal ui_click_signal

func _ready():
	self.connect("ui_click_signal", get_node("/root/Main/GodotInput"), "ui_entered")

# array = [object_name, obejct_image ,signal]
func init_choice_button(array, target_node):
	set_visible(true)
	$object_name_label.text = array[0]
	
	set_image_strech_type_by_texture_size(array[1])
	$object_image.texture = array[1]	
	
	if self.get_signal_connection_list("pressed").size() != 0:
		self.disconnect("pressed", current_target, "get_result_from_choice_button")
	
	current_target = target_node
	self.connect("pressed", target_node, "get_result_from_choice_button", [array])

func set_visible(value):
	visible = value

func set_image_strech_type_by_texture_size(texture):
	if texture.get_size().x > self.rect_size.x or texture.get_size().y > self.rect_size.y:
		$object_image.stretch_mode = TextureRect.STRETCH_KEEP_ASPECT_CENTERED
		$object_image.rect_size = Vector2(75, 75)		
	else:
		$object_image.stretch_mode = TextureRect.STRETCH_KEEP_CENTERED
		#$object_image.rect_size = Vector2(75, 75)

func _gui_input(event):
	emit_signal("ui_click_signal")
