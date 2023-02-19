#pragma once
#include "menu/base/submenu.h"

class vehicle_customs_wheels_menu : public menu::submenu::submenu {
public:
	static vehicle_customs_wheels_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_customs_wheels_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::customs::wheels::vars {
	struct variables {
		bool m_update_cache;
		int m_paint_index;
	};

	extern variables m_vars;
}