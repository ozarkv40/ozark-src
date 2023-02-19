#include "network_account_outfits.h"
#include "menu/base/submenu_handler.h"
#include "../network_account.h"
#include "menu/base/util/global.h"
#include "outfits/network_account_outfits_edit.h"
#include "rage/types/global_types.h"

using namespace network::account::outfits::vars;

namespace network::account::outfits::vars {
	variables m_vars;

	bool does_outfit_slot_exist(int outfit_index) {
		return menu::script_global(rage::global::_155_outfit_editor_base).at(rage::global::_155_outfit_editor_base_offset).at(rage::global::_155_outfit_editor_offset_5).at(outfit_index).at(2).as<bool>();
	}

	char* get_outfit_slot_name_ptr(int outfit_index) {
		return menu::script_global(rage::global::_155_outfit_editor_base).at(rage::global::_155_outfit_editor_base_offset).at(rage::global::_155_outfit_editor_offset_6).at(outfit_index, 8).at(1).get<char>();
	}

	int get_max_slots() {
		return menu::script_global(rage::global::_155_outfit_editor_base2).at(rage::global::_155_outfit_editor_base2_offset).as<int>();
	}

	int get_free_slots() {
		int count = 0;

		for (int i = 0; i < get_max_slots(); i++) {
			if (does_outfit_slot_exist(i)) {
				if (!native::is_string_null_or_empty(get_outfit_slot_name_ptr(i))) {
					continue;
				}
			}

			count++;
		}

		return count;
	}

	int get_free_slot_index() {
		for (int i = 0; i < get_max_slots(); i++) {
			if (native::is_string_null_or_empty(get_outfit_slot_name_ptr(i))) {
				return i;
			}
		}

		return -1;
	}

	void delete_slot(int slot) {
		menu::script_global(rage::global::_155_outfit_editor_base).at(rage::global::_155_outfit_editor_base_offset).at(rage::global::_155_outfit_editor_offset_5).at(slot).at(2).as<int>() = 0;
		*get_outfit_slot_name_ptr(slot) = 0;
	}

	void save_outfit_edit() {
		native::stat_save(0, false, 3);
	}
}

void network_account_outfits_menu::load() {
	set_name("Outfits");
	set_parent<network_account_menu>();

	add_string("Create Outfit");
	add_string("Outfits");
	add_string("New Outfit");
	add_string("~m~None");

	network_account_outfits_edit_menu::get();
}

void network_account_outfits_menu::update() {}

void network_account_outfits_menu::update_once() {
	clear_options(0);

	if (get_free_slots()) {
		add_option(submenu_option(get_string("Create Outfit"))
			.add_click([this] {
				network_account_outfits_edit_menu::get()->set_name(get_string("New Outfit"), false, false);
				network::account::outfits::edit::vars::m_vars.m_slot = get_free_slot_index();
			})
			.add_submenu<network_account_outfits_edit_menu>());

		add_option(break_option(get_string("Outfits")));
	}

	bool valid = false;
	for (int i = 0; i < get_max_slots(); i++) {
		if (does_outfit_slot_exist(i)) {
			char* name = get_outfit_slot_name_ptr(i);
			if (name) {
				if (!native::is_string_null_or_empty(name)) {
					valid = true;

					add_option(submenu_option(name)
						.add_submenu<network_account_outfits_edit_menu>()
						.add_click([=] {
							network_account_outfits_edit_menu::get()->set_name(name, false, false);
							network::account::outfits::edit::vars::m_vars.m_slot = i;
						}));
				}
			}
		}
	}

	if (!valid) {
		add_option(button_option(get_string("~m~None")).ref());
	}
}

void network_account_outfits_menu::feature_update() {}

network_account_outfits_menu* g_instance;
network_account_outfits_menu* network_account_outfits_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_account_outfits_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}