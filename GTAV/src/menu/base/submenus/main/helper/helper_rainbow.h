#pragma once
#include "menu/base/submenu.h"
#include "menu/base/util/rainbow.h"

class helper_rainbow_menu : public menu::submenu::submenu {
public:
	static helper_rainbow_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	helper_rainbow_menu()
		: menu::submenu::submenu() {}
};

namespace helper::rainbow::vars {
	struct variables {
		color_rgba m_local_color;
		menu::rainbow m_local_rainbow;
		menu::rainbow* m_rainbow;
	};

	extern variables m_vars;
}