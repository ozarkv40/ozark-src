#pragma once
#include "menu/base/submenu.h"
#include "menu/base/util/player_manager.h"
#include <unordered_map>

class network_players_removals_menu : public menu::submenu::submenu {
public:
	static network_players_removals_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_players_removals_menu()
		: menu::submenu::submenu() {}
};

namespace network::players::removals::vars {
	struct variables {
		bool m_break_nodes = false;
		bool m_session_crash = false;
		bool m_targeted_crash = false;

		int m_crash_type;
		uint32_t m_break_node_threads[2] = { 0, 0 };
		uint32_t m_session_crash_timeout = 0;
		uint32_t m_targeted_crash_timeout = 0;
		uint64_t m_targeted_crash_target = 0;
		int m_targeted_crash_target_id = 0;

		std::unordered_map<rage::network::net_object*, uint64_t> m_broken_entities;
	};
	
	void session_host_kick(menu::player::player_context& player, bool everyone = false);
	void script_host_kick(menu::player::player_context& player, bool everyone = false);
	void break_freemode_kick(menu::player::player_context& player, bool everyone = false);
	void crash(menu::player::player_context& player, bool everyone = false);
	extern variables m_vars;
}