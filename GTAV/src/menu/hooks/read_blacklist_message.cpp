#include "hooks.h"
#include "menu/base/submenus/main/protection/protection_events.h"
#include "menu/base/util/helpers.h"
#include "rage/engine.h"

static localization t_host_kicking("Host Kicking", true, true);

bool menu::hooks::read_blacklist_message(uint64_t rcx, uint64_t rdx) {
	bool _return = read_blacklist_message_t(rcx, rdx);

	if (_return) {
		if (protection::events::vars::m_vars.m_host_kicks.notify()) {
			uint64_t rockstar_id = *(uint64_t*)(rcx + 0x8);
			if (rockstar_id) {
				menu::player::player_context& player = menu::helpers::get_player_from_rid(rockstar_id);
				if (player.m_connected && !player.m_name.empty()) {
					if (menu::helpers::is_valid_net_player(rage::engine::get_host_net_game_player())) {
						menu::notify::protection(rage::engine::get_host_net_game_player()->m_player_info->m_name, t_host_kicking.get() + " " + player.m_name, false, false);
					}
				}
			}
		}
	}

	return _return;
}