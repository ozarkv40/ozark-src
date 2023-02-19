#include "network_players_selected.h"
#include "menu/base/submenu_handler.h"
#include "../network_players.h"
#include "../../network.h"
#include "menu/base/util/timers.h"
#include "util/caller.h"
#include "menu/base/util/helpers.h"
#include "../spoofing/network_spoofing_profiles.h"
#include "network_players_spawn_blocking.h"
#include "network_players_friendly.h"
#include "network_players_teleport.h"
#include "network_players_text.h"
#include "network_players_removals.h"
#include "network_players_commands.h"
#include "network_players_abusive.h"
#include "network_players_trolling.h"
#include "network_players_vehicle.h"
#include "menu/base/submenus/main/protection/protection_reactions.h"
#include "menu/base/submenus/main/spawner.h"
#include "menu/base/submenus/main/network/session/network_session_overseer.h"

using namespace network::players::selected::vars;

namespace network::players::selected::vars {
	variables m_vars;
}

void network_players_selected_menu::load() {
	set_parent<network_players_menu>();

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
			helper_esp_menu::get()->set_parent<network_players_selected_menu>();
			helper::esp::vars::m_vars.m_current = &menu::player::get_selected_player().m_esp;
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
		.add_click([] { spawner::vars::m_vars.m_flag = spawner::vars::SPAWNER_PLAYER; }));

	add_option(submenu_option("Spawn Blocking")
		.add_translate()
		.add_submenu<network_players_spawn_blocking_menu>()
		.add_tooltip("Block entities being spawned and synced from this player"));

	add_option(button_option("Create Spoofing Profile")
		.add_translate()
		.add_click([] {
			if (!menu::player::get_selected_player().m_net_player || !menu::player::get_selected_player().m_net_player->m_player_info) return;
			uint32_t ip = menu::player::get_selected_player().m_net_player->m_player_info->m_external_ip;

			char buffer[32];
			sprintf(buffer, "%i.%i.%i.%i", ((ip & 0xFF000000) >> 24), ((ip & 0xFF0000) >> 16), ((ip & 0xFF00) >> 8), (ip & 0xFF));

			network::spoofing::profiles::vars::spoof_profile profile;
			profile.m_name = menu::player::get_selected_player().m_name;
			profile.m_ip = std::string(buffer);
			profile.m_rockstar_id = (uint32_t)menu::player::get_selected_player().m_net_player->m_player_info->m_identifier.m_rockstar_id;
			profile.m_file_name = profile.m_name;

			profile.m_crew_icon = menu::player::get_selected_player().m_net_player->get_crew_id();
			profile.m_crew_motto = menu::player::get_selected_player().m_net_player->get_crew_motto();
			profile.m_crew_name = menu::player::get_selected_player().m_net_player->get_crew_name();
			profile.m_crew_rank = menu::player::get_selected_player().m_net_player->get_crew_rank();
			profile.m_crew_tag = menu::player::get_selected_player().m_net_player->get_crew_tag();

			network::spoofing::profiles::vars::save_profile(profile);
		}));

	add_option(button_option("Add to Overseer")
		.add_translate()
		.add_click([] {
			if (menu::player::get_selected_player().m_net_player) {
				if (menu::player::get_selected_player().m_net_player->m_player_info) {
					network::session::overseer::vars::save(menu::player::get_selected_player().m_name, menu::player::get_selected_player().m_net_player->m_player_info->m_identifier.m_rockstar_id, "Manual Add");
				}
			}
		}));

	add_option(toggle_option("Spectate")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_spectate)
		.add_update([](toggle_option* option, int pos) { option->add_toggle(menu::player::get_selected_player().m_spectate); })
		.add_click([] {
			if (menu::player::get_selected_player().m_spectate) {
				if (native::network_is_in_spectator_mode()) {
					menu::player::for_each([](menu::player::player_context& player) {
						player.m_spectate = false;
						native::network_set_in_spectator_mode(false, player.m_ped);
					});

					menu::player::get_selected_player().m_spectate = true;
				}

				native::network_set_in_spectator_mode(true, menu::player::get_selected_player().m_ped);
			} else {
				native::network_set_in_spectator_mode(false, menu::player::get_selected_player().m_ped);
			}
		}));
}

void network_players_selected_menu::update() {}

void network_players_selected_menu::update_once() {
	global::vars::g_network_menu_type = SELECTED_PLAYER;
	if (!menu::player::get_selected_player().m_connected || menu::player::get_selected_player().m_name.empty()) return;
	set_name(menu::player::get_selected_player().m_name.c_str(), false, false);
}

void network_players_selected_menu::feature_update() {
	menu::submenu::submenu* current_submenu = menu::submenu::handler::get_current();
	for (; current_submenu; current_submenu = current_submenu->get_parent()) {
		if (current_submenu == this) {
			if (!menu::player::get_selected_player().m_connected) {
				if (menu::submenu::handler::get_current() != network_players_menu::get()) {
					menu::submenu::handler::set_submenu(network_players_menu::get());
					menu::submenu::handler::set_previous(network_menu::get());
				}
			}

			break;
		}
	}

	menu::player::for_each([](menu::player::player_context& player) {
		if (player.m_esp.m_name || m_vars.m_session_esp.m_name) {
			helper::esp::vars::name_esp(player.m_esp.m_name ? player.m_esp : m_vars.m_session_esp, player.m_ped, player.m_name);
		}

		if (player.m_esp.m_snapline || m_vars.m_session_esp.m_snapline) {
			helper::esp::vars::snapline_esp(player.m_esp.m_snapline ? player.m_esp : m_vars.m_session_esp, player.m_ped);
		}

		if (player.m_esp.m_2d_box || m_vars.m_session_esp.m_2d_box) {
			helper::esp::vars::_2d_esp(player.m_esp.m_2d_box ? player.m_esp : m_vars.m_session_esp, player.m_ped, 0);
		}

		if (player.m_esp.m_2d_corners || m_vars.m_session_esp.m_2d_corners) {
			helper::esp::vars::_2d_esp(player.m_esp.m_2d_corners ? player.m_esp : m_vars.m_session_esp, player.m_ped, 1);
		}

		if (player.m_esp.m_3d_box || m_vars.m_session_esp.m_3d_box) {
			helper::esp::vars::_3d_esp(player.m_esp.m_3d_box ? player.m_esp : m_vars.m_session_esp, player.m_ped, 0);
		}

		if (player.m_esp.m_3d_axis || m_vars.m_session_esp.m_3d_axis) {
			helper::esp::vars::_3d_esp(player.m_esp.m_3d_axis ? player.m_esp : m_vars.m_session_esp, player.m_ped, 1);
		}

		if (player.m_esp.m_skeleton_bones || m_vars.m_session_esp.m_skeleton_bones) {
			helper::esp::vars::skeleton_esp(player.m_esp.m_skeleton_bones ? player.m_esp : m_vars.m_session_esp, player.m_ped, 0);
		}

		if (player.m_esp.m_skeleton_joints || m_vars.m_session_esp.m_skeleton_joints) {
			helper::esp::vars::skeleton_esp(player.m_esp.m_skeleton_joints ? player.m_esp : m_vars.m_session_esp, player.m_ped, 1);
		}

		if (!m_vars.m_session_esp.m_2d_box_rainbow.m_rainbow_toggle && player.m_esp.m_2d_box_rainbow.m_rainbow_toggle) player.m_esp.m_2d_box_rainbow.m_rainbow.run();
		if (!m_vars.m_session_esp.m_2d_corners_rainbow.m_rainbow_toggle && player.m_esp.m_2d_corners_rainbow.m_rainbow_toggle) player.m_esp.m_2d_corners_rainbow.m_rainbow.run();
		if (!m_vars.m_session_esp.m_3d_box_rainbow.m_rainbow_toggle && player.m_esp.m_3d_box_rainbow.m_rainbow_toggle) player.m_esp.m_3d_box_rainbow.m_rainbow.run();
		if (!m_vars.m_session_esp.m_name_bg_rainbow.m_rainbow_toggle && player.m_esp.m_name_bg_rainbow.m_rainbow_toggle) player.m_esp.m_name_bg_rainbow.m_rainbow.run();
		if (!m_vars.m_session_esp.m_name_text_rainbow.m_rainbow_toggle && player.m_esp.m_name_text_rainbow.m_rainbow_toggle) player.m_esp.m_name_text_rainbow.m_rainbow.run();
		if (!m_vars.m_session_esp.m_skeleton_bones_rainbow.m_rainbow_toggle && player.m_esp.m_skeleton_bones_rainbow.m_rainbow_toggle) player.m_esp.m_skeleton_bones_rainbow.m_rainbow.run();
		if (!m_vars.m_session_esp.m_skeleton_joints_rainbow.m_rainbow_toggle && player.m_esp.m_skeleton_joints_rainbow.m_rainbow_toggle) player.m_esp.m_skeleton_joints_rainbow.m_rainbow.run();
	}, true);

	if (m_vars.m_session_esp.m_2d_box_rainbow.m_rainbow_toggle) m_vars.m_session_esp.m_2d_box_rainbow.m_rainbow.run();
	if (m_vars.m_session_esp.m_2d_corners_rainbow.m_rainbow_toggle) m_vars.m_session_esp.m_2d_corners_rainbow.m_rainbow.run();
	if (m_vars.m_session_esp.m_3d_box_rainbow.m_rainbow_toggle) m_vars.m_session_esp.m_3d_box_rainbow.m_rainbow.run();
	if (m_vars.m_session_esp.m_name_bg_rainbow.m_rainbow_toggle) m_vars.m_session_esp.m_name_bg_rainbow.m_rainbow.run();
	if (m_vars.m_session_esp.m_name_text_rainbow.m_rainbow_toggle) m_vars.m_session_esp.m_name_text_rainbow.m_rainbow.run();
	if (m_vars.m_session_esp.m_skeleton_bones_rainbow.m_rainbow_toggle) m_vars.m_session_esp.m_skeleton_bones_rainbow.m_rainbow.run();
	if (m_vars.m_session_esp.m_skeleton_joints_rainbow.m_rainbow_toggle) m_vars.m_session_esp.m_skeleton_joints_rainbow.m_rainbow.run();
}

network_players_selected_menu* g_instance;
network_players_selected_menu* network_players_selected_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_selected_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}