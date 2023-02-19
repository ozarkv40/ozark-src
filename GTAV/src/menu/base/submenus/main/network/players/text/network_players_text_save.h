#pragma once
#include "menu/base/submenu.h"

class network_players_text_save_menu : public menu::submenu::submenu {
public:
	static network_players_text_save_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_players_text_save_menu()
		: menu::submenu::submenu() {}
};

namespace network::players::text::save::vars {
	struct variables {
		std::vector<std::pair<std::string, std::string>> m_messages;
	};

	extern variables m_vars;
}