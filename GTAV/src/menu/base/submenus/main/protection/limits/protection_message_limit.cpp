#include "protection_message_limit.h"
#include "menu/base/submenu_handler.h"
#include "global/lists.h"

using namespace protection::limits::messages::vars;

namespace protection::limits::messages::vars {
	variables m_vars;
}

void protection_message_limit_menu::load() {
	set_parent<protection_limits_menu>();

	add_string("Block Everything");
	add_string("Block Spoofed");
	add_string("Rate Limit");
}

void protection_message_limit_menu::update() {}

void protection_message_limit_menu::update_once() {
	clear_options(0);

	add_option(toggle_option(get_string("Block Everything"))
		.add_toggle(m_vars.m_limit->m_block_all));

	add_option(toggle_option(get_string("Block Spoofed"))
		.add_toggle(m_vars.m_limit->m_block_spoofed));

	add_option(scroll_option<uint32_t>(SCROLL, get_string("Rate Limit"))
		.add_scroll(m_vars.m_limit->m_delay, 0, NUMOF(global::lists::g_timers), global::lists::g_timers));
}

void protection_message_limit_menu::feature_update() {}

protection_message_limit_menu* g_instance;
protection_message_limit_menu* protection_message_limit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new protection_message_limit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}