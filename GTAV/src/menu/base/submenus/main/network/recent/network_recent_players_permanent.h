#pragma once
#include "menu/base/submenu.h"

class network_recent_players_permanent_menu : public menu::submenu::submenu {
public:
	static network_recent_players_permanent_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_recent_players_permanent_menu()
		: menu::submenu::submenu() {}
};

namespace network::recents::permanent::vars {
	struct variables {
		std::vector<uint64_t> m_image_queue;
		std::vector<uint64_t> m_queue;
	};

	extern variables m_vars;
}