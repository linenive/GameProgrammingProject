extends Control

export(String) var current_text
var full_text
var effect_type = 'wave'
var wave_parameter=''
var shake_parameter=''

var default_head
var default_tail
var fade_head
var fade_tail
var fade_parameter
var hover_head
var hover_tail

var text_length = 10
var current_fade = 10
var left_time=10.0

func _ready():
	default_head='[center]'
	default_tail = '[/center]'
	fade_parameter = ' start='+str(current_fade)+' length=' + str(text_length)+' ]'
	fade_head = '[fade'+fade_parameter
	fade_tail = '[/fade]'
	hover_head = '['+effect_type + wave_parameter
	hover_tail = '[/'+effect_type+']'
	
	wave_parameter=' amp=20 freq=3]'
	shake_parameter=' rate=10 level=15]'
	
	$Text.bbcode_text =''
	
func _process(_delta):
	if left_time <= 0:
		queue_free()
	elif left_time<=0.5:
		$Text.rect_position += Vector2(1, -1)*_delta * 20
		left_time -= _delta
		current_fade -= _delta * text_length * 3
		FadeTextUpdate()
	else:
		left_time -= _delta
		
func TextSetting(new_text,new_effect_type,font_size, font_color, life_time):
	left_time = life_time
	effect_type = new_effect_type
	
	$Text.get_font("normal_font").size = font_size
	$Text.set("custom_colors/default_color",font_color)
	
	current_text = new_text
	text_length = len(new_text)
	set_effect_text()

func set_effect_text():
	if effect_type == "wave":
		hover_head = '['+effect_type + wave_parameter
	else:
		hover_head = '['+effect_type + shake_parameter
		
	hover_tail = '[/'+effect_type+']'
	current_fade = text_length
	FadeTextUpdate()

func FadeTextUpdate():
	fade_parameter = ' start='+str(current_fade)+' length=' + str(text_length)+' ]'
	fade_head = '[fade'+fade_parameter
	full_text = default_head +fade_head+ hover_head + current_text + hover_tail +fade_tail+ default_tail
	$Text.bbcode_text = full_text
