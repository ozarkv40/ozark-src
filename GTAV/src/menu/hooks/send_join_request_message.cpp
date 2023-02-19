#include "hooks.h"
#include "menu/base/submenus/main/network/network_spoofing.h"
#include "menu/base/submenus/main/network/network_join_bypass.h"
#include "util/log.h"

bool menu::hooks::send_join_request_message(rage::network::join_request* rcx, uint64_t rdx, uint32_t r8d, uint64_t r9) {
	if (rcx) {
		rcx->m_flags |= 2;
		rcx->m_flags |= 4;

		if (network::spoofing::vars::m_vars.m_rockstar_developer) {
			rcx->m_ros_flags |= 2;
		} else {
			rcx->m_ros_flags &= ~2; // in case r* dev perks is enabled in misc
		}
	}

	return send_join_request_message_t(rcx, rdx, r8d, r9);
}