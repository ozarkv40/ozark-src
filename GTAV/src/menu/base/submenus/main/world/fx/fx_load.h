#pragma once
#include "menu/base/submenu.h"

class fx_load_menu : public menu::submenu::submenu {
public:
	static fx_load_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	fx_load_menu()
		: menu::submenu::submenu() {}
};

namespace world::fx::load::vars {
	struct variables {
	};

	extern variables m_vars;
}