#pragma once
#include "menu/base/submenu.h"

class network_join_bypass_menu : public menu::submenu::submenu {
public:
	static network_join_bypass_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_join_bypass_menu()
		: menu::submenu::submenu() {}
};

namespace network::bypass::vars {
	struct variables {
		bool m_invite_only = true;
		bool m_friend_only = true;
		bool m_crew_only = true;
	};

	extern variables m_vars;
}