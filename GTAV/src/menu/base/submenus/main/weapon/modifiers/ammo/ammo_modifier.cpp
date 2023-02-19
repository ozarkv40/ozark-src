#include "ammo_modifier.h"
#include "menu/base/submenu_handler.h"
#include "../../weapon_modifiers.h"
#include "global/lists.h"
#include "ammo_modifier_edit.h"
#include "ammo_modifier_load.h"

using namespace weapon::ammo::vars;

namespace weapon::ammo::vars {
	variables m_vars;

	void reset() {
		for (auto& modifier : edit::vars::m_vars.m_modifiers) {
			edit::vars::reset_modifier(modifier.m_hash);
		}
	}

	bool has_existing_modifier(uint32_t hash) {
		for (auto& modifier : edit::vars::m_vars.m_modifiers) {
			if (modifier.m_hash == hash) return true;
		}

		return false;
	}
}

void ammo_modifier_menu::load() {
	set_name("Ammo Modifier");
	set_parent<weapon_modifiers_menu>();

	add_option(submenu_option("Load Modifier")
		.add_translate().add_hotkey()
		.add_submenu<ammo_modifier_load_menu>());

	add_option(button_option("Reset All Modifiers")
		.add_translate().add_hotkey()
		.add_click(reset));

	add_option(submenu_option("Current Weapon")
		.add_translate().add_hotkey()
		.add_submenu<ammo_modifier_edit_menu>()
		.add_click([] {
			weapon::ammo::edit::vars::m_vars.m_current_hash = menu::player::get_local_player().m_weapon_hash;
		})
		.add_requirement([] { return menu::player::get_local_player().m_weapon_hash && menu::player::get_local_player().m_weapon_hash != 2725352035; }));

	add_option(break_option("All Weapons")
		.add_translate());

	for (scroll_struct<uint32_t>& weapon : global::lists::g_weapons) {
		add_option(button_option(weapon.m_name.get())
			.add_sprite({ "commonmenu", "shop_ammo_icon" }, [=] { return has_existing_modifier(weapon.m_result); })
			.add_click([=] {
				weapon::ammo::edit::vars::m_vars.m_current_hash = weapon.m_result;
				menu::submenu::handler::set_submenu(ammo_modifier_edit_menu::get());
			}));
	}
}

void ammo_modifier_menu::update() {}

void ammo_modifier_menu::update_once() {}

void ammo_modifier_menu::feature_update() {}

ammo_modifier_menu* g_instance;
ammo_modifier_menu* ammo_modifier_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new ammo_modifier_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
