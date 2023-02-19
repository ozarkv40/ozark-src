#include "hooks.h"
#include "menu/base/submenus/main/protection/protection_anti_detection.h"
#include "util/log.h"

bool menu::hooks::write_player_game_state_data_node(uint64_t rcx, uint64_t rdx) {
	bool _return = write_player_game_state_data_node_t(rcx, rdx);

	if (protection::detection::vars::m_vars.m_super_jump) {
		*(bool*)(rdx + 0x1B7) = false;
	}

	if (protection::detection::vars::m_vars.m_godmode) {
		*(bool*)(rdx + 0xD5) = false;
	}

	if (protection::detection::vars::m_vars.m_spectate) {
		*(bool*)(rdx + 0xC7) = false;
		*(uint16_t*)(rdx + 0x128) = 0;
	}

	return _return;
}