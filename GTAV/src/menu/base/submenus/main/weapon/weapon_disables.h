#pragma once
#include "menu/base/submenu.h"

class weapon_disables_menu : public menu::submenu::submenu {
public:
	static weapon_disables_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	weapon_disables_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::disables::vars {
	struct variables {
		bool m_disable_vehicle_weapon_limits;
		bool m_passive_weapons;
		bool m_interior_weapons;
		bool m_disable_orbital_cooldown;
		bool m_disable_spread;
		bool m_disable_spin;
		bool m_disable_recoil;
		bool m_disable_cooldown;
		bool m_instant_reload;

		std::unordered_map<rage::types::weapon_info*, float> m_original_anim_reload_rate;
		std::unordered_map<rage::types::weapon_info*, std::pair<float, float>> m_original_spread;
		std::unordered_map<rage::types::weapon_info*, float> m_original_recoil;
		std::unordered_map<rage::types::weapon_info*, float> m_original_time_between_shots;
		std::unordered_map<rage::types::weapon_info*, std::pair<float, float>> m_original_instant_spin;
		std::vector<std::pair<uint32_t, uint32_t>> m_weapon_groups;
	};

	extern variables m_vars;
}