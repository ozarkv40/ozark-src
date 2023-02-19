#pragma once
#include "menu/base/submenu.h"

class hand_trails_menu : public menu::submenu::submenu {
public:
	static hand_trails_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	hand_trails_menu()
		: menu::submenu::submenu() {}
};

namespace player::trails::vars {
	struct variables {
		bool m_trails;
		int m_trail_bone_left;
		int m_trail_bone_right;

		color_rgba m_trail_color = { 255, 0, 0, 255 };
	};

	extern variables m_vars;
}