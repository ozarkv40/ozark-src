#pragma once
#include "menu/base/submenu.h"

class network_players_abusive_attackers_menu : public menu::submenu::submenu {
public:
	static network_players_abusive_attackers_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_players_abusive_attackers_menu()
		: menu::submenu::submenu() {}
};

namespace network::players::abusive::attackers::vars {
	struct variables {
		int m_attacker_type;
		int m_attacker_count = 1;

		bool m_attacker_invincibility = false;
		bool m_attacker_invisibility = false;
	};

	extern variables m_vars;
}