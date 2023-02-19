#include "network_players_teleport_apartments.h"
#include "menu/base/submenu_handler.h"
#include "../network_players_teleport.h"
#include "menu/base/util/helpers.h"
#include "rage/types/global_types.h"

using namespace network::players::teleport::apartments::vars;

namespace network::players::teleport::apartments::vars {
	variables m_vars;

	void teleport_player_to_apartment(menu::player::player_context& player, int id) {
		if (global::vars::g_network_menu_type == ALL_PLAYERS) {
			menu::player::for_each([=] (menu::player::player_context& p) {
				menu::helpers::trigger_script_event({ rage::global::apartment_teleport, p.m_id, 0, 0, id, id }, 6, p.m_id);
			});
		} else {
			menu::helpers::trigger_script_event({ rage::global::apartment_teleport, player.m_id, 0, 0, id, id }, 6, player.m_id);
		}
	}
}

void network_players_teleport_apartments_menu::load() {
	set_name("Apartments");
	set_parent<network_players_teleport_menu>();
}

void network_players_teleport_apartments_menu::update() {}

void network_players_teleport_apartments_menu::update_once() {
	clear_options(0);

	for (int i = 1; i < 116; i++) {
		std::string location = menu::helpers::get_location_from_id(i);
		if (location.empty() || !location.compare("NULL")) continue;

		add_option(button_option(location)
			.add_click([=] { teleport_player_to_apartment(menu::player::get_selected_player(), i); }));
	}
}

void network_players_teleport_apartments_menu::feature_update() {}

network_players_teleport_apartments_menu* g_instance;
network_players_teleport_apartments_menu* network_players_teleport_apartments_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_teleport_apartments_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}