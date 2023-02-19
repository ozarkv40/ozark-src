#pragma once
#include "menu/base/submenu.h"

class vehicle_customs_neon_menu : public menu::submenu::submenu {
public:
	static vehicle_customs_neon_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_customs_neon_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::customs::neon::vars {
	struct variables {

	};

	extern variables m_vars;
}