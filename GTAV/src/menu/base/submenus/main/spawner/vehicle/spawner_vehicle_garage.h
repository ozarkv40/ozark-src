#pragma once
#include "menu/base/submenu.h"

class spawner_vehicle_garage_menu : public menu::submenu::submenu {
public:
	static spawner_vehicle_garage_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	spawner_vehicle_garage_menu()
		: menu::submenu::submenu() {}
};

namespace spawner::vehicle::garage::vars {
	struct variables {
		std::vector<int> m_valid_slots[25];
	};

	const char* get_garage_name(int id);
	extern variables m_vars;
}