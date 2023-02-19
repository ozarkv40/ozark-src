#pragma once
#include "menu/base/submenu.h"

class vehicle_customs_bumper_menu : public menu::submenu::submenu {
public:
	static vehicle_customs_bumper_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_customs_bumper_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::customs::bumper::vars {
	struct variables {

	};

	extern variables m_vars;
}