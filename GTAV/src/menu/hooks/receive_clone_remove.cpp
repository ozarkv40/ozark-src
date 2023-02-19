#include "hooks.h"
#include "menu/base/util/player_manager.h"
#include "rage/engine.h"
#include "menu/base/submenus/main/protection/protection_events.h"
#include "menu/base/submenus/main/protection/protection_reactions.h"
#include "menu/base/util/helpers.h"
#include "util/log.h"

static localization t_crash_remove("Crash - Remove Local Player", true, true);
static localization t_ghost("Ghost", true, true);

bool menu::hooks::receive_clone_remove(uint64_t _this, rage::network::net_game_player* sender, uint64_t r8, uint16_t network_id, uint64_t unk) {
	rage::network::net_object* object = rage::engine::get_network_object_from_network_id(_this, network_id, true);

	if (is_valid_ptr(menu::player::get_local_player().m_ped_ptr)) {
		if (object == menu::player::get_local_player().m_ped_ptr->get_net_obj()) {
			if (menu::helpers::is_valid_net_player(sender)) {
				if (protection::events::vars::m_vars.m_crashing.notify()) {
					menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_crash_remove), false, true);
				}

				menu::helpers::flag_modder(sender->m_id, menu::player::REASON_CRASH_ATTEMPT, true);
				protection::reactions::vars::process_event(protection::reactions::vars::EVENT_CRASH_ATTEMPT, sender->m_id);
			}

			return false;
		}
	}

	if (object) {
		if (object->m_type == NetObjectPlayer) {
			if (protection::events::vars::m_vars.m_ghost.enabled()) {
				if (menu::helpers::is_valid_net_player(sender)) {
					if (protection::events::vars::m_vars.m_ghost.notify()) {
						menu::notify::protection(sender->m_player_info->m_name, TRANSLATE(t_ghost), false, true);
					}

					menu::helpers::flag_modder(sender->m_id, menu::player::REASON_GHOST, true);
				}

				if (protection::events::vars::m_vars.m_ghost.block()) {
					return false;
				}
			}
		}
	}

	return receive_clone_remove_t(_this, sender, r8, network_id, unk);
}