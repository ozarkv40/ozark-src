#pragma once
#include "menu/base/submenu.h"

class spawner_vehicle_settings_menu : public menu::submenu::submenu {
public:
	static spawner_vehicle_settings_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	spawner_vehicle_settings_menu()
		: menu::submenu::submenu() {}
};

namespace spawner::vehicle::settings::vars {
	struct variables {
		bool m_notification = true;
		bool m_blip;
		bool m_particle_fx;
		bool m_teleport_inside = true;
		bool m_godmode = true;
		bool m_fade;
		bool m_delete_current = true;
		bool m_air_vehicles_in_air = true;
		bool m_upgrades;
		bool m_session_gift;
		
		int m_upgrades_var;
		float m_spawn_height = 100.f;
	};

	extern variables m_vars;
}