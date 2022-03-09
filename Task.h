#pragma once

#include <memory>

#include "SceneChanger.h"

class Task
{
protected:
	std::shared_ptr<SceneChanger> sceneChanger;
public:
	Task(std::shared_ptr<SceneChanger>& sceneChanger);
	virtual ~Task() {};
	virtual void initialize() {};
	virtual void finalize() {};
	virtual void draw() = 0;
	virtual void update() = 0;
};

