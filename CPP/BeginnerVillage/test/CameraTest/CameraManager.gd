extends Node2D

enum eCameraState {CAMERA_DEFAULT, CAMERA_TRACE}

export (eCameraState)var g_nowcamerastate

var g_targetNode : Node2D
var g_nowtarget_path
var g_screen_size # 현재 스크린 사이즈
var g_screen_boundary_lefttop : Vector2 # 현재 필드의 바운더리
var g_screen_boundary_rightbottom : Vector2 # 현재 필드의 바운더리

var kzoom_in = 0.5
var kzoom_default = 1
var kzoom_scrollfactor = 0.2
var kzoom_max = 1.5
var kzoom_min = 0.5

func _ready():	
	#SetLimit()
	InitCameraSetting()
	
func _process(_delta):
	#UpdateNowCameraSide()
	$Camera2D.position = g_targetNode.position
	DetectZoomScrollKey()
	
func SetLimit():
	g_screen_size = get_viewport_rect().size
	
	GetScreenBoundary()
	$Camera2D.limit_left = g_screen_boundary_lefttop.x
	$Camera2D.limit_right = g_screen_boundary_rightbottom.x
	$Camera2D.limit_top = g_screen_boundary_lefttop.y
	$Camera2D.limit_bottom = g_screen_boundary_rightbottom.y

# 필드의 바운더리를 받아오는 함수. 현재는 좌측과 위쪽으로 화면 크기만큼 한번씩 확장한 사이즈이다.
func GetScreenBoundary():
	g_screen_boundary_lefttop = Vector2(-g_screen_size.x , -g_screen_size.y)
	g_screen_boundary_rightbottom=Vector2(g_screen_size.x , g_screen_size.y)
	
func InitCameraSetting():
	SetCameraSetting_Default()

func SetCameraSetting_Default():
	g_nowcamerastate = eCameraState.CAMERA_DEFAULT
	g_nowtarget_path = "EmptyCamera"
	g_targetNode = get_node(g_nowtarget_path)
	$EmptyCamera.ActiveCanMoveCamera()
	Zoom(kzoom_default)
	
func SetCameraSetting_Trace(newtracing_path):
	g_nowcamerastate = eCameraState.CAMERA_TRACE
	g_nowtarget_path =newtracing_path
	g_targetNode = get_node(g_nowtarget_path)
	$EmptyCamera.DeactiveCanMoveCamera()
	Zoom(kzoom_in)

func DetectZoomScrollKey():
	if g_nowcamerastate == eCameraState.CAMERA_DEFAULT:
		ZoomScroll()
		
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

func Zoom(zoomfactor):
	$Camera2D.zoom.x = zoomfactor
	$Camera2D.zoom.y = zoomfactor

# test와 연관된 부분, 그만 따라가기 버튼을 누르면 카메라가 줌아웃되는 것
func _on_StopFollowing_pressed():
	SetCameraSetting_Default()
	
func UpdateNowCameraSide():
	print(1)
