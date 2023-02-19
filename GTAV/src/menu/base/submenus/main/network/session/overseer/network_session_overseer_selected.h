#pragma once
#include "menu/base/submenu.h"

class network_session_overseer_selected_menu : public menu::submenu::submenu {
public:
	static network_session_overseer_selected_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_session_overseer_selected_menu()
		: menu::submenu::submenu() {}
};

namespace network::session::overseer::selected::vars {
	struct variables {
		std::size_t m_selected;

		bool m_enabled;
		bool m_notify;
		bool m_block_join;
		bool m_crash;
		bool m_kick;
		bool m_cage;
		bool m_kick_from_vehicle;
		bool m_set_on_fire;
		bool m_ragdoll;
		bool m_glitch_physics;
		bool m_black_screen;
		bool m_blame;
		bool m_give_wanted_level;
		bool m_send_to_island;
		bool m_remove_weapons;
		bool m_hostile_clone;
		bool m_bail;
		bool m_explode;
	};

	extern variables m_vars;
}