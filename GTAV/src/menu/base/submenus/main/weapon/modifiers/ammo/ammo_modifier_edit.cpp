#include "ammo_modifier_edit.h"
#include "menu/base/submenu_handler.h"
#include "ammo_modifier.h"
#include "../../weapon_modifiers.h"
#include "ammo_modifier_load.h"
#include "ammo_modifier_swap.h"

using namespace weapon::ammo::edit::vars;

namespace weapon::ammo::edit::vars {
	variables m_vars;

	void reset_modifier(uint32_t hash) {
		auto vit = std::find_if(m_vars.m_modifiers.begin(), m_vars.m_modifiers.end(), [=](EditContext& Context) {
			return Context.m_hash == hash;
		});

		if (vit != m_vars.m_modifiers.end()) {
			uint64_t table = *(uint64_t*)global::vars::g_weapon_info.m_list;
			if (table) {
				for (int16_t i = 0; i < (*(int16_t*)global::vars::g_weapon_info.m_count) - 1; i++) {
					rage::types::weapon_info* ptr = (rage::types::weapon_info*) * (uint64_t*)(table + (i * 8));
					if (ptr) {
						if (ptr->m_name_hash == hash) {
							ptr->m_ammo_info = vit->m_ammo_info;
							ptr->m_aiming_info = vit->m_aiming_info;
							ptr->m_fire_type = vit->m_fire_type;
							ptr->m_audio = vit->m_audio;
							break;
						}
					}
				}
			}

			m_vars.m_modifiers.erase(vit);
		}

	}

	rage::types::weapon_info* get_active_weapon() {
		if (m_vars.m_current_hash == menu::player::get_local_player().m_weapon_hash) return weapon::modifiers::vars::get_weapon_info();

		uint64_t table = *(uint64_t*)global::vars::g_weapon_info.m_list;
		if (table) {
			for (int16_t i = 0; i < (*(int16_t*)global::vars::g_weapon_info.m_count) - 1; i++) {
				rage::types::weapon_info* ptr = (rage::types::weapon_info*) * (uint64_t*)(table + (i * 8));
				if (ptr) {
					if (ptr->m_name_hash == m_vars.m_current_hash) {
						return ptr;
					}
				}
			}
		}

		return nullptr;
	}
}

void ammo_modifier_edit_menu::load() {
	set_name("Ammo Modifier");
	set_parent<ammo_modifier_menu>();

	add_option(button_option("Save Modifier")
		.add_keyboard("Enter modifier name", 100, [](button_option* _this, const char* Name) { weapon::ammo::load::vars::save_modifier(Name, m_vars.m_current_hash); }));

	add_option(button_option("Reset Modifier")
		.add_translate()
		.add_click([] { reset_modifier(m_vars.m_current_hash); }));

	add_option(submenu_option("Bullet Swap")
		.add_translate()
		.add_submenu<ammo_modifier_swap_menu>());

	add_option(number_option<float>(SCROLL, "Damage")
		.add_translate()
		.add_number(m_vars.m_damage, "%.0f", 1.f).set_scroll_speed(5).add_min(1.f).add_max(10000.f)
		.add_click([] {
			rage::types::weapon_info* weapon = get_active_weapon();
			if (weapon) {
				weapon->m_damage = m_vars.m_damage;
			}
		})
		.add_requirement([] { return get_active_weapon() != nullptr; })
		.add_tooltip("~y~Notice: ~w~Won't reset with Reset option"));

	add_option(number_option<float>(SCROLL, "Force")
		.add_translate()
		.add_number(m_vars.m_force, "%.0f", 1.f).set_scroll_speed(5).add_min(1.f).add_max(10000.f)
		.add_click([] {
			rage::types::weapon_info* weapon = get_active_weapon();
			if (weapon) {
				weapon->m_force = m_vars.m_force;
			}
		})
		.add_requirement([] { return get_active_weapon() != nullptr; })
		.add_tooltip("~y~Notice: ~w~Won't reset with Reset option"));

	add_option(number_option<float>(SCROLL, "Speed")
		.add_translate()
		.add_number(m_vars.m_speed, "%.0f", 1.f).set_scroll_speed(5).add_min(1.f).add_max(10000.f)
		.add_click([] {
			rage::types::weapon_info* weapon = get_active_weapon();
			if (weapon) {
				weapon->m_speed = m_vars.m_speed;
			}
		})
		.add_requirement([] { return get_active_weapon() != nullptr; })
		.add_tooltip("~y~Notice: ~w~Won't reset with Reset option"));
}

void ammo_modifier_edit_menu::update() {
	rage::types::weapon_info* active = get_active_weapon();
	if (active == nullptr) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	if (m_vars.m_cached_weapon != active) {
		m_vars.m_current_hash = menu::player::get_local_player().m_weapon_hash;
		m_vars.m_cached_weapon = active;
		if (m_vars.m_cached_weapon) {
			m_vars.m_damage = m_vars.m_cached_weapon->m_damage;
			m_vars.m_force = m_vars.m_cached_weapon->m_force;
			m_vars.m_speed = m_vars.m_cached_weapon->m_speed;
		}
	}
}

void ammo_modifier_edit_menu::update_once() {}

void ammo_modifier_edit_menu::feature_update() {}

ammo_modifier_edit_menu* g_instance;
ammo_modifier_edit_menu* ammo_modifier_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new ammo_modifier_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
