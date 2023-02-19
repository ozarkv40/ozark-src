#pragma once
#include "menu/base/submenu.h"

class weapon_multipliers_menu : public menu::submenu::submenu {
public:
	static weapon_multipliers_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	weapon_multipliers_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::multipliers::vars {
	struct variables {
		bool m_weapon_damage_multiplier;
		bool m_melee_damage_multiplier;
		bool m_defense_damage_multiplier;

		float m_weapon_damage_multiplier_val = 1.f;
		float m_melee_damage_multiplier_val = 1.f;
		float m_defense_damage_multiplier_val = 1.f;
	};

	extern variables m_vars;
}