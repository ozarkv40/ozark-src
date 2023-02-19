#pragma once
#include "menu/base/submenu.h"

class spawner_vehicle_save_menu : public menu::submenu::submenu {
public:
	static spawner_vehicle_save_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	spawner_vehicle_save_menu()
		: menu::submenu::submenu() {}
};

namespace spawner::vehicle::save::vars {
	struct variables {

	};

	extern variables m_vars;
}