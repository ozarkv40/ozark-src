#pragma once
#include "menu/base/submenu.h"

class particle_gun_menu : public menu::submenu::submenu {
public:
	static particle_gun_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	particle_gun_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::particle::vars {
	struct variables {
		bool m_toggle;
		float m_scale = 1.f;
		radio_context m_radio = { "commonmenu", "shop_makeup_icon" };
	};

	extern variables m_vars;
}