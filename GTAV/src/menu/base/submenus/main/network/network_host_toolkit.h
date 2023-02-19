#pragma once
#include "menu/base/submenu.h"

class network_host_toolkit_menu : public menu::submenu::submenu {
public:
	static network_host_toolkit_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_host_toolkit_menu()
		: menu::submenu::submenu() {}
};

namespace network::htoolkit::vars {
	struct variables {
		int m_transition;
		bool m_extra_slot;
		bool m_sync_real_ip;
		bool m_peer_token_correction;
		bool m_peer_token_corruption;
		bool m_randomize_clients;
	};

	bool force_host_of_script(const char* script, bool notify = false);
	extern variables m_vars;
}