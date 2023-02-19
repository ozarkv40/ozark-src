#pragma once
#include "menu/base/submenu.h"

class ammo_modifier_swap_menu : public menu::submenu::submenu {
public:
	static ammo_modifier_swap_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	ammo_modifier_swap_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::ammo::swap::vars {
	struct variables {

	};

	void swap(uint32_t first, uint32_t second);
	extern variables m_vars;
}