#pragma once
#include "menu/base/submenu.h"

class protection_menu : public menu::submenu::submenu {
public:
	static protection_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	protection_menu()
		: menu::submenu::submenu() {}
};

namespace protection::vars {
	struct variables {
		bool m_fake_lag;
		bool m_force_visible;
		bool m_disable_bullets;
		bool m_disable_projectiles;
	};

	extern variables m_vars;
}