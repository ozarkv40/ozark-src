#pragma once
#include "menu/base/submenu.h"

class clipset_menu : public menu::submenu::submenu {
public:
	static clipset_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	clipset_menu()
		: menu::submenu::submenu() {}
};

namespace player::clipset::vars {
	struct variables {
		int m_motion;
		int m_weapon;
	};

	extern variables m_vars;
}