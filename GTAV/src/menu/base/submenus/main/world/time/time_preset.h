#pragma once
#include "menu/base/submenu.h"

class time_preset_menu : public menu::submenu::submenu {
public:
	static time_preset_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	time_preset_menu()
		: menu::submenu::submenu() {}
};

namespace world::time::preset::vars {
	struct variables {
	};

	extern variables m_vars;
}