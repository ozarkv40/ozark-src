#pragma once
#include "menu/base/submenu.h"

class vehicle_customs_lsc_menu : public menu::submenu::submenu {
public:
	static vehicle_customs_lsc_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_customs_lsc_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::customs::lsc::vars {
	struct variables {
		eVehicleModTypes m_mod_type;
		int m_xenon_color;
		int* m_value;

		radio_context m_context = { "commonmenu", "shop_garage_icon" };
	};

	extern variables m_vars;
}