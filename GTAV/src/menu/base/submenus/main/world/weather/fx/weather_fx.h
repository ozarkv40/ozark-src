#pragma once
#include "menu/base/submenu.h"
#include "rage/types/generic_types.h"

class weather_fx_menu : public menu::submenu::submenu {
public:
	static weather_fx_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	weather_fx_menu()
		: menu::submenu::submenu() {}
};

namespace world::weather::fx::vars {
	struct shader {
		rage::types::drop_shader* m_drop;
		color_rgba m_internal_color;
		float m_luminance = 1.f;
	};

	struct variables {
		std::vector<shader> m_shaders;
		std::vector<rage::types::drop_shader> m_originals;
		int m_scroll = 0;
	};

	extern variables m_vars;
}