#pragma once
#include "menu/base/submenu.h"

class network_desync_kick_menu : public menu::submenu::submenu {
public:
	static network_desync_kick_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_desync_kick_menu()
		: menu::submenu::submenu() {}
};

namespace network::htoolkit::desync::vars {
	struct variables {
		bool m_block = true;
		bool m_redirect = true;
		bool m_notify = true;
	};

	extern variables m_vars;
}