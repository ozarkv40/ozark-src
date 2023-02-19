#include "network_account_wins_losses_edit.h"
#include "menu/base/submenu_handler.h"
#include "../network_account_wins_losses.h"
#include "menu/base/util/stats.h"

using namespace network::account::wins::losses::edit::vars;

namespace network::account::wins::losses::edit::vars {
	variables m_vars;
}

void network_account_wins_losses_edit_menu::load() {
	set_name("Wins and Losses");
	set_parent<network_account_wins_losses_menu>();

	add_option(number_option<int>(SCROLL, "Wins")
		.add_translate()
		.add_number(m_vars.m_wins.second, "%i", 1).add_min(0).add_max(std::numeric_limits<int>::max())
		.add_click([] { stats<int>::set(m_vars.m_wins.first.c_str(), m_vars.m_wins.second); }));

	add_option(number_option<int>(SCROLL, "Losses")
		.add_translate()
		.add_number(m_vars.m_losses.second, "%i", 1).add_min(0).add_max(std::numeric_limits<int>::max())
		.add_click([] { stats<int>::set(m_vars.m_losses.first.c_str(), m_vars.m_losses.second); })
		.add_requirement([] { return !m_vars.m_total; }));

	add_option(number_option<int>(SCROLL, "Matches")
		.add_translate()
		.add_number(m_vars.m_losses.second, "%i", 1).add_min(0).add_max(std::numeric_limits<int>::max())
		.add_click([] { stats<int>::set(m_vars.m_losses.first.c_str(), m_vars.m_losses.second); })
		.add_requirement([] { return m_vars.m_total; }));
}

void network_account_wins_losses_edit_menu::update() {}

void network_account_wins_losses_edit_menu::update_once() {
	m_vars.m_wins.second = stats<int>::get(m_vars.m_wins.first.c_str());
	m_vars.m_losses.second = stats<int>::get(m_vars.m_losses.first.c_str());
}

void network_account_wins_losses_edit_menu::feature_update() {}

network_account_wins_losses_edit_menu* g_instance;
network_account_wins_losses_edit_menu* network_account_wins_losses_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_account_wins_losses_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}