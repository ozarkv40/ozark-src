#pragma once
#include "stdafx.h"
#include "global/ui_vars.h"

namespace menu {
	class rainbow {
	public:
		rainbow(int min = 25, int max = 250, int steps = 80);

		void add(color_rgba* color);
		void remove(color_rgba* color);
		void run();
		void start();
		void stop();
		void toggle(bool toggle);

		color_rgba get_default(color_rgba* color);

		bool m_enabled = false;
		int m_increment = 0;
		int m_min = 0;
		int m_max = 0;
		int m_steps = 0;
		color_rgba m_color;
	private:
		std::vector<color_rgba*> m_colors;
		std::vector<std::pair<color_rgba*, color_rgba>> m_default_colors;
	};
}