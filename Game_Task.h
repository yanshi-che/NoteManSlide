#pragma once

namespace Game {

	class Game_Task
	{
	public:
		virtual ~Game_Task() {}
		virtual void initialize() {}
		virtual void finalize() {}
		virtual void update() = 0;
		virtual void draw() = 0;
	};
}

