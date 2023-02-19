#pragma once
#include "menu/base/submenu.h"

class spawner_vehicle_garage_selected_menu : public menu::submenu::submenu {
public:
	static spawner_vehicle_garage_selected_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	spawner_vehicle_garage_selected_menu()
		: menu::submenu::submenu() {}
};

namespace spawner::vehicle::garage::selected::vars {
	struct variables {
		int m_slot;
	};

	extern variables m_vars;
}