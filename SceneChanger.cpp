#include "SceneChanger.h"

SceneChanger::SceneChanger() { next = Scene::None; }

void SceneChanger::changeScene(Scene next) {
	this->next = next;
}

Scene SceneChanger::getNextScene() {
	return next;
}