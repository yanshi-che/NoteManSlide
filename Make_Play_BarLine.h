#pragma once

namespace Make {
	namespace Play {
		class Make_Play_BarLine
		{
		private:
			double time;
			double y;
		public:
			Make_Play_BarLine(const double time);
			void update(double nowTime);
			void draw();
		};
	}
}

