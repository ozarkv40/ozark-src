#pragma once
#include "menu/base/submenu.h"

class vehicle_modifiers_handling_main_menu : public menu::submenu::submenu {
public:
	static vehicle_modifiers_handling_main_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_modifiers_handling_main_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::modifiers::handling::main::vars {
	struct variables {
		int m_type;
	};

	extern variables m_vars;
}