extends Button

var current_target

func _ready():
	pass # Replace with function body.

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
	print(texture.get_size().x)
	print(texture.get_size().y)
	
	print(self.rect_size.x)
	print(self.rect_size.y)
	
	if texture.get_size().x > self.rect_size.x or texture.get_size().y > self.rect_size.y:
		print("la dolce vita")
		$object_image.stretch_mode = TextureRect.STRETCH_KEEP_ASPECT_CENTERED
		$object_image.rect_size = Vector2(75, 75)		
	else:
		print("senorita")
		$object_image.stretch_mode = TextureRect.STRETCH_KEEP_CENTERED
		#$object_image.rect_size = Vector2(75, 75)
