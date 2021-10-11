extends Area2D

export var g_distance=200
export var g_target=0
var g_direction=1

signal traceStart(path,name)

# 임의로 자동으로 움직이는 것 구현. 
func _ready():
	g_direction=1
	g_target=position.x+g_distance*g_direction
	print(get_node("/root/CameraTest/UIManager").get_child_count())
	
func _process(_delta):
	if(position.x==g_target):
		g_direction=g_direction*-1
		g_target = position.x+g_direction*g_distance
	else:
		position.x+=g_direction

# 실제로 사용되는 부분 - 클릭됐을시 자신의 path를 넘겨주는 함수
func _input(event):
	if event is InputEventMouseButton:
		if event.button_index==BUTTON_LEFT and event.is_pressed():
			print(name)
			emit_signal("traceStart",get_path(),name)
		#get_node("/root/UIManager").StartNPCTrace(get_path(),name)
