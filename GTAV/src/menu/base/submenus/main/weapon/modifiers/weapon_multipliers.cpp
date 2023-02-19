#include "weapon_multipliers.h"
#include "menu/base/submenu_handler.h"
#include "../weapon_modifiers.h"

using namespace weapon::multipliers::vars;

namespace weapon::multipliers::vars {
	variables m_vars;
}

void weapon_multipliers_menu::load() {
	set_name("Multipliers");
	set_parent<weapon_modifiers_menu>();

	add_option(number_option<float>(TOGGLE, "Bullet Damage")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_weapon_damage_multiplier)
		.add_number(m_vars.m_weapon_damage_multiplier_val, "%.0f", 1.f).add_min(1.f).add_max(1000.f).set_scroll_speed(10)
		.add_click([] { if (menu::player::get_local_player().m_weapon_hash) native::set_player_weapon_damage_modifier(menu::player::get_local_player().m_id, 1.f); }).add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Melee Damage")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_melee_damage_multiplier)
		.add_number(m_vars.m_melee_damage_multiplier_val, "%.0f", 1.f).add_min(1.f).add_max(1000.f).set_scroll_speed(10)
		.add_click([] { if (menu::player::get_local_player().m_weapon_hash) native::set_player_melee_weapon_damage_modifier(menu::player::get_local_player().m_id, 1.f, 1); }).add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Defense Damage")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_defense_damage_multiplier)
		.add_number(m_vars.m_defense_damage_multiplier_val, "%.0f", 1.f).add_min(1.f).add_max(1000.f).set_scroll_speed(10)
		.add_click([] { if (menu::player::get_local_player().m_weapon_hash) native::set_player_weapon_defense_modifier(menu::player::get_local_player().m_id, 1.f); }).add_savable(get_submenu_name_stack()));
}

void weapon_multipliers_menu::update() {}

void weapon_multipliers_menu::update_once() {}

void weapon_multipliers_menu::feature_update() {
	if (menu::player::get_local_player().m_has_weapon_in_hand) {
		if (m_vars.m_weapon_damage_multiplier) {
			native::set_player_weapon_damage_modifier(menu::player::get_local_player().m_id, m_vars.m_weapon_damage_multiplier_val);
		}

		if (m_vars.m_melee_damage_multiplier) {
			native::set_player_melee_weapon_damage_modifier(menu::player::get_local_player().m_id, m_vars.m_melee_damage_multiplier_val, 1);
		}

		if (m_vars.m_defense_damage_multiplier) {
			native::set_player_weapon_defense_modifier(menu::player::get_local_player().m_id, m_vars.m_defense_damage_multiplier_val);
		}
	}
}

weapon_multipliers_menu* g_instance;
weapon_multipliers_menu* weapon_multipliers_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new weapon_multipliers_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
