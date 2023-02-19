#pragma once
#include "menu/base/submenu.h"

class network_account_wins_losses_edit_menu : public menu::submenu::submenu {
public:
	static network_account_wins_losses_edit_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_account_wins_losses_edit_menu()
		: menu::submenu::submenu() {}
};

namespace network::account::wins::losses::edit::vars {
	struct variables {
		bool m_total = false;
		std::pair<std::string, int> m_wins;
		std::pair<std::string, int> m_losses;
	};

	extern variables m_vars;
}
