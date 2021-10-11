extends Node2D

export var g_speed=3
export var g_velocity=Vector2()
export (Vector2)var g_camera_mouse_detect_size

var g_screen_size
var g_camera_mouse_detect_interval=20
var g_canmovecamera=true

var g_limit_left
var g_limit_right
var g_limit_up
var g_limit_down

func _ready():
	g_screen_size = get_viewport_rect().size	
	g_camera_mouse_detect_size = g_screen_size - Vector2(g_camera_mouse_detect_interval, g_camera_mouse_detect_interval)

func _process(_delta):
	if(g_canmovecamera):
		CameraMovewithKey()
		CameraMovewithMouse()	

func CameraMovewithKey():
	DetectKeyPress()
	if g_velocity.length()>0:
		g_velocity = g_velocity.normalized()*g_speed
		position+=g_velocity
		
func DetectKeyPress():
	g_velocity = Vector2(0,0)
	if Input.is_action_pressed("ui_left"):
		g_velocity.x-=1
	if Input.is_action_pressed("ui_right"):
		g_velocity.x+=1
	if Input.is_action_pressed("ui_up"):
		g_velocity.y-=1
	if Input.is_action_pressed("ui_down"):
		g_velocity.y+=1

func CameraMovewithMouse():
	var nowmousevector = get_viewport().get_mouse_position()

	var addPos = Vector2(0,0)
	if (nowmousevector.x < g_camera_mouse_detect_interval):
		addPos.x=-1
	elif (nowmousevector.x > g_camera_mouse_detect_size.x):
		addPos.x=1	
	if (nowmousevector.y < g_camera_mouse_detect_interval):
		addPos.y=-1
	elif (nowmousevector.y > g_camera_mouse_detect_size.y):
		addPos.y=1

	ChangePosition(position + addPos * g_speed)

func ChangePosition(newposition):
	position = DetectBoundary(newposition)
	
func DetectBoundary(nowposition):
	
	return nowposition
	
func ActiveCanMoveCamera():
	g_canmovecamera = true
	
func DeactiveCanMoveCamera():
	g_canmovecamera = false
	
