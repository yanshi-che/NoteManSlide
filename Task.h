#pragma once

#include <memory>

#include "SceneChanger.h"

class Task
{
protected:
	std::shared_ptr<SceneChanger> p_sceneChanger;
public:
	Task(std::shared_ptr<SceneChanger>& p_sceneChanger);
	virtual ~Task() {};
	virtual void initialize() {};
	virtual void finalize() {};
	virtual void draw() {};
	virtual void update() {};
};

