#pragma once
#include "menu/base/submenu.h"

class ammo_modifier_menu : public menu::submenu::submenu {
public:
	static ammo_modifier_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	ammo_modifier_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::ammo::vars {
	struct variables {

	};

	extern variables m_vars;
}