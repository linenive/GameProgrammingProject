extends Node2D

enum eCameraState {kDefault, kTrace}
export (eCameraState)var g_nowcamerastate
var g_nowtarget_path

var g_screen_size

func _ready():	
	SetLimit()
	InitCameraSetting()
	
func _process(_delta):
	$Camera2D.position = get_node(g_nowtarget_path).position
	
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
	
func SetCameraSetting_Trace(newtracing_path):
	g_nowcamerastate = eCameraState.kTrace
	g_nowtarget_path =newtracing_path
	$EmptyCamera.DeactiveCanMoveCamera()
