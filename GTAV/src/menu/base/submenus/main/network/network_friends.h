#pragma once
#include "menu/base/submenu.h"

class network_friends_menu : public menu::submenu::submenu {
public:
	static network_friends_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_friends_menu()
		: menu::submenu::submenu() {}
};

namespace network::friends::vars {
	struct variables {
		std::vector<uint64_t> m_queue;
		std::vector<uint64_t> m_image_queue;
	};

	extern variables m_vars;
}