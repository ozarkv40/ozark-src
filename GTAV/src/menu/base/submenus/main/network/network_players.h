#pragma once
#include "menu/base/submenu.h"

class network_players_menu : public menu::submenu::submenu {
public:
	static network_players_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_players_menu()
		: menu::submenu::submenu() {}
};

namespace network::players::vars {
	struct variables {
		int m_selected_player = 0;
		int m_sort = 0;
	};

	extern variables m_vars;
}