#include "TestManager.h"

void TestManager::_register_methods(){
	register_method("_ready", &TestManager::_ready);
	register_method("_process", &TestManager::_process);
	register_method("_physics_process", &TestManager::_physics_process);
	register_method("pull", &TestManager::pull);

	register_method("getSkillLevel", &TestManager::getSkillLevel);
	register_method("getSkillName", &TestManager::getSkillName);
	register_method("getTestDataA", &TestManager::getTestDataA);
	register_method("getTestDataB", &TestManager::getTestDataB);

	register_property<TestManager, int>("skilLevel", &TestManager::test_c, 10);
}

void TestManager::_init(){

}

void TestManager::_ready(){
	skill = Skill(5, "µµº®");
	skill.SetData(456, true);
}

void TestManager::_process(float delta){
	skill.SetData(789, true);
}

void TestManager::_physics_process(float delta){
}

void TestManager::pull(Variant from, float magnitude){
}
