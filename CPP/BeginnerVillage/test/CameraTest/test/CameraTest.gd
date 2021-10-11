extends Node2D


func _on_AutoMoveObj_traceStart(path, name):
	TraceStart(path, name)

func _on_StopFollowing_pressed():
	$UIManager.DeactiveStopFollowingButton()
	$CameraManager.SetCameraSetting_Default()
	
func _on_AutoMoveObj2_traceStart(path, name):
	TraceStart(path, name)

func TraceStart(path, name):
	$UIManager.StartNPCTrace(name)
	$CameraManager.SetCameraSetting_Trace(path)
