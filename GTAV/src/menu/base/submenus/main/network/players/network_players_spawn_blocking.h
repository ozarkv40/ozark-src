#pragma once
#include "menu/base/submenu.h"

class network_players_spawn_blocking_menu : public menu::submenu::submenu {
public:
	static network_players_spawn_blocking_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_players_spawn_blocking_menu()
		: menu::submenu::submenu()
	{}
};

namespace network::players::blocking::vars {
	struct variables {
		int m_type = 0;
	};

	extern variables m_vars;
}