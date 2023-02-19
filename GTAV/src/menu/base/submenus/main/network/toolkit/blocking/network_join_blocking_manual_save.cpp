#include "network_join_blocking_manual_save.h"
#include "menu/base/submenu_handler.h"
#include "network_join_blocking_manual_load.h"

using namespace network::htoolkit::blocking::save::vars;

namespace network::htoolkit::blocking::save::vars {
	variables m_vars;

	std::vector<network::htoolkit::blocking::vars::user_block> get_selected() {
		std::vector<network::htoolkit::blocking::vars::user_block> users;
		
		for (std::size_t i = 0; i < network::htoolkit::blocking::vars::m_vars.m_blocked_users.size(); i++) {
			if (m_vars.m_toggles[i]) {
				users.push_back(network::htoolkit::blocking::vars::m_vars.m_blocked_users[i]);
			}
		}

		return users;
	}
}

void network_join_blocking_manual_save_menu::load() {
	set_name("Save User Blocks");
	set_parent<network_join_blocking_manual_load_menu>();

	add_option(button_option("Save Selected Users")
		.add_translate()
		.add_keyboard("Enter file name", 100, [](button_option* option, const char* result) { network::htoolkit::blocking::load::vars::save_blocks(result, get_selected()); }));

	add_option(break_option("Current Users"));
}

void network_join_blocking_manual_save_menu::update() {}

void network_join_blocking_manual_save_menu::update_once() {
	clear_options(2);

	memset(m_vars.m_toggles, 0, sizeof(m_vars.m_toggles));

	int increment = 0;
	for (network::htoolkit::blocking::vars::user_block& user : network::htoolkit::blocking::vars::m_vars.m_blocked_users) {
		char option_name[128];
		switch (user.m_type) {
			case 1: // rid
				sprintf_s(option_name, "%s[Rockstar ID] %lli", user.m_enabled ? "" : "~m~", user.m_rockstar_id);
				break;

			case 2: // name
				sprintf_s(option_name, "%s[NAME] %s", user.m_enabled ? "" : "~m~", user.m_name);
				break;

			case 3: // IP
				sprintf_s(option_name, "%s[IP] %i.%i.%i.%i", user.m_enabled ? "" : "~m~", ((user.m_ip & 0xFF000000) >> 24), ((user.m_ip & 0xFF0000) >> 16), ((user.m_ip & 0xFF00) >> 8), (user.m_ip & 0xFF));
				break;
		}

		add_option(toggle_option(option_name)
			.add_toggle(m_vars.m_toggles[increment++]));
	}
}

void network_join_blocking_manual_save_menu::feature_update() {}

network_join_blocking_manual_save_menu* g_instance;
network_join_blocking_manual_save_menu* network_join_blocking_manual_save_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_join_blocking_manual_save_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}