#include "hooks.h"
#include "menu/base/util/player_manager.h"
#include "rage/engine.h"
#include "menu/base/util/helpers.h"
#include "menu/base/submenus/main/network/players/network_players_removals.h"
#include "menu/base/submenus/main/protection/entity/protection_entity_blocking.h"
#include "util/log.h"

void menu::hooks::pack_clone_create(uint64_t _this, rage::network::net_object* net_obj, rage::network::net_game_player* net_game_player, uint64_t sync_data) {
	if (net_obj) {
		if (net_obj->m_type >= NetObjectAutomobile && net_obj->m_type < INVALID) {
			if (protection::entity::blocking::vars::m_vars.m_toggled[net_obj->m_type]) {
				LOG_DEV("pack clone create blocked - 1");
				return;
			}

			if (net_game_player->m_id >= 0 && net_game_player->m_id < 34) {
				if (menu::player::get_player(net_game_player->m_id).m_ghost[net_obj->m_type]) {
					LOG_DEV("pack clone create blocked - 2");
					return;
				}

				if (net_obj->m_type == NetObjectPickup) {
					std::vector<int> dropping_stealth;
					menu::player::for_each([&] (menu::player::player_context& player) {
						if (player.m_drop_toggle && player.m_drop_stealth) {
							dropping_stealth.push_back(player.m_id);
						}
					}, true);

					bool bad = false;
					if (dropping_stealth.size()) {
						for (int ID : dropping_stealth) {
							if (ID != net_game_player->m_id) {
								bad = true;
								break;
							}
						}
					}

					if (bad) return;
				}

				auto& vars = network::players::removals::vars::m_vars;
				if (vars.m_session_crash) {
					return pack_clone_create_t(_this, net_obj, net_game_player, sync_data);
				}

				if (vars.m_targeted_crash) {
					if (vars.m_broken_entities.find(net_obj) != vars.m_broken_entities.end()) {
						auto p = menu::helpers::get_player_from_rid(vars.m_broken_entities[net_obj]);
						if (p.m_connected && p.m_net_player) {
							LOG_DEV("Packing clone create crash");
							return pack_clone_create_t(_this, net_obj, p.m_net_player, sync_data);
						}

						LOG_DEV("pack clone create blocked - 3");
						return;
					}
				}
			}
		}
	}

	return pack_clone_create_t(_this, net_obj, net_game_player, sync_data);
}