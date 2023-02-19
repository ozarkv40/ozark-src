#pragma once
#include "menu/base/submenu.h"

class model_swaps_presets_menu : public menu::submenu::submenu {
public:
	static model_swaps_presets_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	model_swaps_presets_menu()
		: menu::submenu::submenu() {}
};

namespace misc::swaps::model::presets::vars {
	struct variables {
		bool m_monster_truck_police;
		bool m_astronaut_police_peds;
	};

	extern variables m_vars;
}