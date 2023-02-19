#pragma once
#include "menu/base/submenu.h"

class vehicle_seats_edit_menu : public menu::submenu::submenu {
public:
	static vehicle_seats_edit_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_seats_edit_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::seats::edit::vars {
	struct variables {
		int m_seat;
	};

	extern variables m_vars;
}