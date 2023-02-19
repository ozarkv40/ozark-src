#pragma once
#include "menu/base/submenu.h"
#include "rage/types/network_types.h"
#include <vector>
#include <unordered_map>

class network_players_commands_menu : public menu::submenu::submenu {
public:
	static network_players_commands_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_players_commands_menu()
		: menu::submenu::submenu() {}
};

namespace network::players::commands::vars {
	struct variables {
		bool m_chat_commands;
		std::unordered_map<int, bool> m_chat_command;
	};

	void call_command(const char* command_name, rage::network::net_game_player* player, std::vector<std::string> tokens);
	extern variables m_vars;
}