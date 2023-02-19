#pragma once
#include "menu/base/submenu.h"

class ocean_tuning_menu : public menu::submenu::submenu {
public:
	static ocean_tuning_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	ocean_tuning_menu()
		: menu::submenu::submenu() {}
};

namespace world::ocean::tuning::vars {
	struct variables {
		rage::types::water_tune m_water_tune;
	};

	extern variables m_vars;
}