#pragma once
#include "menu/base/submenu.h"

class vehicle_multipliers_menu : public menu::submenu::submenu {
public:
	static vehicle_multipliers_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_multipliers_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::multipliers::vars {
	struct variables {
		float m_rpm = 1.f;
		float m_torque = 1.f;
		float m_headlight = 1.f;
		float m_traction_curve_max = 1.f;

		bool m_cached_traction = false;
	};

	extern variables m_vars;
}