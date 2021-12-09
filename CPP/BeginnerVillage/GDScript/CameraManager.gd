extends Node2D

enum eCameraState {DEFAULT, TRACE}

export (eCameraState)var g_nowcamerastate
var targetNode : Node2D

var g_nowtarget_path
var g_world_size
var g_screen_size
var g_velocity

var camera_move_lock

var kcamera_speed=10
var kmouse_moving_interval=10

var kzoom_default=1.0
var kzoom_in=0.5
var kzoom_max = 10
var kzoom_min = 0.5

signal start_trace
signal stop_trace

func _ready():	
	SetScreenLimit()
	InitCameraSetting()
	
	$CameraCPP.SetCurrentCameraPosition(Vector2(g_world_size.x/2, g_world_size.y/2))
	$CameraCPP.g_zoom_scroll_factor = 1.6
	
	camera_move_lock = false
	
func _process(_delta):
	DetectCameraMoveObj()
	DetectZoomScrollKey()
	DetectCameraMoveLock()
	
func SetScreenLimit():
	g_world_size = get_node("/root/Main/WorldManager").GetWorldSize()
	g_screen_size = get_viewport_rect().size
	
func InitCameraSetting():
	$CameraCPP.g_speed = kcamera_speed
	$CameraCPP.g_mouse_moving_interval = kmouse_moving_interval
	$CameraCPP.g_zoom_max = kzoom_max
	$CameraCPP.g_zoom_min = kzoom_min
	SetCameraSetting_Default()
	Zoom(kzoom_default)

func SetCameraPosition(new_position):
	$CameraCPP.SetCurrentCameraPosition(new_position)
func DetectCameraMoveLock():
	if Input.is_action_just_pressed("camera_move_lock"):
		camera_move_lock = !camera_move_lock
func DetectCameraMoveObj():
	if g_nowcamerastate == eCameraState.DEFAULT:
		MoveCameraDefault()
	else:
		MoveCameraTrace()
		
func MoveCameraDefault():
	DetectKeyPressDefault()
	$CameraCPP.CameraMoveWithKey(g_velocity)
	if camera_move_lock == false:
		$CameraCPP.CameraMoveWithMouse(get_viewport().get_mouse_position())
	
	$Camera2D.position = $CameraCPP.GetCurrentCameraPosition()
	
func DetectKeyPressDefault():
	g_velocity = Vector2(0,0)
	if Input.is_action_pressed("ui_left"):
		g_velocity.x -= 1
	if Input.is_action_pressed("ui_right"):
		g_velocity.x += 1
	if Input.is_action_pressed("ui_up"):
		g_velocity.y -= 1
	if Input.is_action_pressed("ui_down"):
		g_velocity.y += 1
		
func MoveCameraTrace():
	if HasTraceNode():
		$Camera2D.position = targetNode.position
		DetectKeyPressTrace()

func DetectKeyPressTrace():
	if (Input.is_action_just_pressed("ui_left") || Input.is_action_just_pressed("ui_right") 
	|| Input.is_action_just_pressed("ui_up") || Input.is_action_just_pressed("ui_down")):
		StopTracing()

func HasTraceNode():
	if get_node_or_null(g_nowtarget_path) == null:
		StopTracing()
		return false
	return true
		
func SetCameraSetting_Default():
	g_nowcamerastate = eCameraState.DEFAULT
	g_nowtarget_path = ""
	targetNode = null
	
# 사용법 : get_node("/root/Main/CameraManager").SetCameraSetting_Trace(mypath)
func SetCameraSetting_Trace(newtracing_path):
	g_nowcamerastate = eCameraState.TRACE
	g_nowtarget_path =newtracing_path
	targetNode = get_node(g_nowtarget_path)
	emit_signal("start_trace")
	#Zoom(kzoom_in)

func StopTracing():
	SetCameraPosition($Camera2D.position)
	SetCameraSetting_Default()
	emit_signal("stop_trace")
	
func DetectZoomScrollKey():
	#if g_nowcamerastate == eCameraState.DEFAULT:
	ZoomScroll()
		
func ZoomScroll():
	if Input.is_action_just_released("wheel_down"):
		$CameraCPP.ZoomOut()
		ZoomCamera($CameraCPP.GetCurrentZoom())
	if Input.is_action_just_released("wheel_up"):
		$CameraCPP.ZoomIn()	
		ZoomCamera($CameraCPP.GetCurrentZoom())
		
func ZoomCamera(new_zoom):
	$Camera2D.zoom.x = new_zoom
	$Camera2D.zoom.y = new_zoom	

func Zoom(new_zoom):
	$CameraCPP.SetCurrentZoom(new_zoom)
	ZoomCamera(new_zoom)

func GetCurrentCameraStateInString():
	return str(eCameraState.keys()[g_nowcamerastate])

func IsTargetNode(node):
	if targetNode == node:
		return true
	
	return false

# test와 연관된 부분, 그만 따라가기 버튼을 누르면 카메라가 줌아웃되고 다시 플레이어가 움직일 수 있게 되는 것
func _on_StopFollowing_pressed():
	StopTracing()

