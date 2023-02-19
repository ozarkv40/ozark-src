#pragma once
#include "menu/base/submenu.h"

class world_menu : public menu::submenu::submenu {
public:
	static world_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	world_menu()
		: menu::submenu::submenu() {}
};

namespace world::vars {
	struct variables {
		bool m_disable_lights;
		bool m_render_water_on_map;
		bool m_disable_sky;
		float m_fog;
	};

	extern variables m_vars;
}