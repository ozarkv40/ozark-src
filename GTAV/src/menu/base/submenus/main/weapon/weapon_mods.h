#pragma once
#include "menu/base/submenu.h"
#include "menu/base/util/timers.h"

class weapon_mods_menu : public menu::submenu::submenu {
public:
	static weapon_mods_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	weapon_mods_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::mods::vars {
	struct variables {
		bool m_infinite_ammo;
		bool m_instant_kill;
		bool m_rapid_fire;
		bool m_laser_sight;
		bool m_explosive_ammo;
		bool m_incendiary_ammo;
		bool m_delete_gun;
		bool m_force_gun;
		bool m_teleport_gun;
		bool m_airstrike_gun;
		bool m_defibrillator_gun;
		bool m_money_gun;
		bool m_clown_gun;
		bool m_shrink_gun;
		bool m_deadeye_gun;
		bool m_deadeye_gun_internal;
		bool m_deadeye_gun_timeout;
		bool m_rope_gun;
		bool m_vehicle_stealer_gun;
		bool m_hash_gun;
		bool m_valkyrie_gun;
		bool m_valkryie_running;

		Object m_valkyrie_object;
		Cam m_valkyrie_cam;

		int m_valkyrie_timer = 0;
		int m_targeting_mode;

		std::vector<std::pair<uint32_t, uint32_t>> m_weapon_groups;

		Entity m_rope_gun_entities[2];
		Object m_rope_gun_object;

		menu::timers::timer m_deadeye_gun_timer;
		menu::timers::timer m_deadeye_gun_timeout_timer;
		std::vector<Ped> m_deadeye_gun_peds;
	};

	extern variables m_vars;
}