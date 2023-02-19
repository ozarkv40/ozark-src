#include "ammo_modifier_swap.h"
#include "menu/base/submenu_handler.h"
#include "ammo_modifier_edit.h"
#include "global/lists.h"

using namespace weapon::ammo::swap::vars;

namespace weapon::ammo::swap::vars {
	variables m_vars;

	void swap(uint32_t first, uint32_t second) {
		uint64_t table = *(uint64_t*)global::vars::g_weapon_info.m_list;
		if (table) {
			rage::types::weapon_info* first_ptr = nullptr;
			rage::types::weapon_info* second_ptr = nullptr;

			for (int16_t i = 0; i < (*(int16_t*)global::vars::g_weapon_info.m_count) - 1; i++) {
				rage::types::weapon_info* ptr = (rage::types::weapon_info*) * (uint64_t*)(table + (i * 8));
				if (ptr) {
					if (ptr->m_name_hash == first) {
						first_ptr = ptr;
						break;
					}
				}
			}

			for (int16_t i = 0; i < (*(int16_t*)global::vars::g_weapon_info.m_count) - 1; i++) {
				rage::types::weapon_info* ptr = (rage::types::weapon_info*) * (uint64_t*)(table + (i * 8));
				if (ptr) {
					if (ptr->m_name_hash == second) {
						second_ptr = ptr;
						break;
					}
				}
			}

			if (first_ptr && second_ptr) {
				auto vit = std::find_if(weapon::ammo::edit::vars::m_vars.m_modifiers.begin(), weapon::ammo::edit::vars::m_vars.m_modifiers.end(), [=](weapon::ammo::edit::vars::EditContext& Context) {
					return Context.m_hash == first;
				});

				if (vit == weapon::ammo::edit::vars::m_vars.m_modifiers.end()) {
					weapon::ammo::edit::vars::m_vars.m_modifiers.push_back({ first_ptr->m_ammo_info, first_ptr->m_aiming_info, first_ptr->m_fire_type, first_ptr->m_audio, first, second });
				}

				int ammo = -1;
				native::get_max_ammo(menu::player::get_local_player().m_ped, first, &ammo);

				first_ptr->m_ammo_info = second_ptr->m_ammo_info;
				first_ptr->m_aiming_info = second_ptr->m_aiming_info;
				first_ptr->m_fire_type = second_ptr->m_fire_type;
				first_ptr->m_audio = second_ptr->m_audio;

				native::add_ammo_to_ped(menu::player::get_local_player().m_ped, first, ammo);
				native::give_weapon_to_ped(menu::player::get_local_player().m_ped, second, ammo, false, false);
			}
		}
	}
}

void ammo_modifier_swap_menu::load() {
	set_name("Swap With...");
	set_parent<ammo_modifier_edit_menu>();

	for (scroll_struct<uint32_t> weapon : global::lists::g_weapons) {
		add_option(button_option(weapon.m_name.get())
			.add_click([=] {
				swap(weapon::ammo::edit::vars::m_vars.m_current_hash, weapon.m_result);
				menu::submenu::handler::set_submenu_previous();
			}));
	}
}

void ammo_modifier_swap_menu::update() {}

void ammo_modifier_swap_menu::update_once() {}

void ammo_modifier_swap_menu::feature_update() {}

ammo_modifier_swap_menu* g_instance;
ammo_modifier_swap_menu* ammo_modifier_swap_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new ammo_modifier_swap_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}