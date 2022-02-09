#pragma once

namespace Make {

	class Make_Task
	{
	public:
		virtual ~Make_Task() {}
		virtual void initialize() {}
		virtual void finalize() {}
		virtual void update() = 0;
		virtual void draw() = 0;
	};
}

