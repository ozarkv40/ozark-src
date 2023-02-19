#include "network_session_excludes.h"
#include "menu/base/submenu_handler.h"
#include "../network_session.h"

using namespace network::session::excludes::vars;

namespace network::session::excludes::vars {
	variables m_vars;
}

void network_session_excludes_menu::load() {
	set_name("Excludes");
	set_parent<network_session_menu>();

	add_option(toggle_option("Exclude Self")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_self));

	add_option(toggle_option("Exclude Friends")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_friends));

	add_option(toggle_option("Exclude Modders")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_modders));

	add_option(toggle_option("Exclude Host")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_host));

	add_option(toggle_option("Exclude Script host")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_script_host));

	add_option(toggle_option("Exclude Rockstar Developers")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_rockstar_developers));
}

void network_session_excludes_menu::update() {}

void network_session_excludes_menu::update_once() {}

void network_session_excludes_menu::feature_update() {}

network_session_excludes_menu* g_instance;
network_session_excludes_menu* network_session_excludes_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_session_excludes_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}