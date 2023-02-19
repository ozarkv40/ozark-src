#pragma once
#include "menu/base/submenu.h"

class clear_area_menu : public menu::submenu::submenu {
public:
	static clear_area_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	clear_area_menu()
		: menu::submenu::submenu() {}
};

namespace world::clear::vars {
	struct variables {
		float m_range = 100.f;
	};

	extern variables m_vars;
}