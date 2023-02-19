#include "give_weapon.h"
#include "menu/base/submenu_handler.h"
#include "give_weapons.h"
#include "rage/engine.h"
#include "global/lists.h"

using namespace weapon::give::vars;

namespace weapon::give::vars {
	variables m_vars;

	void upgrade_weapon_components(Ped ped, uint32_t weapon_hash) {
		std::vector<uint32_t> hashes = rage::engine::get_hash_list_from_hash_table(*(uint32_t*)(global::vars::g_weapon_components.m_count) - 1, global::vars::g_weapon_components.m_list);
		for (uint32_t component : hashes) {
			if (native::does_weapon_take_weapon_component(weapon_hash, component)) {
				native::give_weapon_component_to_ped(ped, weapon_hash, component);
			}
		}
	}

	void remove_weapon_upgrades(Ped ped, uint32_t weapon_hash) {
		std::vector<uint32_t> hashes = rage::engine::get_hash_list_from_hash_table(*(uint32_t*)(global::vars::g_weapon_components.m_count) - 1, global::vars::g_weapon_components.m_list);
		for (uint32_t component : hashes) {
			if (native::does_weapon_take_weapon_component(weapon_hash, component)) {
				native::remove_weapon_component_from_ped(ped, weapon_hash, component);
			}
		}
	}

	void give_weapon(Ped ped, uint32_t weapon_hash, bool equip_now, bool fully_upgraded) {
		int ammo = -1;
		native::get_max_ammo(ped, weapon_hash, &ammo);
		native::give_weapon_to_ped(ped, weapon_hash, ammo, false, equip_now);

		if (fully_upgraded) {
			upgrade_weapon_components(ped, weapon_hash);
		}
	}
}

void give_weapon_menu::load() {
	set_name("Give Weapon");
	set_parent<give_weapons_menu>();

	add_option(toggle_option("Give All Weapons (Persistent)")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_give_weapons)
		.add_click([] {
			if (m_vars.m_give_weapons) {
				for (scroll_struct<uint32_t> weapon : global::lists::g_weapons) {
					give_weapon(menu::player::get_local_player().m_ped, weapon.m_result, false, false);
				}
			}
		}).add_savable(get_submenu_name_stack())
		.add_tooltip("When toggled, weapons are reapplied on model change and session change"));

	add_option(break_option("Weapons")
		.add_translate());

	if (m_vars.m_give_weapons) {
		for (scroll_struct<uint32_t> weapon : global::lists::g_weapons) {
			give_weapon(menu::player::get_local_player().m_ped, weapon.m_result, false, false);
		}
	}
}

void give_weapon_menu::update() {}

void give_weapon_menu::update_once() {
	clear_options(2);

	for (scroll_struct<uint32_t> weapon : global::lists::g_weapons) {
		add_option(button_option(weapon.m_name.get())
			.add_click([=] { give_weapon(menu::player::get_local_player().m_ped, weapon.m_result, true, false); })
			.add_update([=](button_option* option) {
				if (native::has_ped_got_weapon(menu::player::get_local_player().m_ped, weapon.m_result, false)) {
					option->add_sprite({ "commonmenu", "shop_gunclub_icon" });
					option->add_sprite_scale({ 0.02112f, 0.03744f });
				} else option->remove_sprite();
			}));
	}
}

void give_weapon_menu::feature_update() {
	if (m_vars.m_give_weapons) {
		if (global::vars::g_reapply_weapons) {
			global::vars::g_reapply_weapons = false;

			for (scroll_struct<uint32_t> weapon : global::lists::g_weapons) {
				give_weapon(menu::player::get_local_player().m_ped, weapon.m_result, false, false);
			}
		}
	}
}

give_weapon_menu* g_instance;
give_weapon_menu* give_weapon_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new give_weapon_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
