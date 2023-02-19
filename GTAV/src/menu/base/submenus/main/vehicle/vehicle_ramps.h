#pragma once
#include "menu/base/submenu.h"

class vehicle_ramps_menu : public menu::submenu::submenu {
public:
	static vehicle_ramps_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_ramps_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::ramps::vars {
	struct variables {
		bool m_transparency;
		bool m_front_ramp;
		bool m_rear_ramp;
		bool m_left_ramp;
		bool m_right_ramp;

		int m_ramp_type = 1;
	};

	extern variables m_vars;
}