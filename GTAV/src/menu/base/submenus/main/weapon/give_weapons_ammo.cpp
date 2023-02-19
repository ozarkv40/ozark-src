#include "give_weapons_ammo.h"
#include "menu/base/submenu_handler.h"
#include "weapon_mods.h"
#include "global/lists.h"
#include "purchase/purchase_weapons.h"
#include "give/give_weapons.h"
#include "weapon_mods.h"
#include "give/give_weapon.h"

void give_weapons_ammo_menu::load() {
	set_name("Give Weapons and Ammo");
	set_parent<weapon_mods_menu>();

	add_option(submenu_option("Give Weapons")
		.add_translate().add_hotkey()
		.add_submenu<give_weapons_menu>());

	add_option(submenu_option("Purchase Weapons")
		.add_translate().add_hotkey()
		.add_submenu<purchase_weapons_menu>());

	add_option(button_option("Give All Weapons")
		.add_translate().add_hotkey()
		.add_click([] {
			for (scroll_struct<uint32_t> weapon : global::lists::g_weapons) {
				weapon::give::vars::give_weapon(menu::player::get_local_player().m_ped, weapon.m_result, false, false);
			}
		}));

	add_option(button_option("Max Weapon Ammo")
		.add_translate().add_hotkey()
		.add_click([] {
			for (scroll_struct<uint32_t> weapon : global::lists::g_weapons) {
				int ammo = -1;
				native::get_max_ammo(menu::player::get_local_player().m_ped, weapon.m_result, &ammo);
				native::add_ammo_to_ped(menu::player::get_local_player().m_ped, weapon.m_result, ammo);
			}
		}));
}

void give_weapons_ammo_menu::update() {}

void give_weapons_ammo_menu::update_once() {}

void give_weapons_ammo_menu::feature_update() {}

give_weapons_ammo_menu* g_instance;
give_weapons_ammo_menu* give_weapons_ammo_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new give_weapons_ammo_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}