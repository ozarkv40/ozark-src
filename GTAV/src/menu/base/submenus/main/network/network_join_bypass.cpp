#include "network_join_bypass.h"
#include "menu/base/submenu_handler.h"
#include "../network.h"

using namespace network::bypass::vars;

namespace network::bypass::vars {
	variables m_vars;
}

void network_join_bypass_menu::load() {
	set_name("Join Bypass");
	set_parent<network_menu>();

	add_option(toggle_option("Invite Only")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_invite_only).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Friend Only")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_friend_only).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Crew Only")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_crew_only).add_savable(get_submenu_name_stack()));
}

void network_join_bypass_menu::update() {}

void network_join_bypass_menu::update_once() {}

void network_join_bypass_menu::feature_update() {}

network_join_bypass_menu* g_instance;
network_join_bypass_menu* network_join_bypass_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_join_bypass_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}