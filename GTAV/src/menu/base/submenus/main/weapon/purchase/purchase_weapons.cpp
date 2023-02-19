#include "purchase_weapons.h"
#include "menu/base/submenu_handler.h"
#include "purchase_weapon.h"
#include "purchase_attachment.h"
#include "../give_weapons_ammo.h"

void purchase_weapons_menu::load() {
	set_name("Purchase Weapons");
	set_parent<give_weapons_ammo_menu>();

	add_option(submenu_option("Purchase Weapon")
		.add_translate().add_hotkey()
		.add_submenu<purchase_weapon_menu>());

	add_option(submenu_option("Purchase Attachment")
		.add_translate().add_hotkey()
		.add_submenu<purchase_attachment_menu>());
}

void purchase_weapons_menu::update() {}

void purchase_weapons_menu::update_once() {}

void purchase_weapons_menu::feature_update() {}

purchase_weapons_menu* g_instance;
purchase_weapons_menu* purchase_weapons_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new purchase_weapons_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}