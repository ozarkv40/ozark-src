#pragma once
#include "menu/base/submenu.h"

class hud_menu : public menu::submenu::submenu {
public:
	static hud_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	hud_menu()
		: menu::submenu::submenu() {}
};

namespace misc::hud::vars {
	struct variables {
		int m_hud;
		color_rgba m_color;
	};

	extern variables m_vars;
}