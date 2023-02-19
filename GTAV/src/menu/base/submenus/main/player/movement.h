#pragma once
#include "menu/base/submenu.h"

class movement_menu : public menu::submenu::submenu {
public:
	static movement_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	movement_menu()
		: menu::submenu::submenu() {}
};

namespace player::movement::vars {
	struct variables {
		bool m_no_clip;
		bool m_no_clip_notify = true;
		bool m_no_clip_bind;

		bool m_super_jump;
		bool m_super_run;
		bool m_super_run_alternative;
		bool m_super_swim;

		float m_super_run_speed = 1.49f;
		float m_super_run_alternative_speed = 5.f;
		float m_super_swim_speed = 1.49f;
		float m_no_clip_speed = 1.f;

		Entity m_walk_on_air_entity;
		bool m_walk_on_air;
	};

	extern variables m_vars;
}