#include "Task.h"

Task::Task(std::shared_ptr<SceneChanger>& p_sceneChanger) {
	this->p_sceneChanger = p_sceneChanger;
}

