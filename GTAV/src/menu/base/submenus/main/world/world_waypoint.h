#pragma once
#include "menu/base/submenu.h"

class world_waypoint_menu : public menu::submenu::submenu {
public:
	static world_waypoint_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	world_waypoint_menu()
		: menu::submenu::submenu() {}
};

namespace world::waypoint::vars {
	struct variables {
		bool m_toggle;
		int m_marker = 28;
		int m_max = 40;
		float m_scale = 0.5f;

		color_rgba m_color = color_rgba(255, 0, 255, 255);
	};

	extern variables m_vars;
}