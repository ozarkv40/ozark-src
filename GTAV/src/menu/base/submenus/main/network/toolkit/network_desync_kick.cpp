#include "network_desync_kick.h"
#include "menu/base/submenu_handler.h"
#include "../network_host_toolkit.h"

using namespace network::htoolkit::desync::vars;

namespace network::htoolkit::desync::vars {
	variables m_vars;
}

void network_desync_kick_menu::load() {
	set_name("Desync Kicks");
	set_parent<network_host_toolkit_menu>();

	add_option(toggle_option("Block")
		.add_translate()
		.add_toggle(m_vars.m_block).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Redirect")
		.add_translate()
		.add_toggle(m_vars.m_redirect).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Notify")
		.add_translate()
		.add_toggle(m_vars.m_notify).add_savable(get_submenu_name_stack()));
}

void network_desync_kick_menu::update() {}

void network_desync_kick_menu::update_once() {}

void network_desync_kick_menu::feature_update() {}

network_desync_kick_menu* g_instance;
network_desync_kick_menu* network_desync_kick_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_desync_kick_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}