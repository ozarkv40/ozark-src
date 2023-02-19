#pragma once
#include "menu/base/submenu.h"

class vehicle_doors_menu : public menu::submenu::submenu {
public:
	static vehicle_doors_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_doors_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::doors::vars {
	struct variables {
		int m_open_door;
		int m_close_door;
		int m_delete_door;
	};

	extern variables m_vars;
}