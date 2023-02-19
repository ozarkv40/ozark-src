#pragma once
#include "menu/base/submenu.h"
#include "menu/base/util/player_manager.h"

class network_players_abusive_menu : public menu::submenu::submenu {
public:
	static network_players_abusive_menu* get();

	void load() override;
	void update_once() override;
	void update() override;
	void feature_update() override;

	network_players_abusive_menu()
		: menu::submenu::submenu() {}
};

namespace network::players::abusive::vars {
	struct variables {
		bool m_freeze = false;
		bool m_simple_explode = false;
		bool m_kick_from_vehicle = false;
		bool m_taze = false;
		bool m_ragdoll = false;
		bool m_glitch_physics = false;
		bool m_forcefield = false;
		bool m_rain_rockets = false;
		bool m_always_wanted = false;
		bool m_block_passive = false;
		bool m_cage = false;
		bool m_ceo = false;
		bool m_set_on_fire = false;
		bool m_send_to_island = false;
		bool m_vehicle_ram = false;
		bool m_clone = false;
		bool m_show_message = false;
		bool m_fake_money_drop = false;

		int m_ceo_type = 0;
		int m_cage_type = 0;
		int m_vehicle_ram_type = 0;
		int m_clone_type = 0;
		int m_show_message_type = 0;
	};

	void taze(menu::player::player_context& player);
	void kick_from_vehicle(menu::player::player_context& player);
	void ragdoll(menu::player::player_context& player);
	void glitch_physics(menu::player::player_context& player);
	void rain_rockets(menu::player::player_context& player);
	void give_wanted_level(menu::player::player_context& player, int level);
	void cage_player(menu::player::player_context& player, int type);
	void ceo_ban(menu::player::player_context& player);
	void ceo_kick(menu::player::player_context& player);
	void set_on_fire(menu::player::player_context& player);
	void blame(menu::player::player_context& player);
	void send_to_island(menu::player::player_context& player);
	void ram(menu::player::player_context& player, int type);
	void clone_player(menu::player::player_context& player, int type);
	void send_message(menu::player::player_context& player, int type);

	extern scroll_struct<int> cages[2];
	extern scroll_struct<int> ceos[2];
	extern scroll_struct<int> clone[2];
	extern scroll_struct<int> messages[14];
	extern scroll_struct<uint32_t> ram_vehicles[23];
	extern variables m_vars;
}