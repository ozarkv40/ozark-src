#pragma once
#include "menu/base/submenu.h"
#include <unordered_map>

class spawner_vehicle_selected_menu : public menu::submenu::submenu {
public:
	static spawner_vehicle_selected_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	spawner_vehicle_selected_menu()
		: menu::submenu::submenu() {}
};

namespace spawner::vehicle::selected::vars {
	struct variables {
		int m_selected;
		std::unordered_map<uint32_t, std::string> m_textures;
	};

	extern variables m_vars;
}