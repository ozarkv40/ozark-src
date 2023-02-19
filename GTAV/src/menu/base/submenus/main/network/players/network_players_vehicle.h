#pragma once
#include "menu/base/submenu.h"

class network_players_vehicle_menu : public menu::submenu::submenu {
public:
	static network_players_vehicle_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_players_vehicle_menu()
		: menu::submenu::submenu() {}
};

namespace network::players::vehicle::vars {
	struct variables {
		bool m_vehicle_godmode = false;
		bool m_vehicle_disable_collision = false;
		bool m_vehicle_slippy_wheels = false;
		bool m_vehicle_freeze = false;

		int m_vehicle_upgrades;
		int m_vehicle_downgrades;
		int m_vehicle_acrobatics;
		int m_vehicle_boost_forwards;
		int m_vehicle_boost_backwards;
		int m_vehicle_rotate;
	};

	extern variables m_vars;
}