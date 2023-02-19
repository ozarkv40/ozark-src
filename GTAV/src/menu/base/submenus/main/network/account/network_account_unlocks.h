#pragma once
#include "menu/base/submenu.h"

class network_account_unlocks_menu : public menu::submenu::submenu {
public:
	static network_account_unlocks_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_account_unlocks_menu()
		: menu::submenu::submenu() {}
};

namespace network::account::unlocks::vars {
	struct variables {

	};

	extern variables m_vars;
}