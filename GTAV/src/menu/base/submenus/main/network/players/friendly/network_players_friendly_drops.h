#pragma once
#include "menu/base/submenu.h"

class network_players_friendly_drops_menu : public menu::submenu::submenu {
public:
	static network_players_friendly_drops_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_players_friendly_drops_menu()
		: menu::submenu::submenu() {}
};

namespace network::players::friendly::drops::vars {
	struct variables {
		bool m_drop_toggle;
		int m_drop_type;
		int m_drop_pickup;
		int m_drop_weapon;
		int m_drop_money_model;
		int m_drop_money_style;
		int m_drop_money_delay = 6;
		int m_drop_money_timer;
	};

	extern variables m_vars;
}