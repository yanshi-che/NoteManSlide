#pragma once


#include <memory>

#include "SceneChanger.h"
#include "Make_DrawManager.h"

class MainSceneManager
{
private:
	std::shared_ptr<SceneChanger> sceneChanger;
	std::unique_ptr<Task> scene;

};

