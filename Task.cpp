#include "Task.h"

Task::Task(std::shared_ptr<SceneChanger>& sceneChanger) {
	this->sceneChanger = sceneChanger;
}

