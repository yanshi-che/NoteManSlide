#pragma once

enum Scene {
	None = 0,
	Home,
	GameMenu,
	GamePlay,
	GameResult,
	Make,
	Config,
};

class SceneChanger
{
private:
	Scene next;
public:
	SceneChanger();
	void changeScene(Scene next);
	Scene nextScene();
};

