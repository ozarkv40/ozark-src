#pragma once
#include "menu/base/submenu.h"

class vehicle_customs_wheels_type_menu : public menu::submenu::submenu {
public:
	static vehicle_customs_wheels_type_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_customs_wheels_type_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::customs::wheels::type::vars {
	struct variables {
		bool m_update_cache;
		int m_cached_wheel_type;
		int m_cached_wheel_index;
		eVehicleModTypes m_mod_type;
	};

	extern variables m_vars;
}