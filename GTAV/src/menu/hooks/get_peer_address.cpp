#include "hooks.h"
#include "menu/base/submenus/main/network/network_spoofing.h"

bool menu::hooks::get_peer_address(uint64_t* peer) {
	if (peer) {
		if (network::spoofing::vars::m_vars.m_spoofed_peer) {
			*peer = network::spoofing::vars::m_vars.m_spoofed_peer;
			return true;
		}
	}

	return get_peer_address_t(peer);
}