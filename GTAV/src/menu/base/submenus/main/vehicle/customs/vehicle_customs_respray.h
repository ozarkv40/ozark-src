#pragma once
#include "menu/base/submenu.h"

class vehicle_customs_respray_menu : public menu::submenu::submenu {
public:
	static vehicle_customs_respray_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_customs_respray_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::customs::respray::vars {
	struct variables {
		bool m_update_cache;
		int m_livery;
	};

	extern variables m_vars;
}