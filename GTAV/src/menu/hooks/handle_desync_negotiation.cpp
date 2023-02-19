#include "hooks.h"
#include "menu/base/util/helpers.h"
#include "menu/base/submenus/main/protection/protection_events.h"
#include "menu/base/submenus/main/network/toolkit/network_desync_kick.h"
#include "menu/base/submenus/main/protection/protection_reactions.h"
#include "menu/base/submenus/main/network/network_host_toolkit.h"
#include "rage/engine.h"
#include "util/log.h"

static localization t_desync_kicking("Desync Kicking", true, true);
static localization t_attempting_to_desync_kick("is attempting to quantum desync kick", true, true);

bool menu::hooks::host_handle_desync_request(uint64_t rcx, uint64_t rdx, rage::network::list_kick_peers* peers, uint32_t r9d) {
	uint64_t sender = 0;
	uint64_t target = 0;

	auto vit = std::find_if(begin(global::vars::g_desyncs_host), end(global::vars::g_desyncs_host), [=](std::unordered_map<uint64_t, uint64_t>::value_type& element) {
		return element.first == peers->m_peers[0].m_peer;
	});

	if (vit != end(global::vars::g_desyncs_host)) {
		sender = peers->m_peers[0].m_peer;
		target = peers->m_peers[1].m_peer;
	} else {
		vit = std::find_if(begin(global::vars::g_desyncs_host), end(global::vars::g_desyncs_host), [=](std::unordered_map<uint64_t, uint64_t>::value_type& element) {
			return element.first == peers->m_peers[1].m_peer;
		});

		if (vit != end(global::vars::g_desyncs_host)) {
			sender = peers->m_peers[1].m_peer;
			target = peers->m_peers[0].m_peer;
		}
	}

	if (sender && target) {
		menu::player::player_context& sender_player = menu::helpers::get_player_from_peer(sender);
		menu::player::player_context& target_player = menu::helpers::get_player_from_peer(target);

		if (sender_player.m_connected && target_player.m_connected) {
			auto v = std::find_if(begin(global::vars::g_host_desync_logs), end(global::vars::g_host_desync_logs), [=](std::pair<uint64_t, uint64_t>& Element) {
				return Element.first == sender && Element.second == target;
			});

			if (v == end(global::vars::g_host_desync_logs)) {
				global::vars::g_host_desync_logs.push_back({ sender, target });
				menu::helpers::flag_modder(sender_player.m_id, menu::player::REASON_QUANTUM_KICK);
				protection::reactions::vars::process_event(protection::reactions::vars::EVENT_QUANTUM_KICK, sender_player.m_id);

				if (network::htoolkit::desync::vars::m_vars.m_notify) {
					menu::notify::protection(sender_player.m_name, t_desync_kicking.get() + " " + target_player.m_name, network::htoolkit::desync::vars::m_vars.m_redirect, network::htoolkit::desync::vars::m_vars.m_block);
				}
			}

			if (network::htoolkit::desync::vars::m_vars.m_redirect) {
				if (menu::helpers::is_valid_net_player(sender_player.m_net_player)) {
					peers->m_peers[1].m_peer = sender_player.m_net_player->m_player_info->m_host_token;
					return host_handle_desync_request_t(rcx, rdx, peers, r9d);
				}
			}
		} else LOG_DEV("[HOST] Failed verifying connected (%i %i))", sender_player.m_connected, target_player.m_connected);
	} else {
		LOG_DEV("[HOST] Failed getting sender + target (%llx %llx))", sender, target);
		return host_handle_desync_request_t(rcx, rdx, peers, r9d);
	}

	if (network::htoolkit::desync::vars::m_vars.m_redirect || network::htoolkit::desync::vars::m_vars.m_block) {
		r9d = 0;
	}

	return host_handle_desync_request_t(rcx, rdx, peers, r9d);
}

uint64_t menu::hooks::handle_desync_negotiation(uint64_t rcx, uint64_t rdx, uint64_t r8) {
	rage::bit_buffer buffer;
	buffer.prepare(*(uint64_t*)(r8 + 0x38), *(uint32_t*)(r8 + 0x40));

	int message_id = 0;
	if (buffer.read_msg_header(&message_id)) {
		if (message_id == 1) { // rage::reassignNegotiateMsg
			Player sender_id = menu::helpers::get_net_msg_sender(*(uint64_t*)(r8 + 0x38));
			if (sender_id != -1) {
				uint32_t mask = 0;
				buffer.read_uint(&mask, 8);

				uint32_t peer_count = 0;
				buffer.read_uint(&peer_count, 5);

				// peer_count &= mask;

				// if there's one target
				if (peer_count == 1) {
					// iterate in case of future code
					uint64_t* peers = new uint64_t[peer_count];

					for (uint32_t i = 0; i < peer_count; i++) {
						buffer.read_ulonglong(&peers[i], 0x40);

						LOG_DEV("Peer[%i]: %llx", i, peers[i]);
					}

					if (menu::helpers::get_player_from_peer(peers[0]).m_connected && !menu::helpers::get_player_from_peer(peers[0]).m_name.empty()) {
						auto vit = std::find_if(begin(global::vars::g_desyncs), end(global::vars::g_desyncs), [=](std::unordered_map<Player, desyncs>::value_type& element) {
							return element.first == sender_id;
						});

						if (vit == end(global::vars::g_desyncs)) {
							global::vars::g_desyncs[sender_id] = { peers[0], GetTickCount(), 1, false };
							LOG_DEV("Pushing back desync peer %llx", peers[0]);
						} else {
							if (GetTickCount() - global::vars::g_desyncs[sender_id].m_last <= 4000) {
								global::vars::g_desyncs[sender_id].m_possibility = true;
								global::vars::g_desyncs[sender_id].m_count++;
							} else global::vars::g_desyncs[sender_id].m_possibility = false;

							global::vars::g_desyncs[sender_id].m_last = GetTickCount();

							if (global::vars::g_desyncs[sender_id].m_possibility && global::vars::g_desyncs[sender_id].m_count >= 10) {
								menu::player::player_context& player = menu::player::get_player(sender_id);
								if (menu::helpers::is_valid_net_player(player.m_net_player)) {
									// don't notify if host, it's handled in the kick hook
									if (protection::events::vars::m_vars.m_desync_kicks.notify()) {
										if (menu::player::get_local_player().m_net_player != rage::engine::get_host_net_game_player()) {
											menu::notify::stacked(TRANSLATE(t_desync_kicking), menu::helpers::clean_name(player.m_name) + " " + TRANSLATE(t_attempting_to_desync_kick) + " " + menu::helpers::get_player_from_peer(peers[0]).m_name);
										}
									}

									menu::helpers::flag_modder(menu::helpers::get_player_from_peer(peers[0]).m_id, menu::player::REASON_QUANTUM_KICK);
									protection::reactions::vars::process_event(protection::reactions::vars::EVENT_QUANTUM_KICK, menu::helpers::get_player_from_peer(peers[0]).m_id);

									if (menu::player::get_local_player().m_net_player == rage::engine::get_host_net_game_player()) {
										global::vars::g_desyncs_host[player.m_net_player->m_player_info->m_host_token] = peers[0];
									}

									global::vars::g_desyncs.erase(sender_id);
								} else LOG_DEV("Bad player");
							} else LOG_DEV("Possibility=%i Count=%i", global::vars::g_desyncs[sender_id].m_possibility, global::vars::g_desyncs[sender_id].m_count);
						}
					} else LOG_DEV("If statement failed (%llx)", peers[0]);

					delete[] peers;
				} else LOG_DEV("Desync peer count was %i (%i)", peer_count, peer_count & mask);
			} else LOG_DEV("Failed getting desync sender");
		}
	}

	return handle_desync_negotiation_t(rcx, rdx, r8);
}