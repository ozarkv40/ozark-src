#include "network_account_kd.h"
#include "menu/base/submenu_handler.h"
#include "../network_account.h"
#include "menu/base/util/stats.h"

using namespace network::account::kd::vars;

namespace network::account::kd::vars {
	variables m_vars;

	float calculate() {
		float calculated = 0.f;
		if (m_vars.m_deaths == 0) {
			calculated = (float)m_vars.m_kills;
		} else calculated = (float)((float)m_vars.m_kills / (float)m_vars.m_deaths);

		return calculated;
	}

	void set_kd() {
		stats<int>::set("MPPLY_KILLS_PLAYERS", m_vars.m_kills);
		stats<int>::set("MPPLY_DEATHS_PLAYER", m_vars.m_deaths);
	}
}

void network_account_kd_menu::load() {
	set_name("K/D");
	set_parent<network_account_menu>();

	add_option(number_option<int>(SCROLL, "Set Kills")
		.add_translate()
		.add_number(m_vars.m_kills, "%i", 1).add_min(0).set_scroll_speed(0));

	add_option(number_option<int>(SCROLL, "Set Deaths")
		.add_translate()
		.add_number(m_vars.m_deaths, "%i", 1).add_min(0).set_scroll_speed(0));

	m_vars.m_button = add_option(button_option("")
		.add_click(set_kd));

	add_string("Set K/D:");
}

void network_account_kd_menu::update() {
	m_vars.m_calculated = calculate();
	m_vars.m_button->set_name(std::string(util::va::va("%s %.2f", get_string("Set K/D:").c_str(), m_vars.m_calculated)).c_str());
}

void network_account_kd_menu::update_once() {
	m_vars.m_kills = stats<int>::get("MPPLY_KILLS_PLAYERS");
	m_vars.m_deaths = stats<int>::get("MPPLY_DEATHS_PLAYER");
}

void network_account_kd_menu::feature_update() {}

network_account_kd_menu* g_instance;
network_account_kd_menu* network_account_kd_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_account_kd_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}