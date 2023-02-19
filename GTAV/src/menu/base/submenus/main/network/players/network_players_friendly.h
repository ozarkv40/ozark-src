#pragma once
#include "menu/base/submenu.h"
#include "menu/base/util/player_manager.h"

class network_players_friendly_menu : public menu::submenu::submenu {
public:
	static network_players_friendly_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_players_friendly_menu()
		: menu::submenu::submenu()
	{}
};

namespace network::players::friendly::vars {
	struct variables {
		bool m_demi_godmode;
		bool m_off_the_radar;
		bool m_disable_police;
		bool m_kill_killers;
		bool m_force_visible;

		int m_bodyguard_count = 1;
		int m_commend;
		int m_outfit;
	};

	void off_the_radar(menu::player::player_context& player);
	void disable_police(menu::player::player_context& player);
	void spawn_bodyguards(menu::player::player_context& player, int count);
	void commend(menu::player::player_context& player, int id);
	void parachute(menu::player::player_context& player);
	void give_all_weapons(menu::player::player_context& player);
	void give_all_attachments(menu::player::player_context& player);
	extern variables m_vars;
}