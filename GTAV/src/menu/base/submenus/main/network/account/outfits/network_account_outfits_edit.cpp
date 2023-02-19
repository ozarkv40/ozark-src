#include "network_account_outfits_edit.h"
#include "menu/base/submenu_handler.h"
#include "../network_account_outfits.h"
#include "menu/base/submenus/main/player/wardrobe.h"
#include "menu/base/util/global.h"
#include "network_account_outfits_edit_name.h"
#include "rage/types/global_types.h"

using namespace network::account::outfits::edit::vars;

namespace network::account::outfits::edit::vars {
	variables m_vars;

	void set_accessory_model(int slot, int index, int value) {
		menu::script_global(rage::global::_155_outfit_editor_base).at(rage::global::_155_outfit_editor_base_offset).at(rage::global::_155_outfit_editor_offset_1).at(slot, 10).at(index).at(2).as<int>() = value;
	}

	void set_accessory_variation(int slot, int index, int value) {
		menu::script_global(rage::global::_155_outfit_editor_base).at(rage::global::_155_outfit_editor_base_offset).at(rage::global::_155_outfit_editor_offset_2).at(slot, 10).at(index).at(2).as<int>() = value;
	}

	void set_clothing_model(int slot, int index, int value) {
		menu::script_global(rage::global::_155_outfit_editor_base).at(rage::global::_155_outfit_editor_base_offset).at(rage::global::_155_outfit_editor_offset_3).at(slot, 13).at(index).at(2).as<int>() = value;
	}

	void set_clothing_variation(int slot, int index, int value) {
		menu::script_global(rage::global::_155_outfit_editor_base).at(rage::global::_155_outfit_editor_base_offset).at(rage::global::_155_outfit_editor_offset_4).at(slot, 13).at(index).at(2).as<int>() = value;
	}

	int get_accessory_model(int slot, int index) {
		return menu::script_global(rage::global::_155_outfit_editor_base).at(rage::global::_155_outfit_editor_base_offset).at(rage::global::_155_outfit_editor_offset_1).at(slot, 10).at(index).at(2).as<int>();
	}

	int get_accessory_variation(int slot, int index) {
		return menu::script_global(rage::global::_155_outfit_editor_base).at(rage::global::_155_outfit_editor_base_offset).at(rage::global::_155_outfit_editor_offset_2).at(slot, 10).at(index).at(2).as<int>();
	}

	int get_clothing_model(int slot, int index) {
		return menu::script_global(rage::global::_155_outfit_editor_base).at(rage::global::_155_outfit_editor_base_offset).at(rage::global::_155_outfit_editor_offset_3).at(slot, 13).at(index).at(2).as<int>();
	}

	int get_clothing_variation(int slot, int index) {
		return menu::script_global(rage::global::_155_outfit_editor_base).at(rage::global::_155_outfit_editor_base_offset).at(rage::global::_155_outfit_editor_offset_4).at(slot, 13).at(index).at(2).as<int>();
	}

	void update_slot_to_current(int slot) {
		for (int i = 0; i < 12; i++) {
			set_clothing_model(slot, i, native::get_ped_drawable_variation(menu::player::get_local_player().m_ped, i));
			set_clothing_variation(slot, i, native::get_ped_texture_variation(menu::player::get_local_player().m_ped, i));
		}

		for (int i = 0; i < 9; i++) {
			set_accessory_model(slot, i, native::get_ped_prop_index(menu::player::get_local_player().m_ped, i));
			set_accessory_variation(slot, i, native::get_ped_prop_texture_index(menu::player::get_local_player().m_ped, i));
		}
	}

	void cache_current_outfit() {
		for (int i = 0; i < 12; i++) {
			m_vars.m_clothing_cache[0][i] = native::get_ped_drawable_variation(menu::player::get_local_player().m_ped, i);
			m_vars.m_clothing_cache[1][i] = native::get_ped_texture_variation(menu::player::get_local_player().m_ped, i);
		}

		for (int i = 0; i < 9; i++) {
			m_vars.m_accessory_cache[0][i] = native::get_ped_prop_index(menu::player::get_local_player().m_ped, i);
			m_vars.m_accessory_cache[1][i] = native::get_ped_prop_texture_index(menu::player::get_local_player().m_ped, i);
		}
	}

	void set_cached_outfit() {
		for (int i = 0; i < 12; i++) {
			native::set_ped_component_variation(menu::player::get_local_player().m_ped, i, m_vars.m_clothing_cache[0][i], m_vars.m_clothing_cache[1][i], 0);
		}

		for (int i = 0; i < 9; i++) {
			native::set_ped_prop_index(menu::player::get_local_player().m_ped, i, m_vars.m_accessory_cache[0][i], m_vars.m_accessory_cache[1][i], true);
		}
	}

	void set_current_outfit_to_slot(int slot) {
		for (int i = 0; i < 12; i++) {
			native::set_ped_component_variation(menu::player::get_local_player().m_ped, i, get_clothing_model(slot, i), get_clothing_variation(slot, i), 0);
		}

		for (int i = 0; i < 9; i++) {
			native::set_ped_prop_index(menu::player::get_local_player().m_ped, i, get_accessory_model(slot, i), get_accessory_variation(slot, i), true);
		}
	}

	void create_outfit(int slot) {
		update_slot_to_current(slot);
		strcpy(network::account::outfits::vars::get_outfit_slot_name_ptr(slot), ("Ozark - " + std::to_string(slot)).c_str());

		menu::script_global(rage::global::_155_outfit_editor_base).at(rage::global::_155_outfit_editor_base_offset).at(rage::global::_155_outfit_editor_offset_5).at(slot).at(2).as<int>() = 1;
		network::account::outfits::vars::save_outfit_edit();
	}
}

void network_account_outfits_edit_menu::load() {
	set_parent<network_account_outfits_menu>();

	add_option(submenu_option("Name")
		.add_translate()
		.add_submenu<network_account_outfits_edit_name_menu>());

	add_option(submenu_option("Wardrobe")
		.add_translate()
		.add_submenu<wardrobe_menu>()
		.add_click([] {
			wardrobe_menu::get()->set_parent<network_account_outfits_edit_menu>();
			cache_current_outfit();
			set_current_outfit_to_slot(m_vars.m_slot);
		}));

	add_option(button_option("Load")
		.add_translate()
		.add_click([] { set_current_outfit_to_slot(m_vars.m_slot); }));

	add_option(button_option("Delete")
		.add_translate()
		.add_click([] {
			network::account::outfits::vars::delete_slot(m_vars.m_slot);
			network::account::outfits::vars::save_outfit_edit();
			menu::submenu::handler::set_submenu_previous(true);
		}));
}

void network_account_outfits_edit_menu::update() {}

void network_account_outfits_edit_menu::update_once() {
	if (menu::submenu::handler::get_previous() == wardrobe_menu::get()) {
		// update the slots components to our current outfit that we just edited
		update_slot_to_current(m_vars.m_slot);

		// restore our current outfit to our real outfit we cached
		set_cached_outfit();

		network::account::outfits::vars::save_outfit_edit();
	}

	// creating an outfit
	if (m_vars.m_slot == network::account::outfits::vars::get_free_slot_index()) {
		create_outfit(m_vars.m_slot);
	}
}

void network_account_outfits_edit_menu::feature_update() {}

network_account_outfits_edit_menu* g_instance;
network_account_outfits_edit_menu* network_account_outfits_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_account_outfits_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}