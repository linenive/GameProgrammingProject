extends Node2D

enum eCameraState {kDefault, kTrace}
export (eCameraState)var g_nowcamerastate
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
	$Camera2D.position = get_node(g_nowtarget_path).position
	DetectZoomScrollKey()
	
func SetLimit():
	g_screen_size = get_viewport_rect().size
	
	$Camera2D.limit_left = -g_screen_size.x
	$Camera2D.limit_right = g_screen_size.x
	$Camera2D.limit_top = -g_screen_size.y
	$Camera2D.limit_bottom = g_screen_size.y

func InitCameraSetting():
	SetCameraSetting_Default()

func SetCameraSetting_Default():
	g_nowcamerastate = eCameraState.kDefault
	g_nowtarget_path ="EmptyCamera"
	$EmptyCamera.ActiveCanMoveCamera()
	Zoom(kzoom_default)
	
func SetCameraSetting_Trace(newtracing_path):
	g_nowcamerastate = eCameraState.kTrace
	g_nowtarget_path =newtracing_path
	$EmptyCamera.DeactiveCanMoveCamera()
	Zoom(kzoom_in)

func DetectZoomScrollKey():
	if g_nowcamerastate == eCameraState.kDefault:
		ZoomScroll()
		
func ZoomScroll():
	if Input.is_action_just_released("wheel_down"):
		ZoomOut()
	if Input.is_action_just_released("wheel_up"):
		ZoomIn()	
		
func ZoomOut():
	var next_scrollfactor=$Camera2D.zoom.x+kzoom_scrollfactor
	if next_scrollfactor<kzoom_max:
		Zoom(next_scrollfactor)
		
func ZoomIn():
	var next_scrollfactor=$Camera2D.zoom.x-kzoom_scrollfactor
	if next_scrollfactor>kzoom_min:
		Zoom(next_scrollfactor)

func Zoom(zoomfactor):
	$Camera2D.zoom.x=zoomfactor
	$Camera2D.zoom.y=zoomfactor

	

