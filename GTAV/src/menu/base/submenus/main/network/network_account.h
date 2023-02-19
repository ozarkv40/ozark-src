#pragma once
#include "menu/base/submenu.h"

class network_account_menu : public menu::submenu::submenu {
public:
	static network_account_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_account_menu()
		: menu::submenu::submenu() {}
};

namespace network::account::vars {
	struct variables {
		int m_selected_character;
	};

	extern variables m_vars;
}