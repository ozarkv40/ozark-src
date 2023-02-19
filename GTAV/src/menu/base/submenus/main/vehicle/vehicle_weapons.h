#pragma once
#include "menu/base/submenu.h"

class vehicle_weapons_menu : public menu::submenu::submenu {
public:
	static vehicle_weapons_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_weapons_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::weapons::vars {
	struct variables {
		bool m_toggle;
		bool m_aiming_lines;
		float m_speed = 2000.f;
		int m_aiming_line_type;

		radio_context m_context = { "commonmenu", "shop_ammo_icon" };
	};

	extern variables m_vars;
}