#include "SceneChanger.h"

SceneChanger::SceneChanger(): next(None){}

void SceneChanger::changeScene(Scene next) {
	this->next = next;
}

Scene SceneChanger::nextScene() {
	return next;
}