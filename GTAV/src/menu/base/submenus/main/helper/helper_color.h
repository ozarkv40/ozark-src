#pragma once
#include "menu/base/submenu.h"
#include <functional>

class helper_color_menu : public menu::submenu::submenu {
public:
	static helper_color_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	helper_color_menu()
		: menu::submenu::submenu() {}
};

namespace helper::color::vars {
	struct variables {
		int m_type;
		color_rgba* m_color;
		color_hsv m_hsv;

		std::function<void()> m_callback = []() {};
	};

	extern variables m_vars;
}