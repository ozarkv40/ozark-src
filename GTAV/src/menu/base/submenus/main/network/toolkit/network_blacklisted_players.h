#pragma once
#include "menu/base/submenu.h"

class network_blacklisted_players_menu : public menu::submenu::submenu {
public:
	static network_blacklisted_players_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_blacklisted_players_menu()
		: menu::submenu::submenu() {}
};

namespace network::htoolkit::blacklist::vars {
	struct blacklisted_player {
		rage::network::blacklisted_player m_player;
		bool m_api;
		std::string m_resolved_name;
	};

	struct variables {
		std::vector<blacklisted_player> m_players;
	};

	extern variables m_vars;
}