#include "give_weapons.h"
#include "menu/base/submenu_handler.h"
#include "../weapon_mods.h"
#include "give_weapon.h"
#include "give_attachment.h"
#include "give_tint.h"
#include "../give_weapons_ammo.h"

void give_weapons_menu::load() {
	set_name("Give Weapons");
	set_parent<give_weapons_ammo_menu>();

	add_option(submenu_option("Give Weapon")
		.add_translate().add_hotkey()
		.add_submenu<give_weapon_menu>());

	add_option(submenu_option("Give Attachment")
		.add_translate().add_hotkey()
		.add_submenu<give_attachment_menu>());

	add_option(submenu_option("Give Tint")
		.add_translate().add_hotkey()
		.add_submenu<give_tint_menu>());
}

void give_weapons_menu::update() {}

void give_weapons_menu::update_once() {}

void give_weapons_menu::feature_update() {}

give_weapons_menu* g_instance;
give_weapons_menu* give_weapons_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new give_weapons_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}