#pragma once
#include "menu/base/submenu.h"

class vehicle_health_menu : public menu::submenu::submenu {
public:
	static vehicle_health_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_health_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::health::vars {
	struct variables {
		bool m_auto_repair;
		bool m_auto_wash;
	};

	extern variables m_vars;
}