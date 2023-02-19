#pragma once
#include "menu/base/submenu.h"
#include "menu/base/util/rainbow.h"
#include "rage/types/base_types.h"

class vehicle_tyre_tracks_menu : public menu::submenu::submenu {
public:
	static vehicle_tyre_tracks_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	vehicle_tyre_tracks_menu()
		: menu::submenu::submenu() {}
};

namespace vehicle::tyres::vars {
	struct variables {
		bool m_persistent;
		rage::types::vfx_wheel* m_cache;
		color_rgba m_color = color_rgba(255, 0, 0, 255);
		bool m_rainbow_toggle;
		bool m_save_to_config;
		menu::rainbow m_rainbow;
	};

	extern variables m_vars;
}