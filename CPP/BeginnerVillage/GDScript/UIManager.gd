extends Node

# 정상적으로 작동하는 테스트 스크립트

func _process(delta):
	$Label.text = String(get_node("/root/Main").get_test_attr())
	
