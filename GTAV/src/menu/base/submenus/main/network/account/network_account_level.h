#pragma once
#include "menu/base/submenu.h"

class network_account_level_menu : public menu::submenu::submenu {
public:
	static network_account_level_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_account_level_menu()
		: menu::submenu::submenu() {}
};

namespace network::account::level::vars {
	struct variables {
		int m_type;
	};

	extern variables m_vars;
}