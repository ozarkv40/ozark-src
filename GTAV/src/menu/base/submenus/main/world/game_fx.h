#pragma once
#include "menu/base/submenu.h"

class game_fx_menu : public menu::submenu::submenu {
public:
	static game_fx_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	game_fx_menu()
		: menu::submenu::submenu() {}
};

namespace world::fx::vars {
	struct variables {
		bool m_disable_lights;
		bool m_render_water_on_map;
		bool m_disable_sky;

		float m_fog;
		float m_water;

		bool m_fog_toggle;
		bool m_water_toggle;
	};

	extern variables m_vars;
}