#pragma once
#include "menu/base/submenu.h"

class misc_swaps_menu : public menu::submenu::submenu {
public:
	static misc_swaps_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	misc_swaps_menu()
		: menu::submenu::submenu() {}
};

namespace misc::swaps::vars {
	struct variables {

	};

	extern variables m_vars;
}