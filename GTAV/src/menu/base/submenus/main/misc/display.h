#pragma once
#include "menu/base/submenu.h"

class display_menu : public menu::submenu::submenu {
public:
	static display_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	display_menu()
		: menu::submenu::submenu() {}
};

namespace misc::display::vars {
	struct variables {
		bool m_fps;
		bool m_position;
		bool m_free_slots;
		bool m_modder_count;
		bool m_entity_pools;
		bool m_host;
		bool m_next_host;
		bool m_frame_count;

		int m_fps_var;
		int m_draw_fps_cache[2];
		int m_draw_fps_average = 0;
		int m_draw_fps_average_total = 0;
		int m_draw_fps_average_count = 0;
	};

	extern variables m_vars;
}