#include "hooks.h"
#include "menu/base/submenus/main/protection/protection_join_blocking.h"
#include "util/log.h"

void menu::hooks::write_gs_item(int index, rage::network::gs_session* data, const char* type) {
	if (protection::joining::vars::m_vars.m_block) {
		memset(data, 0, sizeof(rage::network::gs_session));
	}

	if (protection::joining::vars::m_vars.m_spoof) {
		if (protection::joining::vars::m_vars.m_spoof_info.m_peer_token) {
			memcpy(data, &protection::joining::vars::m_vars.m_spoof_info, sizeof(rage::network::gs_session));
		}
	}

	write_gs_item_t(index, data, type);
}