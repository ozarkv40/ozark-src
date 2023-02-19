#pragma once
#include "menu/base/submenu.h"

class network_spoofing_menu : public menu::submenu::submenu {
public:
	static network_spoofing_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_spoofing_menu()
		: menu::submenu::submenu() {}
};

namespace network::spoofing::vars {
	struct variables {
		uint64_t m_original_peer = 0xFFFFFFFFFFFFFFFC;
		uint64_t m_spoofed_peer = 0;
		bool m_rockstar_developer;
		bool m_movement_animation;
	};

	void do_peer_spoof(uint64_t peer, bool no_change = false);
	extern variables m_vars;
}