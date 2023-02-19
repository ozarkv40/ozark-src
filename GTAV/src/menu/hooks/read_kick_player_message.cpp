#include "hooks.h"
#include "menu/base/util/notify.h"
#include "util/va.h"
#include "rage/engine.h"

static localization t_kicked("Kicked", true, true);
static localization t_kicked_by_host("You were kick by the host", true, true);
static localization t_kicked_by_desync("You were desynced from the session", true, true);

bool menu::hooks::read_kick_player_message(uint64_t rcx, uint64_t rdx) {
	if (read_kick_player_message_t(rcx, rdx)) {
		uint32_t type = *(uint32_t*)(rdx + 0x10);
		switch (type) {
			case 0:
			case 4:
				menu::notify::stacked(TRANSLATE(t_kicked), util::va::va("%s (%s)", TRANSLATE(t_kicked_by_host), rage::engine::get_host_net_game_player()->m_player_info->m_name), global::ui::g_error);
				break;

			case 1:
				menu::notify::stacked(TRANSLATE(t_kicked), TRANSLATE(t_kicked_by_desync), global::ui::g_error);
				break;
		}
	}

	return false;
}