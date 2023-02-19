#include "network_session.h"
#include "menu/base/submenu_handler.h"
#include "../network.h"
#include "players/network_players_friendly.h"
#include "players/network_players_teleport.h"
#include "players/network_players_text.h"
#include "players/network_players_removals.h"
#include "players/network_players_commands.h"
#include "players/network_players_abusive.h"
#include "players/network_players_trolling.h"
#include "players/network_players_vehicle.h"
#include "players/network_players_selected.h"
#include "menu/base/submenus/main/spawner.h"
#include "spoofing/network_spoofing_profiles.h"
#include "menu/base/util/panels.h"
#include "session/network_session_excludes.h"
#include "session/network_session_overseer.h"

using namespace network::session::vars;

namespace network::session::vars {
	variables m_vars;
}

void network_session_menu::load() {
	set_name("Session");
	set_parent<network_menu>();

	add_option(submenu_option("Removals")
		.add_translate()
		.add_submenu<network_players_removals_menu>());

	add_option(submenu_option("Friendly")
		.add_translate()
		.add_submenu<network_players_friendly_menu>());

	add_option(submenu_option("Teleport")
		.add_translate()
		.add_submenu<network_players_teleport_menu>());

	add_option(submenu_option("Abusive")
		.add_translate()
		.add_submenu<network_players_abusive_menu>());

	add_option(submenu_option("Trolling")
		.add_translate()
		.add_submenu<network_players_trolling_menu>());

	add_option(submenu_option("ESP")
		.add_translate()
		.add_submenu<helper_esp_menu>()
		.add_click([] {
			helper_esp_menu::get()->set_parent<network_session_menu>();
			helper::esp::vars::m_vars.m_current = &network::players::selected::vars::m_vars.m_session_esp;
		}));

	add_option(submenu_option("Chat Commands")
		.add_translate()
		.add_submenu<network_players_commands_menu>());

	add_option(submenu_option("Text Message")
		.add_translate()
		.add_submenu<network_players_text_menu>());

	add_option(submenu_option("Vehicle")
		.add_translate()
		.add_submenu<network_players_vehicle_menu>());

	add_option(submenu_option("Spawner")
		.add_translate()
		.add_submenu<spawner_menu>()
		.add_click([] { spawner::vars::m_vars.m_flag = spawner::vars::SPAWNER_SESSION; }));

	add_option(submenu_option("Excludes")
		.add_translate()
		.add_submenu<network_session_excludes_menu>()
		.add_tooltip("Exclude players from session options"));

	add_option(submenu_option("Overseer")
		.add_translate()
		.add_submenu<network_session_overseer_menu>());

	add_option(button_option("Create Spoofing Profiles")
		.add_translate()
		.add_click([] {
			menu::player::for_each([] (menu::player::player_context& player) {
				if (!player.m_net_player || !player.m_net_player->m_player_info) return;
				uint32_t ip = player.m_net_player->m_player_info->m_external_ip;

				char buffer[32];
				sprintf(buffer, "%i.%i.%i.%i", ((ip & 0xFF000000) >> 24), ((ip & 0xFF0000) >> 16), ((ip & 0xFF00) >> 8), (ip & 0xFF));

				network::spoofing::profiles::vars::spoof_profile profile;
				profile.m_name = player.m_name;
				profile.m_ip = std::string(buffer);
				profile.m_rockstar_id = (uint32_t)player.m_net_player->m_player_info->m_identifier.m_rockstar_id;
				profile.m_file_name = profile.m_name;

				profile.m_crew_icon = player.m_net_player->get_crew_id();
				profile.m_crew_motto = player.m_net_player->get_crew_motto();
				profile.m_crew_name = player.m_net_player->get_crew_name();
				profile.m_crew_rank = player.m_net_player->get_crew_rank();
				profile.m_crew_tag = player.m_net_player->get_crew_tag();

				network::spoofing::profiles::vars::save_profile(profile);
			});
		}));
}

void network_session_menu::update() {}

void network_session_menu::update_once() {
	menu::panels::toggle_panel_render("PANEL_OVERSEER", false);
	menu::panels::toggle_panel_render("PANEL_SESSION", true);
}

void network_session_menu::feature_update() {}

network_session_menu* g_instance;
network_session_menu* network_session_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_session_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}