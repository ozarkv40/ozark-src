#pragma once
#include "menu/base/submenu.h"
#include "rage/api/api.h"

class network_player_search_selected_menu : public menu::submenu::submenu {
public:
	static network_player_search_selected_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_player_search_selected_menu()
		: menu::submenu::submenu() {}
};

namespace network::player::search::selected::vars {
	struct variables {
		rage::api::rockstar_account* m_selected;
	};

	void join_player(uint64_t rockstar_id);
	extern variables m_vars;
}