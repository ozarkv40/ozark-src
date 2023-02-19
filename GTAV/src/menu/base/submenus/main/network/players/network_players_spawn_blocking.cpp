#include "network_players_spawn_blocking.h"
#include "menu/base/submenu_handler.h"
#include "network_players_selected.h"

using namespace network::players::blocking::vars;

namespace network::players::blocking::vars {
	variables m_vars;

	scroll_struct<int> types[] = {
		{ localization("Entity Creation", true), 0 },
		{ localization("Entity Sync", true), 0 },
	};

	void block_all() {
		memset(menu::player::get_selected_player().m_block_entities[m_vars.m_type], 1, 14);
	}
}

void network_players_spawn_blocking_menu::load() {
	set_name("Spawn Blocking");
	set_parent<network_players_selected_menu>();

	add_option(scroll_option<int>(SCROLL, "Network Type")
		.add_translate()
		.add_scroll(m_vars.m_type, 0, NUMOF(types), types));

	add_option(button_option("Block All")
		.add_translate()
		.add_click(block_all));

	add_option(toggle_option("Automobile")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][0])
		.add_update([](toggle_option* option, int pos) { option->add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][0]); }));

	add_option(toggle_option("Bike")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][1])
		.add_update([](toggle_option* option, int pos) { option->add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][1]); }));

	add_option(toggle_option("Boat")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][2])
		.add_update([](toggle_option* option, int pos) { option->add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][2]); }));

	add_option(toggle_option("Door")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][3])
		.add_update([](toggle_option* option, int pos) { option->add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][3]); }));

	add_option(toggle_option("Helicopter")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][4])
		.add_update([](toggle_option* option, int pos) { option->add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][4]); }));

	add_option(toggle_option("Object")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][5])
		.add_update([](toggle_option* option, int pos) { option->add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][5]); }));

	add_option(toggle_option("Ped")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][6])
		.add_update([](toggle_option* option, int pos) { option->add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][6]); }));

	add_option(toggle_option("Pickup")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][7])
		.add_update([](toggle_option* option, int pos) { option->add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][7]); }));

	add_option(toggle_option("Pickup Placement")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][8])
		.add_update([](toggle_option* option, int pos) { option->add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][8]); }));

	add_option(toggle_option("Plane")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][9])
		.add_update([](toggle_option* option, int pos) { option->add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][9]); }));

	add_option(toggle_option("Submarine")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][10])
		.add_update([](toggle_option* option, int pos) { option->add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][10]); }));

	add_option(toggle_option("Player")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][11])
		.add_update([](toggle_option* option, int pos) { option->add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][11]); }));

	add_option(toggle_option("Trailer")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][12])
		.add_update([](toggle_option* option, int pos) { option->add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][12]); }));

	add_option(toggle_option("Train")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][13])
		.add_update([](toggle_option* option, int pos) { option->add_toggle(menu::player::get_selected_player().m_block_entities[m_vars.m_type][13]); }));
}

void network_players_spawn_blocking_menu::update() {}

void network_players_spawn_blocking_menu::update_once() {}

void network_players_spawn_blocking_menu::feature_update() {}

network_players_spawn_blocking_menu* g_instance;
network_players_spawn_blocking_menu* network_players_spawn_blocking_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_spawn_blocking_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}