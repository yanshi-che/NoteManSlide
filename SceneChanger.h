#pragma once


enum class Scene {
	None = 0,
	Home,
	GameMenu,
	GamePlay,
	GameResult,
	NoteEdit,
	Config,
	Exit
};

class SceneChanger
{
private:
	Scene next;
public:
	SceneChanger();
	void changeScene(Scene next);
	Scene getNextScene();
};

