#include "network_account_wins_losses.h"
#include "menu/base/submenu_handler.h"
#include "../network_account.h"
#include "wins/network_account_wins_losses_edit.h"

using namespace network::account::wins::losses::vars;

namespace network::account::wins::losses::vars {
	variables m_vars;

	void set(std::string win, std::string loss, bool total = false) {
		network::account::wins::losses::edit::vars::m_vars.m_wins.first = win;
		network::account::wins::losses::edit::vars::m_vars.m_losses.first = loss;
		network::account::wins::losses::edit::vars::m_vars.m_total = total;
	}
}

void network_account_wins_losses_menu::load() {
	set_name("Wins and Losses");
	set_parent<network_account_menu>();

	add_option(submenu_option("Races")
		.add_translate()
		.add_submenu<network_account_wins_losses_edit_menu>()
		.add_click([] { set("MPPLY_TOTAL_RACES_WON", "MPPLY_TOTAL_RACES_LOST"); }));

	add_option(submenu_option("Deathmatch")
		.add_translate()
		.add_submenu<network_account_wins_losses_edit_menu>()
		.add_click([] { set("MPPLY_TOTAL_DEATHMATCH_WON", "MPPLY_TOTAL_DEATHMATCH_LOST"); }));

	add_option(submenu_option("Team Deathmatch")
		.add_translate()
		.add_submenu<network_account_wins_losses_edit_menu>()
		.add_click([] { set("MPPLY_TOTAL_TDEATHMATCH_WON", "MPPLY_TOTAL_TDEATHMATCH_LOST"); }));

	add_option(submenu_option("Darts")
		.add_translate()
		.add_submenu<network_account_wins_losses_edit_menu>()
		.add_click([] { set("MPPLY_DARTS_TOTAL_WINS", "MPPLY_DARTS_TOTAL_MATCHES", true); }));

	add_option(submenu_option("Arm Wrestling")
		.add_translate()
		.add_submenu<network_account_wins_losses_edit_menu>()
		.add_click([] { set("MPPLY_ARMWRESTLING_TOTAL_WINS", "MPPLY_ARMWRESTLING_TOTAL_MATCH", true); }));

	add_option(submenu_option("Tennis")
		.add_translate()
		.add_submenu<network_account_wins_losses_edit_menu>()
		.add_click([] { set("MPPLY_TENNIS_MATCHES_WON", "MPPLY_TENNIS_MATCHES_LOST"); }));

	add_option(submenu_option("Golf")
		.add_translate()
		.add_submenu<network_account_wins_losses_edit_menu>()
		.add_click([] { set("MPPLY_GOLF_WINS", "MPPLY_GOLF_LOSSES"); }));

	add_option(submenu_option("Shooting Range")
		.add_translate()
		.add_submenu<network_account_wins_losses_edit_menu>()
		.add_click([] { set("MPPLY_SHOOTINGRANGE_WINS", "MPPLY_SHOOTINGRANGE_LOSSES"); }));
}

void network_account_wins_losses_menu::update() {}

void network_account_wins_losses_menu::update_once() {}

void network_account_wins_losses_menu::feature_update() {}

network_account_wins_losses_menu* g_instance;
network_account_wins_losses_menu* network_account_wins_losses_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_account_wins_losses_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}