#pragma once
#include "menu/base/submenu.h"

class trains_menu : public menu::submenu::submenu {
public:
	static trains_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	trains_menu()
		: menu::submenu::submenu() {}
};

namespace world::train::vars {
	struct variables {
		bool m_allow_random = true;
		bool m_spawn;
		bool m_derail;
		bool m_speed;

		int m_speed_val = 9;
		int m_paint;
		Vehicle m_train = 0;
	};

	extern variables m_vars;
}