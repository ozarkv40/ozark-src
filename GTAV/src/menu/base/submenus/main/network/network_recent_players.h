#pragma once
#include "menu/base/submenu.h"

class network_recent_players_menu : public menu::submenu::submenu {
public:
	static network_recent_players_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_recent_players_menu()
		: menu::submenu::submenu() {}
};

namespace network::recents::vars {
	struct recent_player {
		char m_name[0x20];
		char m_ip[16];
		char m_first_encountered[0x50];
		char m_last_encountered[0x50];
		uint64_t m_rockstar_id;
		int m_internal_encountered;
	};

	struct variables {
		std::vector<uint64_t> m_queue;
		std::vector<uint64_t> m_image_queue;
		std::vector<std::pair<std::string, recent_player>> m_players;
		std::vector<std::pair<std::string, recent_player>> m_permanent_players;
		std::vector<std::pair<std::string, recent_player>>* m_selected_list;

		bool m_update_players = true;
		bool m_update_online = true;
	};

	void save(std::string name, std::string ip, uint64_t rockstar_id);
	extern variables m_vars;
}