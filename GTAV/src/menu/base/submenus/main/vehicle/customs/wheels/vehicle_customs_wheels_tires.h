#pragma once
#include "menu/base/submenu.h"

class vehicle_customs_wheels_tires_menu : public menu::submenu::submenu {
public:
	static vehicle_customs_wheels_tires_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_customs_wheels_tires_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::customs::wheels::tires::vars {
	struct variables {
		bool m_update_cache;
		bool m_custom_tires;
		bool m_tire_smoke;
		bool m_tires_low_grip;
		color_rgba m_tire_smoke_color;
	};

	extern variables m_vars;
}