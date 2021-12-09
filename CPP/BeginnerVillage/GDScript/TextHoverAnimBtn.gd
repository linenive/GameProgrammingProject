extends Button

export(String) var text_btn 

var current_text

var default_head
var default_tail
var hover_head
var hover_tail

# Called when the node enters the scene tree for the first time.
func _ready():
	default_head='[center]'
	default_tail = '[/center]'
	hover_head = '[wave amp=20 freq=10]'
	hover_tail = '[/wave]'
	
	set_default_text()

func set_default_text():
	current_text = default_head + text_btn + default_tail
	$Text.bbcode_text = current_text

func set_hover_text():
	current_text = default_head + hover_head + text_btn + hover_tail + default_tail
	$Text.bbcode_text = current_text	

func _on_Text_mouse_entered():
	set_hover_text()

func _on_Text_mouse_exited():
	set_default_text()
