#pragma once
#include "menu/base/submenu.h"

class player_menu : public menu::submenu::submenu {
public:
	static player_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	player_menu()
		: menu::submenu::submenu() {}
};

namespace player::vars {
	struct variables {
		bool m_godmode;
		bool m_disable_police;
		bool m_disable_ragdoll;
		bool m_cops_turn_blind_eye;
		bool m_off_the_radar;
		bool m_reveal_hidden_players;
		bool m_reduced_collision;
		bool m_invisibility;
		bool m_superman;
		bool m_badsport;
		bool m_swim_anywhere;
		bool m_breathe_fire;
		bool m_peds_ingore_player;
		bool m_kill_killers;

		int m_breathe_fire_handle;
		int m_invisibility_var;
		int m_merryweather;
	};

	extern variables m_vars;
}