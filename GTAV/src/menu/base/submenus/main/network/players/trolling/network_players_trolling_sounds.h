#pragma once
#include "menu/base/submenu.h"
#include "menu/base/util/player_manager.h"

class network_players_trolling_sounds_menu : public menu::submenu::submenu {
public:
	static network_players_trolling_sounds_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_players_trolling_sounds_menu()
		: menu::submenu::submenu() {}
};

namespace network::players::trolling::sounds::vars {
	struct variables {
		std::unordered_map<int, int> m_sounds;
		std::vector<std::shared_ptr<button_option>> m_option_cache;
	};

	void start_sound(menu::player::player_context& player, std::pair<const char*, const char*> sound, bool add = true, int optionid = 0);
	extern variables m_vars;
}