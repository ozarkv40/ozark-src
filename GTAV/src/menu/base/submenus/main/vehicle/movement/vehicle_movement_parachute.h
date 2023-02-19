#pragma once
#include "menu/base/submenu.h"

class vehicle_movement_parachute_menu : public menu::submenu::submenu {
public:
	static vehicle_movement_parachute_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_movement_parachute_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::movement::parachute::vars {
	struct variables {
		bool m_auto_deploy;
	};

	extern variables m_vars;
}