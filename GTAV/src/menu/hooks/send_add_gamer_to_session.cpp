#include "hooks.h"
#include "menu/base/submenus/main/network/network_spoofing.h"
#include "menu/base/submenus/main/network/network_host_toolkit.h"
#include "menu/base/submenus/main/network/spoofing/network_spoofing_name.h"
#include "menu/base/submenus/main/network/spoofing/network_spoofing_ip.h"
#include "util/log.h"
#include "util/util.h"
#include "rage/engine.h"
#include "menu/base/util/player_manager.h"
#include <random>

bool menu::hooks::send_add_gamer_to_session(uint64_t rcx, rage::network::network_gamer_cmd* gamer) {
	if (gamer) {
		if (gamer->m_host_token == network::spoofing::vars::m_vars.m_spoofed_peer) {
			// IM JOINING, SPOOF
			LOG_DEV("%s", util::convert_bytes_to_string((uint8_t*)gamer, 0x100, true).c_str());

			if (!network::spoofing::name::vars::m_vars.m_spoofed_name.empty()) {
				const char* original_name = rage::engine::sc_get_string("gtag");
				if (original_name) {
					if (strcmp(original_name, network::spoofing::name::vars::m_vars.m_spoofed_name.c_str())) {
						LOG_CUSTOM_WARN(XOR("Spoof"), XOR("Spoofing name from %s to %s"), original_name, network::spoofing::name::vars::m_vars.m_spoofed_name.c_str());
						strncpy(gamer->m_name, network::spoofing::name::vars::m_vars.m_spoofed_name.c_str(), 20);

						if (menu::player::get_local_player().m_net_player) {
							if (menu::player::get_local_player().m_net_player->m_player_info) {
								strncpy(menu::player::get_local_player().m_net_player->m_player_info->m_name, network::spoofing::name::vars::m_vars.m_spoofed_name.c_str(), 0x14);
							}
						}
					}
				}
			}

			if (!network::spoofing::ip::vars::m_vars.m_spoofing_ip.empty()) {
				if (strcmp(network::spoofing::ip::vars::m_vars.m_default_ip.c_str(), network::spoofing::ip::vars::m_vars.m_spoofing_ip.c_str())) {
					std::vector<std::string> split = util::split_string(network::spoofing::ip::vars::m_vars.m_spoofing_ip, ".");
					if (split.size() == 4) {
						LOG_CUSTOM_WARN(XOR("Spoof"), XOR("Spoofing IP from %s to %s"), network::spoofing::ip::vars::m_vars.m_default_ip.c_str(), network::spoofing::ip::vars::m_vars.m_spoofing_ip.c_str());
						gamer->set_ip(3, (uint8_t)atoi(split[0].c_str()));
						gamer->set_ip(2, (uint8_t)atoi(split[1].c_str()));
						gamer->set_ip(1, (uint8_t)atoi(split[2].c_str()));
						gamer->set_ip(0, (uint8_t)atoi(split[3].c_str()));
					} else {
						LOG_CUSTOM_ERROR(XOR("Spoof"), XOR("Failed spoofing IP, format isn't valid"));
					}
				}
			}
		} else {
			// IM HOST, POG
			if (network::htoolkit::vars::m_vars.m_sync_real_ip) {
				if (global::vars::g_sync_real_ip.contains(gamer->m_host_token)) {
					gamer->m_ip = global::vars::g_sync_real_ip[gamer->m_host_token];

					LOG_CUSTOM_WARN(XOR("Spoof"), XOR("Giving %s's real IP to a player in the session (%i.%i.%i.%i)"), gamer->m_name,
						((gamer->m_ip & 0xFF000000) >> 24), ((gamer->m_ip & 0xFF0000) >> 16), ((gamer->m_ip & 0xFF00) >> 8), (gamer->m_ip & 0xFF));
				}
			}

			if (network::htoolkit::vars::m_vars.m_peer_token_corruption) {
				if (global::vars::g_sync_peer_corruption.contains(gamer->m_host_token)) {
					gamer->m_host_token = global::vars::g_sync_peer_corruption[gamer->m_host_token];
					LOG_CUSTOM_WARN(XOR("Spoof"), XOR("Giving a player in the session a corrupted peer token, because %s was spoofing (L)"), gamer->m_name);
				}
			}

			/*if (network::htoolkit::vars::m_vars.m_randomize_clients) {
				std::string new_name = util::create_random_string(0x13);
				LOG(XOR("Randomizing %s's name to %s"), gamer->m_name, new_name.c_str());
				strcpy(gamer->m_name, new_name.c_str());
			}*/
		}
	}

	return send_add_gamer_to_session_t(rcx, gamer);
}