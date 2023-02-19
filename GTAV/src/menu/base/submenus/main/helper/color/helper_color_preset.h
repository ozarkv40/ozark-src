#pragma once
#include "menu/base/submenu.h"

class helper_color_preset_menu : public menu::submenu::submenu {
public:
	static helper_color_preset_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	helper_color_preset_menu()
		: menu::submenu::submenu() {}
};

namespace helper::color::preset::vars {
	struct variables {
		color_rgba* m_color;
	};

	extern variables m_vars;
}