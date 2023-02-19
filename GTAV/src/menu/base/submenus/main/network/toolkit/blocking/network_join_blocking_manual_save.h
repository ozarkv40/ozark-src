#pragma once
#include "menu/base/submenu.h"

class network_join_blocking_manual_save_menu : public menu::submenu::submenu {
public:
	static network_join_blocking_manual_save_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_join_blocking_manual_save_menu()
		: menu::submenu::submenu() {}
};

namespace network::htoolkit::blocking::save::vars {
	struct variables {
		bool m_toggles[1024];
	};

	extern variables m_vars;
}