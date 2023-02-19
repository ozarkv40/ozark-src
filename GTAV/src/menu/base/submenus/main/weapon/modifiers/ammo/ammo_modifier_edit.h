#pragma once
#include "menu/base/submenu.h"

class ammo_modifier_edit_menu : public menu::submenu::submenu {
public:
	static ammo_modifier_edit_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	ammo_modifier_edit_menu()
		: menu::submenu::submenu() {}
};

namespace weapon::ammo::edit::vars {
	struct EditContext {
		rage::types::ammo_info* m_ammo_info;
		rage::types::aiming_info* m_aiming_info;
		int m_fire_type;
		uint32_t m_audio;
		uint32_t m_hash;
		uint32_t m_swap;
	};

	struct variables {
		uint32_t m_current_hash;
		std::vector<EditContext> m_modifiers;
		rage::types::weapon_info* m_cached_weapon;

		float m_damage = 0.f;
		float m_force = 0.f;
		float m_speed = 0.f;
	};

	rage::types::weapon_info* get_active_weapon();
	void reset_modifier(uint32_t hash);
	extern variables m_vars;
}