#pragma once
#include "menu/base/submenu.h"
#include "rage/api/api.h"

class network_player_search_menu : public menu::submenu::submenu {
public:
	static network_player_search_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_player_search_menu()
		: menu::submenu::submenu() {}
};

namespace network::player::search::vars {
	struct variables {
		std::vector<rage::api::rockstar_account> m_accounts;
		int m_current_page = 0;
		int m_current_offset = 0;
		int m_total = 0;
		int m_total_pages_requested = 0;
		bool m_processing_next_page = false;

		std::string m_name = "";
		uint64_t m_rockstar_id = 0;

		std::vector<uint64_t> m_queue;
		std::vector<uint64_t> m_image_queue;
	};

	extern variables m_vars;
}