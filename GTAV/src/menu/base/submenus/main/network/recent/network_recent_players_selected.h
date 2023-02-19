#pragma once
#include "menu/base/submenu.h"

class network_recent_players_selected_menu : public menu::submenu::submenu {
public:
	static network_recent_players_selected_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_recent_players_selected_menu()
		: menu::submenu::submenu() {}
};

namespace network::recents::selected::vars {
	struct variables {
		int m_type;
		std::size_t m_selected_player;
	};

	extern variables m_vars;
}