#pragma once
#include "menu/base/submenu.h"

class vehicle_customs_wheels_type_edit_menu : public menu::submenu::submenu {
public:
	static vehicle_customs_wheels_type_edit_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_customs_wheels_type_edit_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::customs::wheels::type::edit::vars {
	struct variables {
		int m_wheel_type;
		radio_context m_context = { "commonmenu", "shop_garage_icon" };
	};

	extern variables m_vars;
}