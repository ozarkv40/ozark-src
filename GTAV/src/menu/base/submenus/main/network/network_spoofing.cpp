#include "network_spoofing.h"
#include "menu/base/submenu_handler.h"
#include "../network.h"
#include "rage/engine.h"
#include "spoofing/network_spoofing_player_rotation.h"
#include "spoofing/network_spoofing_vehicle_rotation.h"
#include "spoofing/network_spoofing_intervals.h"
#include "spoofing/network_spoofing_crew.h"
#include "spoofing/network_spoofing_name.h"
#include "spoofing/network_spoofing_ip.h"
#include "spoofing/network_spoofing_rid.h"
#include "spoofing/network_spoofing_profiles.h"
#include "util/log.h"

using namespace network::spoofing::vars;

namespace network::spoofing::vars {
	variables m_vars;

	uint64_t offsets[][2] = {
		{ 0x2BFA020, 0x2C00030 },
		{ 0x2945570, 0x29440D0 },
		{ 0x293E980, 0x2936400 },
		{ 0x1E16348, 0x1E1B7C8 },
		{ 0x2C06530, 0x2C0C5E0 },
		{ 0x2C09C20, 0x2C10508 },
		{ 0x2C09C08, 0x2C104F0 },
		{ 0x290CB20, 0x29117F0 },
		{ 0x2943DA0 + 0x30, 0x2949550 + 0x30 },
	};

	void do_peer_spoof(uint64_t peer, bool no_change) {
		if (m_vars.m_original_peer == 0xFFFFFFFFFFFFFFFC) {
			m_vars.m_original_peer = *(uint64_t*)(global::vars::g_game_address.first + offsets[0][global::vars::g_steam]); // updated
		}

		m_vars.m_spoofed_peer = peer;
		uint64_t check_peer = *(uint64_t*)(global::vars::g_game_address.first + offsets[0][global::vars::g_steam]);
		bool same_spoof = peer == *(uint64_t*)(global::vars::g_game_address.first + offsets[0][global::vars::g_steam]); // updated

		for (int i = 0; i <= 8; i++) {
			*(uint64_t*)(global::vars::g_game_address.first + offsets[i][global::vars::g_steam]) = peer; // updated
		}

		rage::network::network_base_config* real_config = global::vars::g_network_base_config;
		if (global::vars::g_steam) {
			real_config = (rage::network::network_base_config*)((uint64_t)global::vars::g_network_base_config + 0x70);
		}

		if (is_valid_ptr(real_config)) {
			if (real_config->m_unk_ptr) {
				for (uint32_t i = 0; i < *(uint32_t*)(real_config->m_unk_ptr + 0x2388); i++) {
					uint64_t config = *(uint64_t*)(real_config->m_unk_ptr + (i * 8) + 0x2288);
					if (config) {
						if (*(uint64_t*)(config + 0x60) == check_peer) {
							*(uint64_t*)(config + 0x60) = peer;
						}
					}
				}

				uint64_t unk_table = global::vars::g_game_address.first + offsets[8][global::vars::g_steam]; // updated
				for (int i = 0; i < 32; i++) {
					uint64_t ptr = *(uint64_t*)(unk_table + (i * 8) + 0x1808);
					if (!is_valid_ptr(ptr)) break;

					if (*(uint64_t*)(ptr + 0x60) == check_peer) {
						*(uint64_t*)(ptr + 0x60) = peer;
					}
				}

				*(uint64_t*)(real_config->m_unk_ptr + 0x9A0) = peer;
			}
		}

		if (global::vars::g_ped_factory) {
			if (global::vars::g_ped_factory->m_local_ped) {
				if (global::vars::g_ped_factory->m_local_ped->m_player_info) {
					global::vars::g_ped_factory->m_local_ped->m_player_info->m_host_token = peer;
				}
			}
		}

		if (!same_spoof && !no_change) {
			if (*global::vars::g_game_state == GameStatePlaying) {
				if (native::network_is_in_session()) {
					network::vars::find_new_session(0);
				}
			}
		}
	}

	void handle_peer_change(button_option* option, const char* result) {
		if (result[0] == '0' && (result[1] == 'x' || result[1] == 'X')) {
			do_peer_spoof(_strtoui64(result, 0, 0));
			util::config::write_uint64(network_spoofing_menu::get()->get_submenu_name_stack(), "Peer", _strtoui64(result, 0, 0));
		} else {
			std::string str(result);
			if (std::find_if(str.begin(), str.end(), [](unsigned char c) { return !std::isdigit(c); }) == str.end()) {
				do_peer_spoof(atoi(result));
				util::config::write_uint64(network_spoofing_menu::get()->get_submenu_name_stack(), "Peer", atoi(result));
			}
		}
	}

	void handle_peer_reset() {
		do_peer_spoof(m_vars.m_original_peer);
		m_vars.m_spoofed_peer = m_vars.m_original_peer;
		util::config::write_uint64(network_spoofing_menu::get()->get_submenu_name_stack(), "Peer", 0);
	}
}

void network_spoofing_menu::load() {
	set_name("Spoofing");
	set_parent<network_menu>();

	if (m_vars.m_original_peer == 0xFFFFFFFFFFFFFFFC) {
		m_vars.m_original_peer = *(uint64_t*)(global::vars::g_game_address.first + offsets[0][global::vars::g_steam]); // updated
		m_vars.m_spoofed_peer = m_vars.m_original_peer;
	}

	add_option(submenu_option("Profiles")
		.add_translate().add_hotkey()
		.add_submenu<network_spoofing_profiles_menu>());

	add_option(submenu_option("Rockstar ID")
		.add_translate().add_hotkey()
		.add_submenu<network_spoofing_rid_menu>());

	add_option(submenu_option("IP Address")
		.add_translate().add_hotkey()
		.add_submenu<network_spoofing_ip_menu>());

	add_option(submenu_option("Name")
		.add_translate().add_hotkey()
		.add_submenu<network_spoofing_name_menu>());

	add_option(submenu_option("Crew")
		.add_translate().add_hotkey()
		.add_submenu<network_spoofing_crew_menu>());

	add_option(submenu_option("Sync Intervals")
		.add_translate().add_hotkey()
		.add_submenu<network_spoofing_intervals_menu>());

	add_option(submenu_option("Player Rotation")
		.add_translate().add_hotkey()
		.add_submenu<network_spoofing_player_rotation_menu>());

	add_option(submenu_option("Vehicle Rotation")
		.add_translate().add_hotkey()
		.add_submenu<network_spoofing_vehicle_rotation_menu>());

	add_option(toggle_option("Movement Animation")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_movement_animation)
		.add_tooltip("Stops your player doing a walk/sprint animation"));

	add_option(toggle_option("Rockstar Developer")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_rockstar_developer)
		.add_tooltip("You NEED to be using Rockstar ID spoofing for this, otherwise you have a chance of getting banned"));

	add_option(button_option("Force Next Session Host")
		.add_translate().add_hotkey()
		.add_keyboard("Enter the peer to spoof to! (Hint: hash or numeric)", 30, handle_peer_change)
		.add_tooltip("Saves to config automatically. NOTE: Changing peer mid session will cause an automatic session change. LOWER = BETTER"));

	add_option(button_option("Revert Next Session Host")
		.add_translate().add_hotkey()
		.add_click(handle_peer_reset)
		.add_tooltip("Reset your peer token to the original, saves to config automatically. NOTE: Resetting peer mid session will cause an automatic session change")
		.add_requirement([] { return m_vars.m_spoofed_peer != m_vars.m_original_peer; }));

	add_string("Spoofing");
	add_string("Peer spoof loaded from config, current peer set to");

	uint64_t peer = util::config::read_uint64(get_submenu_name_stack(), "Peer", 0);
	if (peer > 0) {
		menu::notify::stacked(get_string("Spoofing"), util::va::va("Peer spoof loaded from config, current peer set to 0x%llx", peer));
		do_peer_spoof(peer);
	}
}

void network_spoofing_menu::update() {}

void network_spoofing_menu::update_once() {
	if (native::does_entity_exist(network::spoofing::rotation::vehicle::vars::m_vars.m_ghost_handle)) {
		native::detach_entity(network::spoofing::rotation::vehicle::vars::m_vars.m_ghost_handle, true, false);
		native::delete_entity(&network::spoofing::rotation::vehicle::vars::m_vars.m_ghost_handle);
		network::spoofing::rotation::vehicle::vars::m_vars.m_ghost_handle = 0;
	}
}

void network_spoofing_menu::feature_update() {}

network_spoofing_menu* g_instance;
network_spoofing_menu* network_spoofing_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_spoofing_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}