#pragma once
#include "menu/base/submenu.h"

class weapon_modifiers_menu : public menu::submenu::submenu {
public:
	static weapon_modifiers_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	weapon_modifiers_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::modifiers::vars {
	struct variables {};

	rage::types::weapon_info* get_weapon_info();
	extern variables m_vars;
}