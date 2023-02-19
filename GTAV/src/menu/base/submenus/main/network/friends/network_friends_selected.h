#pragma once
#include "menu/base/submenu.h"

class network_friends_selected_menu : public menu::submenu::submenu {
public:
	static network_friends_selected_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_friends_selected_menu()
		: menu::submenu::submenu() {}
};

namespace network::friends::selected::vars {
	struct variables {
		rage::network::friends* m_selected;
	};

	extern variables m_vars;
}