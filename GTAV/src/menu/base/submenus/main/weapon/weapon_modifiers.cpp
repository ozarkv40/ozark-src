#include "weapon_modifiers.h"
#include "menu/base/submenu_handler.h"
#include "weapon_mods.h"
#include "modifiers/weapon_multipliers.h"
#include "modifiers/weapon_matrix.h"
#include "modifiers/ammo/ammo_modifier.h"

using namespace weapon::modifiers::vars;

namespace weapon::modifiers::vars {
	variables m_vars;

	rage::types::weapon_info* get_weapon_info() {
		rage::types::ped* ped = global::vars::g_ped_factory->m_local_ped;
		if (ped) {
			rage::types::ped_weapon_manager* weapon_manager = ped->m_ped_weapon_manager;
			if (weapon_manager) {
				return weapon_manager->m_weapon_info;
			}
		}

		return nullptr;
	}
}

void weapon_modifiers_menu::load() {
	set_name("Modifiers");
	set_parent<weapon_mods_menu>();

	add_option(submenu_option("Ammo")
		.add_translate().add_hotkey()
		.add_submenu<ammo_modifier_menu>());

	add_option(submenu_option("Multipliers")
		.add_translate().add_hotkey()
		.add_submenu<weapon_multipliers_menu>());

	add_option(submenu_option("Matrix")
		.add_translate().add_hotkey()
		.add_submenu<weapon_matrix_menu>());
}

void weapon_modifiers_menu::update() {}

void weapon_modifiers_menu::update_once() {}

void weapon_modifiers_menu::feature_update() {}

weapon_modifiers_menu* g_instance;
weapon_modifiers_menu* weapon_modifiers_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new weapon_modifiers_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
