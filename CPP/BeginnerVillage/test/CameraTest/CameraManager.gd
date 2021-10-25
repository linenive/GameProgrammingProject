extends Node2D

enum eCameraState {DEFAULT, TRACE}

export (eCameraState)var g_nowcamerastate
export var g_velocity=Vector2()
export var g_speed=3

var g_unmoving_size
var g_unmoving_interval=100

var targetNode : Node2D
var g_nowtarget_path

var g_screen_size
var g_screen_boundary_lefttop
var g_screen_boundary_rightbottom

var kzoom_in = 0.5
var kzoom_default = 1
var kzoom_scrollfactor = 0.2
var kzoom_max = 1.5
var kzoom_min = 0.5

func _ready():	
	SetLimit()
	InitCameraSetting()
	
func _process(_delta):
	DetectCameraMoveObj()
	DetectZoomScrollKey()
	
func SetLimit():
	g_screen_size = get_viewport_rect().size
	g_unmoving_size = g_screen_size-Vector2(g_unmoving_interval,g_unmoving_interval)
	
	#in gd	
	$Camera2D.limit_left = -g_screen_size.x
	$Camera2D.limit_right = g_screen_size.x
	$Camera2D.limit_top = -g_screen_size.y
	$Camera2D.limit_bottom = g_screen_size.y

#in gd	
func DetectCameraMoveObj():
	if g_nowcamerastate == eCameraState.DEFAULT:
		MoveCamera()
	else:
		$Camera2D.position = targetNode.position
#in gd	
func MoveCamera():
	CameraMovewithKey()
	CameraMovewithMouse()
	
func CameraMovewithKey():
	DetectKeyPress()
	if g_velocity.length()>0:
		g_velocity = g_velocity.normalized()*g_speed
		$Camera2D.position+=g_velocity
#in gd
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
		addPos.x=-g_speed
	elif (nowmousevector.x>g_unmoving_size.x):
		addPos.x=g_speed	
	if (nowmousevector.y<g_unmoving_interval):
		addPos.y=-g_speed
	elif (nowmousevector.y>g_unmoving_size.y):
		addPos.y=g_speed
		
	$Camera2D.position += addPos	
	
# Camera Set ====	
func InitCameraSetting():
	SetCameraSetting_Default()

func SetCameraSetting_Default():
	g_nowcamerastate = eCameraState.DEFAULT
	g_nowtarget_path = ""
	targetNode = null
	Zoom(kzoom_default)
	
func SetCameraSetting_Trace(newtracing_path):
	g_nowcamerastate = eCameraState.TRACE
	g_nowtarget_path =newtracing_path
	targetNode = get_node(g_nowtarget_path)
	Zoom(kzoom_in)

# ZOOM ====
#in gd
func DetectZoomScrollKey():
	if g_nowcamerastate == eCameraState.DEFAULT:
		ZoomScroll()
#in gd
func ZoomScroll():
	if Input.is_action_just_released("wheel_down"):
		ZoomOut()
	if Input.is_action_just_released("wheel_up"):
		ZoomIn()	
		
func ZoomOut():
	var next_scrollfactor = $Camera2D.zoom.x + kzoom_scrollfactor
	if next_scrollfactor < kzoom_max:
		Zoom(next_scrollfactor)
		
func ZoomIn():
	var next_scrollfactor = $Camera2D.zoom.x - kzoom_scrollfactor
	if next_scrollfactor > kzoom_min:
		Zoom(next_scrollfactor)
#in gd
func Zoom(zoomfactor):
	$Camera2D.zoom.x = zoomfactor
	$Camera2D.zoom.y = zoomfactor
	
# test와 연관된 부분, 그만 따라가기 버튼을 누르면 카메라가 줌아웃되는 것
func _on_StopFollowing_pressed():
	SetCameraSetting_Default()

