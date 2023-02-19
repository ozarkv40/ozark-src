#pragma once
#include "menu/base/submenu.h"

class vehicle_gravity_menu : public menu::submenu::submenu {
public:
	static vehicle_gravity_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_gravity_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::gravity::vars {
	struct variables {
		int m_gravity;
		bool m_slippy_wheels;
		bool m_drive_on_water;
		bool m_freeze;
		bool m_stick_to_ground;
		bool m_auto_flip;

		Entity m_drive_on_water_entity;
	};

	extern variables m_vars;
}