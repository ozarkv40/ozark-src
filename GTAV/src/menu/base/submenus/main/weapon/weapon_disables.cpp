#include "weapon_disables.h"
#include "menu/base/submenu_handler.h"
#include "weapon_mods.h"
#include "weapon_modifiers.h"

using namespace weapon::disables::vars;

namespace weapon::disables::vars {
	variables m_vars;

	void disable_weapon_limits() {
		if (m_vars.m_disable_vehicle_weapon_limits) m_vars.m_weapon_groups.clear();

		uint64_t table = *(uint64_t*)global::vars::g_weapon_info.m_list;
		if (table) {
			for (int16_t i = 0; i < (*(int16_t*)global::vars::g_weapon_info.m_count) - 1; i++) {
				rage::types::weapon_info* ptr = (rage::types::weapon_info*) * (uint64_t*)(table + (i * 8));
				if (ptr) {
					if (!m_vars.m_disable_vehicle_weapon_limits) {
						auto vit = std::find_if(m_vars.m_weapon_groups.begin(), m_vars.m_weapon_groups.end(), [=](std::pair<uint32_t, uint32_t>& element) {
							return element.first == ptr->m_name_hash;
						});

						if (vit != m_vars.m_weapon_groups.end()) {
							ptr->m_group_hash = vit->second;
						}
					} else {
						uint32_t weapon_groups[] = {
							0x18d5fa97,
							0xc6e9a5c5,
							0x39d5c192,
							0x451b04bc,
							0x33431399,
							0xb7bbd827,
							0xa27a4f9f,
							0x29268262,
							0xfdbf656c
						};

						for (uint32_t hash : weapon_groups) {
							if (ptr->m_group_hash == hash) {
								m_vars.m_weapon_groups.push_back({ ptr->m_name_hash, ptr->m_group_hash });
								ptr->m_group_hash = 0x18d5fa97; // set to a pistol
								break;
							}
						}
					}
				}
			}
		}
	}
}

void weapon_disables_menu::load() {
	set_name("Disables");
	set_parent<weapon_mods_menu>();

	add_option(toggle_option("Disable Vehicle Restrictions")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_vehicle_weapon_limits)
		.add_click(disable_weapon_limits).add_savable(get_submenu_name_stack())
		.add_tooltip("Disables not being able to use any weapon in vehicles"));

	add_option(toggle_option("Disable Passive Restrictions")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_passive_weapons).add_savable(get_submenu_name_stack())
		.add_tooltip("Allows you to use weapons while in passive"));

	add_option(toggle_option("Disable Interior Restrictions")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_interior_weapons).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Orbital Cooldown")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_orbital_cooldown).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Disable Spread")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_spread).add_savable(get_submenu_name_stack())
		.add_click([] {
		if (!m_vars.m_disable_spread) {
			if (weapon::modifiers::vars::get_weapon_info()) {
				if (m_vars.m_original_spread.find(weapon::modifiers::vars::get_weapon_info()) != m_vars.m_original_spread.end()) {
					weapon::modifiers::vars::get_weapon_info()->m_batch_spread = m_vars.m_original_spread[weapon::modifiers::vars::get_weapon_info()].first;
					weapon::modifiers::vars::get_weapon_info()->m_accuracy_spread = m_vars.m_original_spread[weapon::modifiers::vars::get_weapon_info()].second;
				}
			}
		}
	}));

	add_option(toggle_option("Disable Recoil")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_recoil).add_savable(get_submenu_name_stack())
		.add_click([] {
		if (!m_vars.m_disable_recoil) {
			if (weapon::modifiers::vars::get_weapon_info()) {
				if (m_vars.m_original_recoil.find(weapon::modifiers::vars::get_weapon_info()) != m_vars.m_original_recoil.end()) {
					weapon::modifiers::vars::get_weapon_info()->m_recoil_shake_amptitude = m_vars.m_original_recoil[weapon::modifiers::vars::get_weapon_info()];
				}
			}
		}
	}));

	add_option(toggle_option("Disable Cooldown")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_cooldown).add_savable(get_submenu_name_stack())
		.add_click([] {
		if (!m_vars.m_disable_cooldown) {
			if (weapon::modifiers::vars::get_weapon_info()) {
				if (m_vars.m_original_time_between_shots.find(weapon::modifiers::vars::get_weapon_info()) != m_vars.m_original_time_between_shots.end()) {
					weapon::modifiers::vars::get_weapon_info()->m_time_between_shots = m_vars.m_original_time_between_shots[weapon::modifiers::vars::get_weapon_info()];
				}
			}
		}
	}));

	add_option(toggle_option("Disable Spin Time")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_spin).add_savable(get_submenu_name_stack())
		.add_click([] {
		if (!m_vars.m_disable_spin) {
			if (weapon::modifiers::vars::get_weapon_info()) {
				if (m_vars.m_original_instant_spin.find(weapon::modifiers::vars::get_weapon_info()) != m_vars.m_original_instant_spin.end()) {
					weapon::modifiers::vars::get_weapon_info()->m_spin_up_time = m_vars.m_original_instant_spin[weapon::modifiers::vars::get_weapon_info()].first;
					weapon::modifiers::vars::get_weapon_info()->m_spin_down_time = m_vars.m_original_instant_spin[weapon::modifiers::vars::get_weapon_info()].second;
				}
			}
		}
	}));

	add_option(toggle_option("Disable Reload Anim")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_instant_reload).add_savable(get_submenu_name_stack())
		.add_click([] {
			if (!m_vars.m_instant_reload) {
				if (weapon::modifiers::vars::get_weapon_info()) {
					if (m_vars.m_original_anim_reload_rate.find(weapon::modifiers::vars::get_weapon_info()) != m_vars.m_original_anim_reload_rate.end()) {
						weapon::modifiers::vars::get_weapon_info()->m_anim_reload_rate = m_vars.m_original_anim_reload_rate[weapon::modifiers::vars::get_weapon_info()];
					}
				}
			}
		}));
}

void weapon_disables_menu::update() {}

void weapon_disables_menu::update_once() {}

void weapon_disables_menu::feature_update() {
	if (menu::player::get_local_player().m_has_weapon_in_hand) {
		if (m_vars.m_instant_reload) {
			rage::types::weapon_info* weapon_info = weapon::modifiers::vars::get_weapon_info();
			if (weapon_info) {
				if (weapon_info->m_name_hash != 0xb1ca77b1
					&& weapon_info->m_name_hash != 0x7f7497e5
					&& weapon_info->m_name_hash != 0x63ab0442) {
					if (m_vars.m_original_anim_reload_rate.find(weapon::modifiers::vars::get_weapon_info()) == m_vars.m_original_anim_reload_rate.end()) {
						m_vars.m_original_anim_reload_rate[weapon_info] = weapon_info->m_anim_reload_rate;
					}

					weapon_info->m_anim_reload_rate = 100.f;
				}
			}
		}

		if (m_vars.m_disable_spread) {
			rage::types::weapon_info* weapon_info = weapon::modifiers::vars::get_weapon_info();
			if (weapon_info) {
				if (m_vars.m_original_spread.find(weapon::modifiers::vars::get_weapon_info()) == m_vars.m_original_spread.end()) {
					m_vars.m_original_spread[weapon_info].first = weapon_info->m_batch_spread;
					m_vars.m_original_spread[weapon_info].second = weapon_info->m_accuracy_spread;
				}

				weapon_info->m_batch_spread = 0.f;
				weapon_info->m_accuracy_spread = 0.f;
			}
		}

		if (m_vars.m_disable_recoil) {
			rage::types::weapon_info* weapon_info = weapon::modifiers::vars::get_weapon_info();
			if (weapon_info) {
				if (m_vars.m_original_recoil.find(weapon::modifiers::vars::get_weapon_info()) == m_vars.m_original_recoil.end()) {
					m_vars.m_original_recoil[weapon_info] = weapon_info->m_recoil_shake_amptitude;
				}

				weapon_info->m_recoil_shake_amptitude = 0.f;
			}
		}

		if (m_vars.m_disable_cooldown) {
			if (menu::player::get_local_player().m_weapon_hash == 0x6d544c99
				|| menu::player::get_local_player().m_weapon_hash == 0xaf3696a1
				|| menu::player::get_local_player().m_weapon_hash == 0x3656c8c1) {
				rage::types::weapon_info* weapon_info = weapon::modifiers::vars::get_weapon_info();
				if (weapon_info) {
					if (m_vars.m_original_time_between_shots.find(weapon::modifiers::vars::get_weapon_info()) == m_vars.m_original_time_between_shots.end()) {
						m_vars.m_original_time_between_shots[weapon_info] = weapon_info->m_time_between_shots;
					}

					weapon_info->m_time_between_shots = 0.f;
				}
			}
		}

		if (m_vars.m_disable_spin) {
			if (menu::player::get_local_player().m_weapon_hash == 0x42bf8a85) {
				rage::types::weapon_info* weapon_info = weapon::modifiers::vars::get_weapon_info();
				if (weapon_info) {
					if (m_vars.m_original_instant_spin.find(weapon::modifiers::vars::get_weapon_info()) == m_vars.m_original_instant_spin.end()) {
						m_vars.m_original_instant_spin[weapon_info].first = weapon_info->m_spin_up_time;
						m_vars.m_original_instant_spin[weapon_info].second = weapon_info->m_spin_down_time;
					}

					weapon_info->m_spin_up_time = 0.f;
					weapon_info->m_spin_down_time = 0.f;
				}
			}
		}
	}
}

weapon_disables_menu* g_instance;
weapon_disables_menu* weapon_disables_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new weapon_disables_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
