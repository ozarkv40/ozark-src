#pragma once
#include "menu/base/submenu.h"

class vehicle_seats_menu : public menu::submenu::submenu {
public:
	static vehicle_seats_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_seats_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::seats::vars {
	struct variables {

	};

	extern variables m_vars;
}