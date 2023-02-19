#pragma once
#include "menu/base/submenu.h"
#include "menu/base/submenus/main/helper/helper_esp.h"

class network_players_selected_menu : public menu::submenu::submenu {
public:
	static network_players_selected_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_players_selected_menu()
		: menu::submenu::submenu() {}
};

namespace network::players::selected::vars {
	struct variables {
		helper::esp::vars::esp_context m_session_esp = { true };
	};

	extern variables m_vars;
}