#include "hooks.h"
#include "menu/base/submenus/main/protection/protection_events.h"
#include "menu/base/submenus/main/protection/protection_reactions.h"
#include "menu/base/util/helpers.h"
#include "rage/engine.h"
#include "util/caller.h"

static localization t_script_host_migration("Script Host Migration", true, true);
static localization t_forced_script_host_migration("Forced Script Host Migration", true, true);

bool menu::hooks::read_new_script_host_message(uint64_t rcx, uint64_t rdx) {
	uint8_t data[0x50];
	memset(data, 0, 0x50);

	uint64_t script_table = *(uint64_t*)rcx;
	*(uint64_t*)&data[0] = caller::call<uint64_t>(*(uint64_t*)(script_table + 0x78), rcx);

	if (caller::call<bool>(global::vars::g_read_new_script_host_message, data, *(uint64_t*)(rdx), *(uint32_t*)(rdx + 0x8), 0)) {
		rage::network::net_game_player* new_host = *(rage::network::net_game_player**)(rdx + 0x10);
		if (menu::helpers::is_valid_net_player(new_host)) {
			bool forced = false;
			uint16_t host_token = *(uint16_t*)&data[0x8];
			if (host_token == 0xFFFF) {
				forced = true;
				menu::helpers::flag_modder(new_host->m_id, menu::player::REASON_SCRIPT_MIGRATION);
				protection::reactions::vars::process_event(protection::reactions::vars::EVENT_SCRIPT_MIGRATION, new_host->m_id);
			}

			if (protection::events::vars::m_vars.m_sh_migration.notify()) {
				rage::script::game_script_handler* script_handler = caller::call<rage::script::game_script_handler*>(*(uint64_t*)(script_table + 0x48), rcx, *(uint64_t*)(&data[0]));
				if (is_valid_ptr(script_handler)) {
					if (is_valid_ptr(script_handler->m_thread)) {
						if (!strcmp(script_handler->m_thread->m_name, "freemode")) {
							if (new_host->m_id != native::network_get_host_of_script("freemode", -1, 0)) {
								menu::notify::protection(new_host->m_player_info->m_name, forced ? TRANSLATE(t_forced_script_host_migration) : TRANSLATE(t_script_host_migration), false, false);
							}
						}
					}
				}
			}
		}
	}

	return read_new_script_host_message_t(rcx, rdx);
}