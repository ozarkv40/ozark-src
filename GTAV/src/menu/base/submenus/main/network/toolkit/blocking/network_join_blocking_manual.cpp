#include "network_join_blocking_manual.h"
#include "menu/base/submenu_handler.h"
#include "../network_join_blocking.h"
#include "network_join_blocking_add.h"
#include "network_join_blocking_manual_edit.h"
#include "network_join_blocking_manual_load.h"

using namespace network::htoolkit::blocking::manual::vars;

namespace network::htoolkit::blocking::manual::vars {
	variables m_vars;
}

void network_join_blocking_manual_menu::load() {
	set_name("Manual User Block");
	set_parent<network_join_blocking_menu>();

	add_option(submenu_option("Save and Load")
		.add_translate().add_hotkey()
		.add_submenu<network_join_blocking_manual_load_menu>());

	add_option(submenu_option("Add User Block")
		.add_translate().add_hotkey()
		.add_submenu<network_join_blocking_add_menu>()
		.add_click([] {
			network::htoolkit::blocking::add::vars::m_vars.m_type = 0;
			network::htoolkit::blocking::add::vars::m_vars.m_rockstar_id = 0;
			network::htoolkit::blocking::add::vars::m_vars.m_ip = 0;
			network::htoolkit::blocking::add::vars::m_vars.m_name[0] = '\0';
			network::htoolkit::blocking::add::vars::m_vars.m_enabled = true;
			network::htoolkit::blocking::add::vars::m_vars.m_response = 0;
		}));

	add_option(break_option("Users")
		.add_translate());

	network_join_blocking_manual_edit_menu::get();

	add_string("~m~None");
}

void network_join_blocking_manual_menu::update() {}

void network_join_blocking_manual_menu::update_once() {
	clear_options(3);

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

		add_option(submenu_option(option_name)
			.add_hotkey()
			.add_click([&] { network::htoolkit::blocking::manual::edit::vars::m_vars.m_selected = &user;  })
			.add_submenu<network_join_blocking_manual_edit_menu>());
	}

	if (network::htoolkit::blocking::vars::m_vars.m_blocked_users.empty()) {
		add_option(button_option(get_string("~m~None")).ref());
	}
}

void network_join_blocking_manual_menu::feature_update() {}

network_join_blocking_manual_menu* g_instance;
network_join_blocking_manual_menu* network_join_blocking_manual_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_join_blocking_manual_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}