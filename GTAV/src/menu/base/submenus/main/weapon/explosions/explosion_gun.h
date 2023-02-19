#pragma once
#include "menu/base/submenu.h"

class explosion_gun_menu : public menu::submenu::submenu {
public:
	static explosion_gun_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	explosion_gun_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::explosion::gun::vars {
	struct variables {
		int m_type;
		int m_change_owner_value;
		int m_list_size;
		bool m_toggle;
		bool m_audible = true;
		bool m_invisible = false;
		bool m_change_owner = false;
		float m_radius = 10.f;
		float m_camera_shake = 0.f;
		int m_owner_id = 0;
		scroll_struct<Ped> m_change_owner_list[32];
	};

	extern variables m_vars;
}
