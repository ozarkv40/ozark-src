#include "hooks.h"
#include "menu/base/util/helpers.h"
#include "menu/base/submenus/main/protection/protection_events.h"
#include "menu/base/submenus/main/protection/protection_reactions.h"
#include "menu/base/submenus/main/network/network_host_toolkit.h"
#include "util/log.h"

enum eUpdatePlayerScriptStatus {
	REMOVE_BITSET,
	SCRIPT_ADD_CANDIDATE,
	SCRIPT_ADDED_CANDIDATE,
	SCRIPT_RETRY_JOIN,
};

struct script_status {
	char _0x0000[0x8];
	eUpdatePlayerScriptStatus m_status;
};

static localization t_join_timeout("Join Timeout", true, true);
static localization t_prevented_join_timeout("Prevented join timeout from", true, true);

void menu::hooks::update_player_script_status(rage::script::game_script_handler_network_component* component, uint64_t rdx, uint64_t r8) {
	script_status* status = (script_status*)rdx;
	if (!is_valid_ptr(component)) {
		LOG_DEV("BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD");
		return;
	}

	if (component->m_state == 2) {
#ifdef DEV_MODE
		std::string state = "";
		switch (status->m_status) {
			case 0: state = "REMOVE_BITSET"; break;
			case 1: state = "SCRIPT_ADD_CANDIDATE"; break;
			case 2: state = "SCRIPT_ADDED_CANDIDATE"; break;
			case 3: state = "SCRIPT_RETRY_JOIN"; break;
		}
#endif

		rage::network::net_game_player* player = *(rage::network::net_game_player**)(r8 + 0x10);
		if (menu::helpers::is_valid_net_player(player)) {
			if (is_valid_ptr(component->m_component)) {
				if (is_valid_ptr(component->m_component->m_thread)) {
					LOG_DEV("[%s][%s] State=%s", player->m_player_info->m_name, component->m_component->m_thread->m_name, state.c_str());

					if (status->m_status == SCRIPT_RETRY_JOIN) {
						auto vit = std::find_if(begin(global::vars::g_join_timeout_fix), end(global::vars::g_join_timeout_fix), [=](join_timeout_fix& element) {
							return element.m_id == player->m_id && element.m_script_hash == component->m_component->m_thread->m_script_hash;
						});

						if (vit == end(global::vars::g_join_timeout_fix)) {
							global::vars::g_join_timeout_fix.push_back({ player->m_id, component->m_component->m_thread->m_script_hash, 1 });
							goto end;
						}

						vit->m_retry_count++;
						if (vit->m_retry_count >= 5) {
							status->m_status = SCRIPT_ADD_CANDIDATE;

							network::htoolkit::vars::force_host_of_script(component->m_component->m_thread->m_name);

							//if (!strcmp(component->m_component->m_thread->m_name, "freemode")) {
								menu::helpers::flag_modder(player->m_id, menu::player::REASON_JOIN_TIMEOUT);
								protection::reactions::vars::process_event(protection::reactions::vars::EVENT_JOIN_TIMEOUT, player->m_id);

								if (protection::events::vars::m_vars.m_join_timeout.notify()) {
									menu::notify::stacked(TRANSLATE(t_join_timeout), util::va::va("%s %s (%s)", TRANSLATE(t_prevented_join_timeout), menu::helpers::clean_name(player->m_player_info->m_name).c_str(), component->m_component->m_thread->m_name));
								}
							//}
						}
					}
				}
			}
		}
	}

end:
	update_player_script_status_t(component, rdx, r8);
}