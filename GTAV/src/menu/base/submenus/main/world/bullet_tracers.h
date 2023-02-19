#pragma once
#include "menu/base/submenu.h"
#include "rage/types/generic_types.h"

class bullet_tracers_menu : public menu::submenu::submenu {
public:
	static bullet_tracers_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	bullet_tracers_menu()
		: menu::submenu::submenu() {}
};

namespace world::tracers::vars {
	struct tracer {
		uint32_t m_spawn_time;
		math::vector3_<float> m_spawn_position;
		math::vector3_<float> m_end_position;
		void* m_shooter;
		rage::types::weapon_info* m_weapon_info;
		bool m_populated = false;
	};

	struct variables {
		int m_tracer_current_index = 0;
		tracer m_tracers[1000];

		bool m_npc;
		bool m_player;
		bool m_self;

		int m_npc_timer = 1;
		int m_player_timer = 1;
		int m_self_timer = 1;
		int m_selected_color;

		color_rgba m_colors[3] = {
			color_rgba(255, 0, 0),
			color_rgba(0, 255, 0),
			color_rgba(0, 0, 255)
		};
	};

	extern variables m_vars;
}