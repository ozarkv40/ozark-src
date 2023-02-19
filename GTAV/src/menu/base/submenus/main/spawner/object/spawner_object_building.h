#pragma once
#include "menu/base/submenu.h"

class spawner_object_building_menu : public menu::submenu::submenu {
public:
	static spawner_object_building_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	spawner_object_building_menu()
		: menu::submenu::submenu() {}
};

namespace spawner::object::building::vars {
	struct variables {
		int m_type;
		int m_count[4] = { 30, 33, 15, 20 };
		float m_vertical_angle;
	};

	extern variables m_vars;
}