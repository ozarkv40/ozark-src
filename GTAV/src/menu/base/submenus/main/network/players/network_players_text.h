#pragma once
#include "menu/base/submenu.h"
#include "menu/base/util/player_manager.h"

class network_players_text_menu : public menu::submenu::submenu {
public:
	static network_players_text_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_players_text_menu()
		: menu::submenu::submenu() {}
};

namespace network::players::text::vars {
	struct variables {
		bool m_sender_toggle;
		bool m_randomize_sender;

		Player m_sender_id;
		int m_sender;
		int m_list_size;
		scroll_struct<int> m_player_list[34];
	};

	void send_text_message(menu::player::player_context& player, menu::player::player_context& sender, const char* message);
	extern variables m_vars;
}