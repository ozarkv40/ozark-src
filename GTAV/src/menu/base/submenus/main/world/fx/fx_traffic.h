#pragma once
#include "menu/base/submenu.h"
#include "fx_color.h"
#include "fx_ui_color.h"

class fx_traffic_menu : public menu::submenu::submenu {
public:
	static fx_traffic_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	fx_traffic_menu()
		: menu::submenu::submenu() {}
};

namespace world::fx::traffic::vars {
	struct variables {
		float* m_far_fade_start;
		float* m_far_fade_end;
		float* m_near_fade_start;
		float* m_near_fade_end;

		world::fx::color::vars::custom_color m_red_color;
		world::fx::color::vars::custom_color m_green_color;
		world::fx::color::vars::custom_color m_amber_color;
		world::fx::color::vars::custom_color m_walk_color;
		world::fx::color::vars::custom_color m_dont_walk_color;
		world::fx::ui::color::vars::custom_color m_near_color;
	};

	extern variables m_vars;
}