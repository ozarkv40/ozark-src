#pragma once
#include "menu/base/submenu.h"

class network_join_blocking_manual_menu : public menu::submenu::submenu {
public:
	static network_join_blocking_manual_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_join_blocking_manual_menu()
		: menu::submenu::submenu() {}
};

namespace network::htoolkit::blocking::manual::vars {
	struct variables {

	};

	extern variables m_vars;
}