#pragma once
#include "menu/base/submenu.h"

class teleport_save_load_menu : public menu::submenu::submenu {
public:
	static teleport_save_load_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	teleport_save_load_menu()
		: menu::submenu::submenu() {}
};

namespace teleport::save::vars {
	struct variables {
		std::vector<std::pair<std::string, math::vector3<float>>> m_locations;
	};

	extern variables m_vars;
}