#pragma once
#include "menu/base/submenu.h"

class vehicle_modifiers_handling_menu : public menu::submenu::submenu {
public:
	static vehicle_modifiers_handling_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_modifiers_handling_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::modifiers::handling::vars {
	struct variables {
		int m_type = 0;

		bool m_in_boat;
		bool m_in_bike;
		bool m_in_flying;
	};

	extern variables m_vars;
}