#pragma once
#include "menu/base/submenu.h"

class network_menu : public menu::submenu::submenu {
public:
	static network_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_menu()
		: menu::submenu::submenu() {}
};

namespace network::vars {
	struct variables {
		int m_transition;
		bool m_join_notifications = true;
	};

	void find_new_session(int id);
	extern variables m_vars;
}