#include "hooks.h"
#include "util/memory/memory.h"
#include "util/log.h"
#include "menu/base/submenus/main/network/toolkit/network_join_blocking.h"
#include "menu/base/submenus/main/network/toolkit/blocking/network_join_blocking_edit.h"
#include "menu/base/submenus/main/network/network_host_toolkit.h"
#include "menu/base/submenus/main/network/session/network_session_overseer.h"
#include "menu/base/util/notify.h"
#include "menu/base/util/helpers.h"
#include "util/caller.h"
#include <random>

std::vector<std::vector<uint8_t>> blacklisted_ips = {
	{ 104, 206, 12, 199 },
	{ 1, 159, 58, 170 },
	{ 5, 180, 62, 142 },
	{ 139, 99, 234, 42 },
	{ 139, 99, 234, 43 },
	{ 139, 99, 235, 167 },
	{ 124, 170, 101, 44 },
	{ 139, 99, 145, 127 },
	{ 139, 99, 234, 46 },
	{ 103, 137, 14, 227 }
};

std::vector<uint32_t> blacklisted_rids = {
	99760757,
	98042282,
	27232953,
	112323207,
	104516056,
	76705345,
	98932544,
	81665528,
	125642770,
	108803216,
	102267130,
	142314594,
	104231567,
	104032434,
	125518606,
	104337890,
	69160994,
	108608304,
	126427379,
	136720574,
	83765581,
	19541822,
	182093032,
	148254157,
	176014334,
	111632819,
	95888690,
	165700836
};

static localization t_session_join_request("Session Join Request", true, true);
static localization t_prevented("Prevented", true, true);
static localization t_joining_with_force_host("joining with force host, their modified token is", true, true);
static localization t_joining_with_developer_flag("joining with developer flags", true, true);
static localization t_joining_with_rid("joining with a spoofed Rockstar ID", true, true);
static localization t_joining_with_name("joining with a spoofed name", true, true);
static localization t_joining_with_ip("joining with a spoofed IP, their real IP is", true, true);
static localization t_joining_blocked("joining, you're not allowing anyone to join per your Host Toolkit config", true, true);
static localization t_joining_blocked_friend_only("joining, you're only allowing friends to join per your Host Toolkit config", true, true);
static localization t_joining_manually_blocked("joining, you have them manually blocked per your Host Toolkit config", true, true);
static localization t_corrupted_peer("is spoofing their peer, which has now been corrupted for this session hehe uwu", true, true);

bool menu::hooks::receive_session_join_request(uint64_t rcx, uint64_t rdx, uint64_t r8, uint64_t r9, int stack) {
	if (*(uint8_t*)(global::vars::g_hack_patches["RSJR"].m_address) == global::vars::g_hack_patches["RSJR"].m_patch[0]) {
		memory::write_vector(global::vars::g_hack_patches["RSJR"].m_address, global::vars::g_hack_patches["RSJR"].m_bytes);
	}

	using namespace network::htoolkit::blocking::vars;

	uint32_t ip_address = *(uint32_t*)(r9 + 0x8);
	rage::network::network_gamer_cmd* gamer_cmd = (rage::network::network_gamer_cmd*)(r8 - 0x8);

	LOG_DEV("== HOST JOIN REQUEST ==");
	LOG_DEV("Name: %s", gamer_cmd->m_name);
	LOG_DEV("Peer: %llx", gamer_cmd->m_host_token);
	LOG_DEV("RID: %llx", gamer_cmd->m_rockstar_id);
	LOG_DEV("Identifier: %llx", gamer_cmd->m_identifier.m_rockstar_id);
	LOG_DEV("IP: %llx", gamer_cmd->m_ip);
	LOG_DEV("MIP: %llx", gamer_cmd->m_msg_ip);
	LOG_DEV("MessageIP: %llx", ip_address);

	if (network::session::overseer::vars::process_join_request(gamer_cmd->m_identifier.m_rockstar_id, gamer_cmd->m_name)
		|| network::session::overseer::vars::process_join_request(gamer_cmd->m_rockstar_id, gamer_cmd->m_name)) {
		global::vars::g_hack_patches["RSJR"].m_patch[2] = FAILED_TO_JOIN_INTENDED_SESSION;
		memory::write_vector(global::vars::g_hack_patches["RSJR"].m_address, global::vars::g_hack_patches["RSJR"].m_patch);
		goto end;
	}

	if (m_vars.m_responses[TOOLKIT_DEV].m_enabled) {
		rage::network::join_request request;
		caller::call<void>(global::vars::g_construct_read_session_join_request_msg, &request.m_net_game_player_data_msg);
		if (caller::call<bool>(global::vars::g_read_session_join_request_msg, &request, *(uint64_t*)(r9 + 0x28), *(uint32_t*)(r9 + 0x30), 0)) {
			if ((request.m_ros_flags & 2) != 0) {
				if (m_vars.m_responses[TOOLKIT_DEV].m_notify) {
					if ((GetTickCount() - global::vars::g_spoofed_data_join_requests[gamer_cmd->m_host_token]) > 10000) {
						menu::notify::stacked(TRANSLATE(t_session_join_request), util::va::va("%s %s %s", TRANSLATE(t_prevented), menu::helpers::clean_name(gamer_cmd->m_name).c_str(), TRANSLATE(t_joining_with_developer_flag)), global::ui::g_error);
					}

					global::vars::g_spoofed_data_join_requests[gamer_cmd->m_host_token] = GetTickCount();
				}

				global::vars::g_hack_patches["RSJR"].m_patch[2] = network::htoolkit::blocking::edit::vars::responses[m_vars.m_responses[TOOLKIT_DEV].m_context.m_selected].m_result.second;
				memory::write_vector(global::vars::g_hack_patches["RSJR"].m_address, global::vars::g_hack_patches["RSJR"].m_patch);
				goto end;
			}
		}
	}

	if (std::find(begin(blacklisted_rids), end(blacklisted_rids), gamer_cmd->m_identifier.m_rockstar_id) != end(blacklisted_rids)
		|| std::find(begin(blacklisted_rids), end(blacklisted_rids), gamer_cmd->m_rockstar_id) != end(blacklisted_rids)
		|| std::find_if(begin(blacklisted_ips), end(blacklisted_ips), [=](std::vector<uint8_t>& e) { return e[0] == ((ip_address & 0xFF000000) >> 24) && e[1] == ((ip_address & 0xFF0000) >> 16) && e[2] == ((ip_address & 0xFF00) >> 8) && e[3] == (ip_address & 0xFF); }) != end(blacklisted_ips)) {
		LOG_DEV("Prevented faggot joining session (%s)", gamer_cmd->m_name);
		
		global::vars::g_hack_patches["RSJR"].m_patch[2] = UNABLE_TO_CONNECT_TO_SESSION;
		memory::write_vector(global::vars::g_hack_patches["RSJR"].m_address, global::vars::g_hack_patches["RSJR"].m_patch);
		goto end;
	}

	if (!m_vars.m_blocked_users.empty()) {
		for (user_block& user : m_vars.m_blocked_users) {
			if (user.m_enabled) {
				bool block = false;
				switch (user.m_type) {
					case 1: // rid
						if (gamer_cmd->m_identifier.m_rockstar_id == user.m_rockstar_id
							|| gamer_cmd->m_rockstar_id == user.m_rockstar_id) {
							block = true;
						}

						break;

					case 2: // name
						if (!strcmp(user.m_name, gamer_cmd->m_name)) {
							block = true;
						}

						break;

					case 3: // IP
						if (ip_address == user.m_ip || gamer_cmd->m_msg_ip == user.m_ip) {
							block = true;
						}

						break;
				}

				if (block) {
					if ((GetTickCount() - global::vars::g_spoofed_data_join_requests[gamer_cmd->m_host_token]) > 10000) {
						menu::notify::stacked(TRANSLATE(t_session_join_request), util::va::va("%s %s %s", TRANSLATE(t_prevented), menu::helpers::clean_name(gamer_cmd->m_name).c_str(), TRANSLATE(t_joining_manually_blocked)), global::ui::g_error);
					}

					global::vars::g_spoofed_data_join_requests[gamer_cmd->m_host_token] = GetTickCount();

					global::vars::g_hack_patches["RSJR"].m_patch[2] = user.m_response;
					memory::write_vector(global::vars::g_hack_patches["RSJR"].m_address, global::vars::g_hack_patches["RSJR"].m_patch);
					goto end;
				}
			}
		}
	}

	if (m_vars.m_responses[TOOLKIT_NEXT_SESSION_HOST].m_enabled || network::htoolkit::vars::m_vars.m_peer_token_corruption) {
		if (((gamer_cmd->m_host_token >> 32) & 0xFFFFFFFF) < 0x1000 || gamer_cmd->m_host_token < 0x1000) {
			if (m_vars.m_responses[TOOLKIT_NEXT_SESSION_HOST].m_enabled) {
				if (m_vars.m_responses[TOOLKIT_NEXT_SESSION_HOST].m_notify) {
					if ((GetTickCount() - global::vars::g_spoofed_data_join_requests[gamer_cmd->m_host_token]) > 10000) {
						menu::notify::stacked(TRANSLATE(t_session_join_request), util::va::va("%s %s %s %llx", TRANSLATE(t_prevented), menu::helpers::clean_name(gamer_cmd->m_name).c_str(), TRANSLATE(t_joining_with_force_host), gamer_cmd->m_host_token), global::ui::g_error);
					}

					global::vars::g_spoofed_data_join_requests[gamer_cmd->m_host_token] = GetTickCount();
				}

				global::vars::g_hack_patches["RSJR"].m_patch[2] = network::htoolkit::blocking::edit::vars::responses[m_vars.m_responses[TOOLKIT_NEXT_SESSION_HOST].m_context.m_selected].m_result.second;
				memory::write_vector(global::vars::g_hack_patches["RSJR"].m_address, global::vars::g_hack_patches["RSJR"].m_patch);
			} else {
				if (network::htoolkit::vars::m_vars.m_peer_token_corruption) {
					std::random_device r;
					std::seed_seq seed2 { r(), r(), r(), r(), r(), r(), r(), r() };
					std::mt19937 engine(seed2);
					std::uniform_int_distribution<uint64_t> rng(0xFFFFFFFF00000000, std::numeric_limits<uint64_t>::max());

					global::vars::g_sync_peer_corruption[gamer_cmd->m_host_token] = rng(engine);
					menu::notify::stacked(TRANSLATE(t_session_join_request), util::va::va("%s %s", menu::helpers::clean_name(gamer_cmd->m_name).c_str(), TRANSLATE(t_corrupted_peer)), global::ui::g_error);
				}
			}

			goto end;
		}
	}

	if (m_vars.m_responses[TOOLKIT_RID].m_enabled) {
		if (gamer_cmd->m_rockstar_id != gamer_cmd->m_identifier.m_rockstar_id
			|| gamer_cmd->m_identifier.m_rockstar_id < 10000) {
			if (m_vars.m_responses[TOOLKIT_RID].m_notify) {
				if ((GetTickCount() - global::vars::g_spoofed_data_join_requests[gamer_cmd->m_host_token]) > 10000) {
					if (gamer_cmd->m_rockstar_id != gamer_cmd->m_identifier.m_rockstar_id) {
						menu::notify::stacked(TRANSLATE(t_session_join_request), util::va::va("%s %s %s (%i & %i)", TRANSLATE(t_prevented), menu::helpers::clean_name(gamer_cmd->m_name).c_str(), TRANSLATE(t_joining_with_rid), (uint32_t)gamer_cmd->m_rockstar_id, (uint32_t)gamer_cmd->m_identifier.m_rockstar_id), global::ui::g_error);
					} else {
						menu::notify::stacked(TRANSLATE(t_session_join_request), util::va::va("%s %s %s (%i)", TRANSLATE(t_prevented), menu::helpers::clean_name(gamer_cmd->m_name).c_str(), TRANSLATE(t_joining_with_rid), (uint32_t)gamer_cmd->m_rockstar_id), global::ui::g_error);
					}
				}

				global::vars::g_spoofed_data_join_requests[gamer_cmd->m_host_token] = GetTickCount();
			}

			global::vars::g_hack_patches["RSJR"].m_patch[2] = network::htoolkit::blocking::edit::vars::responses[m_vars.m_responses[TOOLKIT_RID].m_context.m_selected].m_result.second;
			memory::write_vector(global::vars::g_hack_patches["RSJR"].m_address, global::vars::g_hack_patches["RSJR"].m_patch);
			goto end;
		}
	}

	if (m_vars.m_responses[TOOLKIT_NAME].m_enabled) {
		if (std::string(gamer_cmd->m_name).find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_.") != std::string::npos || strlen(gamer_cmd->m_name) < 6) {
			if (m_vars.m_responses[TOOLKIT_NAME].m_notify) {
				if ((GetTickCount() - global::vars::g_spoofed_data_join_requests[gamer_cmd->m_host_token]) > 10000) {
					menu::notify::stacked(TRANSLATE(t_session_join_request), util::va::va("%s \"%s\" %s", TRANSLATE(t_prevented), menu::helpers::clean_name(gamer_cmd->m_name).c_str(), TRANSLATE(t_joining_with_name)), global::ui::g_error);
				}

				global::vars::g_spoofed_data_join_requests[gamer_cmd->m_host_token] = GetTickCount();
			}

			global::vars::g_hack_patches["RSJR"].m_patch[2] = network::htoolkit::blocking::edit::vars::responses[m_vars.m_responses[TOOLKIT_NAME].m_context.m_selected].m_result.second;
			memory::write_vector(global::vars::g_hack_patches["RSJR"].m_address, global::vars::g_hack_patches["RSJR"].m_patch);
			goto end;
		}
	}

	if (m_vars.m_responses[TOOLKIT_IP].m_enabled) {
		if (gamer_cmd->m_msg_ip != ip_address || gamer_cmd->m_ip != ip_address) {
			if (m_vars.m_responses[TOOLKIT_IP].m_notify) {
				if ((GetTickCount() - global::vars::g_spoofed_data_join_requests[gamer_cmd->m_host_token]) > 10000) {
					char buffer[16];
					sprintf_s(buffer, "%i.%i.%i.%i", ((ip_address & 0xFF000000) >> 24), ((ip_address & 0xFF0000) >> 16), ((ip_address & 0xFF00) >> 8), (ip_address & 0xFF));
					menu::notify::stacked(TRANSLATE(t_session_join_request), util::va::va("%s %s %s %s", TRANSLATE(t_prevented), menu::helpers::clean_name(gamer_cmd->m_name).c_str(), TRANSLATE(t_joining_with_ip), buffer), global::ui::g_error);
				}

				global::vars::g_spoofed_data_join_requests[gamer_cmd->m_host_token] = GetTickCount();
			}

			global::vars::g_hack_patches["RSJR"].m_patch[2] = network::htoolkit::blocking::edit::vars::responses[m_vars.m_responses[TOOLKIT_IP].m_context.m_selected].m_result.second;
			memory::write_vector(global::vars::g_hack_patches["RSJR"].m_address, global::vars::g_hack_patches["RSJR"].m_patch);
			goto end;
		}
	}

	if (m_vars.m_who_can_join > 0) {
		if (m_vars.m_who_can_join == 1) {
			if ((GetTickCount() - global::vars::g_spoofed_data_join_requests[gamer_cmd->m_host_token]) > 10000) {
				menu::notify::stacked(TRANSLATE(t_session_join_request), util::va::va("%s %s %s", TRANSLATE(t_prevented), menu::helpers::clean_name(gamer_cmd->m_name).c_str(), TRANSLATE(t_joining_blocked)), global::ui::g_error);
			}

			global::vars::g_spoofed_data_join_requests[gamer_cmd->m_host_token] = GetTickCount();

			global::vars::g_hack_patches["RSJR"].m_patch[2] = UNABLE_TO_CONNECT_TO_SESSION;
			memory::write_vector(global::vars::g_hack_patches["RSJR"].m_address, global::vars::g_hack_patches["RSJR"].m_patch);
			goto end;
		}

		// Friends only
		bool can_join = false;
		for (int i = 0; i < native::network_get_friend_count(); i++) {
			rage::network::friends* _friend = (rage::network::friends*)&global::vars::g_friends[i];
			if (_friend->m_rockstar_id == gamer_cmd->m_identifier.m_rockstar_id) {
				if (!strcmp(gamer_cmd->m_name, _friend->m_name)) {
					can_join = true;
					break;
				}
			}
		}

		if (!can_join) {
			if ((GetTickCount() - global::vars::g_spoofed_data_join_requests[gamer_cmd->m_host_token]) > 10000) {
				menu::notify::stacked(TRANSLATE(t_session_join_request), util::va::va("%s %s %s", TRANSLATE(t_prevented), menu::helpers::clean_name(gamer_cmd->m_name).c_str(), TRANSLATE(t_joining_blocked_friend_only)), global::ui::g_error);
			}

			global::vars::g_spoofed_data_join_requests[gamer_cmd->m_host_token] = GetTickCount();

			global::vars::g_hack_patches["RSJR"].m_patch[2] = UNABLE_TO_CONNECT_TO_SESSION;
			memory::write_vector(global::vars::g_hack_patches["RSJR"].m_address, global::vars::g_hack_patches["RSJR"].m_patch);
			goto end;
		}
	}

end:
	if (network::htoolkit::vars::m_vars.m_sync_real_ip) {
		if (gamer_cmd->m_msg_ip != ip_address || gamer_cmd->m_ip != ip_address) {
			global::vars::g_sync_real_ip[gamer_cmd->m_host_token] = ip_address;
		}
	}

	// BETA - Change Peer
	bool change = false;
	menu::player::for_each([&] (menu::player::player_context& player) {
		if (player.m_net_player) {
			if (player.m_net_player->m_player_info) {
				if (player.m_net_player->m_player_info->m_host_token == gamer_cmd->m_host_token) {
					change = true;
				}
			}
		}
	}, true, true);

	if (change) {
		LOG_DEV("Player joining has the same peer as someone in the session, requesting that they change it...");
		global::vars::g_change_peer = true;
	}

	return receive_session_join_request_t(rcx, rdx, r8, r9, stack);
}