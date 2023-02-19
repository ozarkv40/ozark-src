#include "network_players_text_presets.h"
#include "menu/base/submenu_handler.h"
#include "../network_players_text.h"
#include "menu/base/util/helpers.h"

using namespace network::players::text::presets::vars;

namespace network::players::text::presets::vars {
	variables m_vars;

	std::string presets[] = {
		"buy Ozark at ozark.gg", "money drop at the airport", "i love penis",
		"i'm actually retarded", "i don't get any action in bed", "fuck you",
		"you suck", "crash me if you can loser", "spare some coochie?",
		"i need love and attention", "i have no fwends :(", "PLEASE send me feet pics",
		"Ozark #1", "enjoy the crash lmao"
	};
}

void network_players_text_presets_menu::load() {
	set_name("Presets");
	set_parent<network_players_text_menu>();

	for (std::string& preset : presets) {
		add_string(preset);
	}

	add_option(toggle_option("Send Translated Preset")
		.add_translate()
		.add_hotkey()
		.add_toggle(m_vars.m_send_tanslated)
		.add_tooltip("Send the translated version of the presets"));

	add_option(button_option("IP Address")
		.add_translate()
		.add_click([] {
			if (menu::helpers::is_valid_net_player(menu::player::get_selected_player().m_net_player)) {
				uint32_t ip = menu::player::get_selected_player().m_net_player->m_player_info->m_external_ip;

				char buffer[32];
				sprintf(buffer, "%i.%i.%i.%i", ((ip & 0xFF000000) >> 24), ((ip & 0xFF0000) >> 16), ((ip & 0xFF00) >> 8), (ip & 0xFF));
				menu::player::get_selected_player().m_text_message_msg = std::string(buffer);
			}

			menu::submenu::handler::set_submenu_previous();
		})
		.add_requirement([] { return global::vars::g_network_menu_type == SELECTED_PLAYER; }));

	add_option(button_option("Geo Location")
		.add_translate()
		.add_click([] {
			if (menu::helpers::is_valid_net_player(menu::player::get_selected_player().m_net_player)) {
				uint32_t ip = menu::player::get_selected_player().m_net_player->m_player_info->m_external_ip;

				auto vit = global::vars::g_geo.find(ip);
				if (vit != global::vars::g_geo.end()) {
					menu::player::get_selected_player().m_text_message_msg = vit->second.m_city + ", " + vit->second.m_region_name;
				}
			}

			menu::submenu::handler::set_submenu_previous();
		})
		.add_requirement([] { return global::vars::g_network_menu_type == SELECTED_PLAYER; }));
}

void network_players_text_presets_menu::update() {}

void network_players_text_presets_menu::update_once() {
	clear_options(3);

	for (std::string& preset : presets) {
		add_option(button_option(get_string(preset))
			.add_click([=] {
				menu::player::get_selected_player().m_text_message_msg = m_vars.m_send_tanslated ? get_string(preset) : preset;
				menu::submenu::handler::set_submenu_previous(); 
			}));
	}
}

void network_players_text_presets_menu::feature_update() {}

network_players_text_presets_menu* g_instance;
network_players_text_presets_menu* network_players_text_presets_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_text_presets_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}