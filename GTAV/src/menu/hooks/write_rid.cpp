#include "hooks.h"
#include "menu/base/submenus/main/network/spoofing/network_spoofing_rid.h"
#include "util/log.h"
#include "util/util.h"

bool menu::hooks::write_net_msg_identifier(rage::bit_buffer* buffer, uint64_t rdx, int r8d) {
	if (global::vars::g_rs_info) {
		if (global::vars::g_rs_info->m_rockstar_id) {
			if (rdx == global::vars::g_rs_info->m_rockstar_id) {
				if (network::spoofing::rid::vars::m_vars.m_loaded || network::spoofing::rid::vars::m_vars.m_spoofing_rid > 0) {
					rdx = network::spoofing::rid::vars::m_vars.m_spoofing_rid;
				}
			}
		}
	}
	
	return write_net_msg_identifier_t(buffer, rdx, r8d);
}

bool menu::hooks::write_ulonglong_to_bit_buffer(rage::bit_buffer* buffer, uint64_t rdx, int r8d) {
	if (global::vars::g_rs_info) {
		if (global::vars::g_rs_info->m_rockstar_id) {
			if (rdx == global::vars::g_rs_info->m_rockstar_id) {
				if (network::spoofing::rid::vars::m_vars.m_loaded || network::spoofing::rid::vars::m_vars.m_spoofing_rid > 0) {
					rdx = network::spoofing::rid::vars::m_vars.m_spoofing_rid;
				}
			}
		}
	}

	return write_ulonglong_to_bit_buffer_t(buffer, rdx, r8d);
}