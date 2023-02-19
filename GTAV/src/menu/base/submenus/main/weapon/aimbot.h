#pragma once
#include "menu/base/submenu.h"

class aimbot_menu : public menu::submenu::submenu {
public:
	static aimbot_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	aimbot_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::aimbot::vars {
	struct variables {
		bool m_toggle;
		bool m_aiming_required;
		bool m_auto_fire;
		bool m_auto_ads;
		bool m_show_aimbot_target;
		bool m_fov;
		bool m_fov_draw;

		int m_aim_entity;
		int m_aim_filter;
		int m_aim_type;
		int m_aim_tag;
		int m_auto_fire_delay;
		int m_auto_fire_delay_timer;
		int m_aim_distance;

		float m_fov_range = 2.5f;
	};

	extern scroll_struct<int> aim_entity[3];
	extern variables m_vars;
}