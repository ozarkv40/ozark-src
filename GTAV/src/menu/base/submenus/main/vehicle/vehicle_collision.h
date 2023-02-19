#pragma once
#include "menu/base/submenu.h"

class vehicle_collision_menu : public menu::submenu::submenu {
public:
	static vehicle_collision_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_collision_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::collision::vars {
	struct variables {
		bool m_disable_full_collision;
		bool m_disable_vehicle_collision;
	};

	extern variables m_vars;
}