extends Node2D

export var g_speed=3
export var g_velocity=Vector2()

var g_screen_size
var g_unmoving_interval=20
export (Vector2)var g_unmoving_size
var g_camera_mouse_detect_interval=20
var g_camera_mouse_detect_size
var g_canmovecamera=true

var g_screen_boundary_lefttop : Vector2 # 현재 필드의 바운더리
var g_screen_boundary_rightbottom : Vector2 # 현재 필드의 바운더리
var now_zoom_scale

func _ready():
	g_screen_size = get_viewport_rect().size	
	g_unmoving_size = g_screen_size-Vector2(g_unmoving_interval,g_unmoving_interval)

	g_camera_mouse_detect_size = g_screen_size - Vector2(g_camera_mouse_detect_interval, g_camera_mouse_detect_interval)
	position = g_screen_size/2
	
func _process(_delta):
	if(g_canmovecamera):
		CameraMovewithKey()
		CameraMovewithMouse()	

func SetMoveKeyBoundary(lefttop, rightbottom):
	g_screen_boundary_lefttop = lefttop
	g_screen_boundary_rightbottom = rightbottom

func SetSpeed(speed):
	g_speed=speed
func SetZoomScale(zoom):
	now_zoom_scale = zoom
	
func CameraMovewithKey():
	DetectKeyPress()
	if g_velocity.length()>0:
		g_velocity = g_velocity.normalized()*g_speed
		#position+=g_velocity
		DetectBoundary(position+g_velocity)
		
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
	if (nowmousevector.x<g_unmoving_interval):
		addPos.x=-1
	elif (nowmousevector.x>g_unmoving_size.x):
		addPos.x=1	
	if (nowmousevector.y<g_unmoving_interval):
		addPos.y=-1
	elif (nowmousevector.y>g_unmoving_size.y):
		addPos.y=1

	position += addPos*g_speed

	var add_pos = Vector2(0,0)
	if (nowmousevector.x < g_camera_mouse_detect_interval):
		add_pos.x=-1
	elif (nowmousevector.x > g_camera_mouse_detect_size.x):
		add_pos.x=1	
	if (nowmousevector.y < g_camera_mouse_detect_interval):
		add_pos.y=-1
	elif (nowmousevector.y > g_camera_mouse_detect_size.y):
		add_pos.y=1
	
	DetectBoundary(position + add_pos *g_speed)
	#position +=addPos * g_speed
	
func DetectBoundary(new_position):
	var half_viewport = g_screen_size * now_zoom_scale / 2
	var lefttop = new_position - half_viewport
	var rightbottom = new_position + half_viewport

	$CanvasLayer/Label.text = str(lefttop)
	$CanvasLayer/Label2.text = str(rightbottom)
	
	position = new_position
	

func ActiveCanMoveCamera():
	g_canmovecamera = true
func DeactiveCanMoveCamera():
	g_canmovecamera = false
#screen  boundary를 벗어나지 않게 수정
	
