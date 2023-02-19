#include "network_account.h"
#include "menu/base/submenu_handler.h"
#include "../network.h"
#include "menu/base/util/stats.h"
#include "account/network_account_level.h"
#include "account/network_account_unlocks.h"
#include "account/network_account_times.h"
#include "account/network_account_outfits.h"
#include "account/network_account_wins_losses.h"
#include "account/network_account_kd.h"

using namespace network::account::vars;

namespace network::account::vars {
	variables m_vars;

	scroll_struct<int> characters[] = {
		{ localization("PLACEHOLDER", true), 0 },
		{ localization("PLACEHOLDER", true), 1 }
	};

	int get_character_count() {
		const char* character_two = native::stat_get_string(0xD2AB0EC6, -1);
		if (!character_two || strlen(character_two) < 1) return 1;
		return 2;
	}
}

void network_account_menu::load() {
	set_name("Account");
	set_parent<network_menu>();

	int current_char = 0;
	native::stat_get_int(0x2F2F120F, &current_char, -1);
	m_vars.m_selected_character = current_char ? 1 : 0;

	add_option(scroll_option<int>(SCROLL, "Selected Character")
		.add_translate()
		.add_scroll(m_vars.m_selected_character, 0, NUMOF(characters), characters)
		.add_update([](scroll_option<int>* option, int pos) { option->add_scroll(m_vars.m_selected_character, 0, get_character_count(), characters); }));

	// TODO: Presets maybe?

	add_option(submenu_option("Level")
		.add_translate()
		.add_submenu<network_account_level_menu>());

	add_option(submenu_option("Unlocks")
		.add_translate()
		.add_submenu<network_account_unlocks_menu>());

	add_option(submenu_option("Times")
		.add_translate()
		.add_submenu<network_account_times_menu>());

	add_option(submenu_option("Outfits")
		.add_translate()
		.add_submenu<network_account_outfits_menu>());

	add_option(submenu_option("Wins and Losses")
		.add_translate()
		.add_submenu<network_account_wins_losses_menu>());

	add_option(submenu_option("K/D")
		.add_translate()
		.add_submenu<network_account_kd_menu>());

	add_option(button_option("Edit Character Name")
		.add_translate()
		.add_keyboard("Enter new character name", 32, [](button_option* option, const char* name) {
			native::stat_set_string(native::get_hash_key(("MP" + std::to_string(m_vars.m_selected_character) + "_CHAR_NAME").c_str()), name, true);
		})
		.add_update([](button_option* option) {
			option->add_keyboard_default(characters[m_vars.m_selected_character].m_name.get_original());
		}));

	add_option(button_option("Redesign Character")
		.add_translate()
		.add_click([] { stats<bool>::set("FM_CHANGECHAR_ASKED", false); }));

	add_option(button_option("Clear Mental State")
		.add_translate()
		.add_click([] { stats<float>::set("PLAYER_MENTAL_STATE", 0.0f); }));

	add_string("Unavailable");
}

void network_account_menu::update() {}

void network_account_menu::update_once() {
	characters[0].m_name.set(native::stat_get_string(0x4A211FC8, -1));
	characters[1].m_name.set(native::stat_get_string(0xD2AB0EC6, -1));

	if (!native::network_is_in_session()) {
		characters[0].m_name.set("~c~" + get_string("Unavailable"));
		characters[1].m_name.set("~c~" + get_string("Unavailable"));
	}
}

void network_account_menu::feature_update() {}

network_account_menu* g_instance;
network_account_menu* network_account_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_account_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}