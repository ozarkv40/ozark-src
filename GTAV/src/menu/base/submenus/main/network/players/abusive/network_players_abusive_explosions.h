#pragma once
#include "menu/base/submenu.h"

class network_players_abusive_explosions_menu : public menu::submenu::submenu {
public:
	static network_players_abusive_explosions_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_players_abusive_explosions_menu()
		: menu::submenu::submenu() {}
};

namespace network::players::abusive::explosions::vars {
	struct variables {
		int m_explosion_type;
		int m_explosion_visual;

		float m_explosion_radius = 2.f;
		float m_explosion_camera_shake;

		bool m_explosion_sound = true;
		bool m_explosion_loop = false;
	};

	extern variables m_vars;
}