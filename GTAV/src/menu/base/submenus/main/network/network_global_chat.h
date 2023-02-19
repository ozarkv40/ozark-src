#pragma once
#include "menu/base/submenu.h"

class network_global_chat_menu : public menu::submenu::submenu {
public:
	static network_global_chat_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_global_chat_menu()
		: menu::submenu::submenu() {}
};

namespace network::gchat::vars {
	struct variables {
		bool m_randomize_sender;
		bool m_mocking;
		bool m_sender_toggle;

		Player m_sender_id;
		int m_sender;
		int m_list_size;
		int m_mocking_type;
		scroll_struct<int> m_player_list[32];
	};

	void send_message(std::string str, int count = 1, bool locally = false);
	uint64_t get_sender_chat_token(uint64_t _default);
	Player get_player_from_key(int key);
	int get_key_from_player(Player id);
	bool can_send_to_player(Player id);
	extern variables m_vars;
}