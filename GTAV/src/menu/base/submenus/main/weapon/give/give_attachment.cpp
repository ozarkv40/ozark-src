#include "give_attachment.h"
#include "menu/base/submenu_handler.h"
#include "give_weapons.h"
#include "../purchase/purchase_weapon.h"
#include "rage/engine.h"
#include "global/lists.h"
#include "give_weapon.h"
#include "give_attachment_selected.h"
#include "menu/base/util/notify.h"

using namespace weapon::give::attachment::vars;

namespace weapon::give::attachment::vars {
	variables m_vars;

	scroll_struct<int> give_all[] = {
		{ localization("Current", true), 0 },
		{ localization("All", true), 1 }
	};

	bool does_weapon_have_components(uint32_t weapon) {
		int count = 0;
		uint32_t last_component = 0;

		auto hashes = rage::engine::get_hash_list_from_hash_table(*(uint32_t*)(global::vars::g_weapon_components.m_count) - 1, global::vars::g_weapon_components.m_list);
		for (uint32_t component : hashes) {
			if (native::does_weapon_take_weapon_component(weapon, component)) {
				count++;
				last_component = component;
			}
		}

		if (count) {
			if (count == 1) {
				if (!strcmp(weapon::purchase::weapon::vars::scripts::func_181(last_component, weapon), "NULL")) {
					return false;
				}
			}

			return true;
		}

		return false;
	}

	void do_give_all(give_attachment_menu* _this, bool remove) {
		if (remove) {
			if (m_vars.m_remove_all == 0) {
				if (menu::player::get_local_player().m_has_weapon_in_hand) {
					weapon::give::vars::remove_weapon_upgrades(menu::player::get_local_player().m_ped, menu::player::get_local_player().m_weapon_hash);
				} else {
					menu::notify::stacked(_this->get_string("Remove Attachments"), _this->get_string("You don't have a weapon in hand"), global::ui::g_error);
				}

				return;
			}

			for (scroll_struct<uint32_t> weapon : global::lists::g_weapons) {
				weapon::give::vars::remove_weapon_upgrades(menu::player::get_local_player().m_ped, weapon.m_result);
			}

			return;
		}

		if (m_vars.m_give_all == 0) {
			if (menu::player::get_local_player().m_has_weapon_in_hand) {
				weapon::give::vars::upgrade_weapon_components(menu::player::get_local_player().m_ped, menu::player::get_local_player().m_weapon_hash);
			} else {
				menu::notify::stacked(_this->get_string("Give Attachments"), _this->get_string("You don't have a weapon in hand"), global::ui::g_error);
			}

			return;
		}

		for (scroll_struct<uint32_t> weapon : global::lists::g_weapons) {
			weapon::give::vars::upgrade_weapon_components(menu::player::get_local_player().m_ped, weapon.m_result);
		}
	}
}

void give_attachment_menu::load() {
	set_name("Give Attachment");
	set_parent<give_weapons_menu>();

	add_string("Remove Attachments");
	add_string("Give Attachments");
	add_string("You don't have a weapon in hand");

	add_option(scroll_option<int>(SCROLLSELECT, "Give All Attachments")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_give_all, 0, NUMOF(give_all), give_all)
		.add_click([this] { do_give_all(this, false); }));

	add_option(scroll_option<int>(SCROLLSELECT, "Remove All Attachments")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_remove_all, 0, NUMOF(give_all), give_all)
		.add_click([this] { do_give_all(this, true); }));

	add_option(submenu_option("Current Weapon")
		.add_translate().add_hotkey()
		.add_click([] { weapon::give::attachment::selected::vars::m_vars.m_selected_weapon = menu::player::get_local_player().m_weapon_hash; })
		.add_submenu<give_attachment_selected_menu>()
		.add_requirement([] { return menu::player::get_local_player().m_has_weapon_in_hand && does_weapon_have_components(menu::player::get_local_player().m_weapon_hash); }));

	add_option(break_option("Weapons")
		.add_translate());
}

void give_attachment_menu::update() {}

void give_attachment_menu::update_once() {
	clear_options(4);

	for (scroll_struct<uint32_t> weapon : global::lists::g_weapons) {
		if (does_weapon_have_components(weapon.m_result)) {
			add_option(submenu_option(weapon.m_name.get())
				.add_click([=] { weapon::give::attachment::selected::vars::m_vars.m_selected_weapon = weapon.m_result; })
				.add_submenu<give_attachment_selected_menu>());
		}
	}
}

void give_attachment_menu::feature_update() {}

give_attachment_menu* g_instance;
give_attachment_menu* give_attachment_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new give_attachment_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
