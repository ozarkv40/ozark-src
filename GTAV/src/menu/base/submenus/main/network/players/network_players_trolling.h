#pragma once
#include "menu/base/submenu.h"
#include "menu/base/util/player_manager.h"

class network_players_trolling_menu : public menu::submenu::submenu {
public:
	static network_players_trolling_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_players_trolling_menu()
		: menu::submenu::submenu() {}
};

namespace network::players::trolling::vars {
	struct variables {
		int m_remove_weapon_group_type;
	};

	void black_screen(menu::player::player_context& player);
	extern variables m_vars;
}
