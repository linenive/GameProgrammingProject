extends Node2D

enum eCameraState {DEFAULT, TRACE}
export (eCameraState)var g_nowcamerastate
var targetNode : Node2D
var g_nowtarget_path
var g_screen_size

var kzoom_in = 0.5
var kzoom_default = 1
var kzoom_scrollfactor = 0.2
var kzoom_max = 1.5
var kzoom_min = 0.5

func _ready():	
	SetLimit()
	InitCameraSetting()
	
func _process(_delta):
	$Camera2D.position = targetNode.position
	DetectZoomScrollKey()
	
func SetLimit():
<<<<<<< Updated upstream
	g_screen_size = get_viewport_rect().size
=======
	CalcMapBoundary()
	$EmptyCamera.SetMoveKeyBoundary(g_screen_boundary_lefttop,g_screen_boundary_rightbottom)
	
	$Camera2D.limit_left = g_screen_boundary_lefttop.x
	$Camera2D.limit_right = g_screen_boundary_rightbottom.x
	$Camera2D.limit_top = g_screen_boundary_lefttop.y
	$Camera2D.limit_bottom = g_screen_boundary_rightbottom.y

func CalcMapBoundary():
	GetScreenBoundary(Vector2(0,0), Vector2(1728,1728))
	
func GetScreenBoundary(lefttop, rightbottom):
	g_screen_boundary_lefttop = lefttop
	g_screen_boundary_rightbottom = rightbottom
>>>>>>> Stashed changes
	
	$Camera2D.limit_left = -g_screen_size.x
	$Camera2D.limit_right = g_screen_size.x
	$Camera2D.limit_top = -g_screen_size.y
	$Camera2D.limit_bottom = g_screen_size.y

func InitCameraSetting():
	SetCameraSetting_Default()

func SetCameraSetting_Default():
	g_nowcamerastate = eCameraState.DEFAULT
	g_nowtarget_path = "EmptyCamera"
	targetNode = get_node(g_nowtarget_path)
	$EmptyCamera.ActiveCanMoveCamera()
	Zoom(kzoom_default)
	
func SetCameraSetting_Trace(newtracing_path):
	g_nowcamerastate = eCameraState.TRACE
	g_nowtarget_path =newtracing_path
	targetNode = get_node(g_nowtarget_path)
	$EmptyCamera.DeactiveCanMoveCamera()
	Zoom(kzoom_in)

func DetectZoomScrollKey():
	if g_nowcamerastate == eCameraState.DEFAULT:
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
<<<<<<< Updated upstream

=======
	$EmptyCamera.SetZoomScale($Camera2D.zoom.x)
	
# test와 연관된 부분, 그만 따라가기 버튼을 누르면 카메라가 줌아웃되는 것
func _on_StopFollowing_pressed():
	SetCameraSetting_Default()
>>>>>>> Stashed changes
	

