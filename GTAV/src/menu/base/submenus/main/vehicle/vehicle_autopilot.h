#pragma once
#include "menu/base/submenu.h"

class vehicle_autopilot_menu : public menu::submenu::submenu {
public:
	static vehicle_autopilot_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_autopilot_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::autopilot::vars {
	struct variables {
		int m_destinations;
		int m_styles;

		float m_speed = 20.f;
	};

	extern variables m_vars;
}