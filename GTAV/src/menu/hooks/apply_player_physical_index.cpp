#include "hooks.h"
#include "menu/base/util/helpers.h"
#include "menu/base/util/player_manager.h"
#include "rage/invoker/natives.h"
#include "util/log.h"
#include "util/va.h"
#include "menu/base/util/notify.h"
#include "menu/base/submenus/main/network/network_recent_players.h"
#include "menu/base/submenus/main/network/session/network_session_overseer.h"
#include "menu/base/submenus/main/network.h"
#include "menu/base/submenus/main/settings/hide_info.h"
#include "rage/api/api.h"
#include "rage/ros.h"
#include "rage/engine.h"

static localization t_player_joining("Player Joining", true, true);
static localization t_player_leaving("Player Leaving", true, true);
static localization t_joining_into_slot("is joining into slot", true, true);
static localization t_leaving_slot("is leaving slot", true, true);

void clean_allocations() {
	LOG("Cleaning allocations created from the previous session");
	global::vars::g_online_rockstar_ids_queue.clear();
	global::vars::g_online_rockstar_ids.clear();
	global::vars::g_relay_usage.clear();
	global::vars::g_geo.clear();
	global::vars::g_alignment_tests.clear();
	global::vars::g_desyncs_host.clear();
	global::vars::g_desyncs.clear();
	global::vars::g_join_timeout_fix.clear();
	global::vars::g_host_desync_logs.clear();
	global::vars::g_last_synced_player_models.clear();
	global::vars::g_spoofed_data_join_requests.clear();
	global::vars::g_gs_info_requests.clear();
	global::vars::g_sync_real_ip.clear();
	global::vars::g_sync_peer_corruption.clear();

	menu::player::for_each([](menu::player::player_context& player) {
		player.reset();
	}, true, true);
}

void menu::hooks::apply_player_physical_index(uint64_t network_player_manager, rage::network::net_game_player* player, uint8_t slot) {
	if (menu::helpers::is_valid_net_player(player)) {
		if (player != *(rage::network::net_game_player**)(*(uint64_t*)(global::vars::g_network_player_manager) + 0xE8)) {
			if (slot != 0xFF) {
				if (settings::hide::vars::m_vars.m_hide_names) {
					settings::hide::vars::m_vars.m_cached[player->m_player_info->m_identifier.m_rockstar_id] = player->m_player_info->m_name;
					strcpy(player->m_player_info->m_name, util::va::va("Player_%i", slot));
				}
			}

			auto vit = std::find_if(begin(global::vars::g_join_timeout_fix), end(global::vars::g_join_timeout_fix), [=](join_timeout_fix& element) {
				return element.m_id == (slot == 0xff ? player->m_id : slot);
			});

			if (vit != end(global::vars::g_join_timeout_fix)) {
				global::vars::g_join_timeout_fix.erase(vit);
			}

			if (network::vars::m_vars.m_join_notifications) {
				std::string cleaned = menu::helpers::clean_name(player->m_player_info->m_name);
				if (slot == 0xFF) {
					// leaving
					menu::notify::stacked(TRANSLATE(t_player_leaving), util::va::va("%s %s %i", cleaned.c_str(), TRANSLATE(t_leaving_slot), player->m_id));
				} else {
					// joining
					menu::notify::stacked(TRANSLATE(t_player_joining), util::va::va("%s %s %i", cleaned.c_str(), TRANSLATE(t_joining_into_slot), slot));
				}
			}

			if (slot != 0xFF) {
				uint32_t ip = player->m_player_info->m_external_ip;

				char buffer[32];
				sprintf_s(buffer, "%i.%i.%i.%i", ((ip & 0xff000000) >> 24), ((ip & 0xff0000) >> 16), ((ip & 0xff00) >> 8), (ip & 0xff));

				network::recents::vars::save(menu::helpers::clean_name(player->m_player_info->m_name), buffer, player->m_player_info->m_identifier.m_rockstar_id);
				network::session::overseer::vars::process_join_notify(player->m_player_info->m_identifier.m_rockstar_id, menu::helpers::clean_name(player->m_player_info->m_name));
			}
		} else {
			clean_allocations();
		}
	}

	menu::player::get_player(slot == 0xFF ? player->m_id : slot).reset();
	return apply_player_physical_index_t(network_player_manager, player, slot);
}