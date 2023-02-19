#pragma once
#include "menu/base/submenu.h"

class ammo_modifier_load_menu : public menu::submenu::submenu {
public:
	static ammo_modifier_load_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	ammo_modifier_load_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::ammo::load::vars {
	struct variables {

	};

	void save_modifier(const char* name, uint32_t model);
	extern variables m_vars;
}