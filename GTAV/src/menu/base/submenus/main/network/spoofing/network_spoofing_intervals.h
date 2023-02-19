#pragma once
#include "menu/base/submenu.h"

class network_spoofing_intervals_menu : public menu::submenu::submenu {
public:
	static network_spoofing_intervals_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_spoofing_intervals_menu()
		: menu::submenu::submenu() {}
};

namespace network::spoofing::intervals::vars {
	struct variables {

	};

	extern variables m_vars;
}