#include "protection_spawn_rate_limit_edit.h"
#include "menu/base/submenu_handler.h"
#include "../protection_spawn_rate_limit.h"
#include "global/lists.h"

using namespace protection::limits::spawn::edit::vars;

namespace protection::limits::spawn::edit::vars {
	variables m_vars;
}

void protection_spawn_rate_limit_edit_menu::load() {
	set_name("Spawn Rate");
	set_parent<protection_spawn_rate_limit_menu>();

	add_string("Model");
	add_string("Comment");
	add_string("Delay Per Spawn");
	add_string("Enabled");
}

void protection_spawn_rate_limit_edit_menu::update() {}

void protection_spawn_rate_limit_edit_menu::update_once() {
	clear_options(0);

	add_option(button_option(util::va::va("%s: 0x%X", get_string("Model").c_str(), protection::limits::spawn::vars::m_vars.m_limits[m_vars.m_selected].m_model)));
	add_option(button_option(util::va::va("%s: %s", get_string("Comment").c_str(), protection::limits::spawn::vars::m_vars.m_limits[m_vars.m_selected].m_comment)));

	add_option(scroll_option<uint32_t>(SCROLL, get_string("Delay Per Spawn"))
		.add_scroll(protection::limits::spawn::vars::m_vars.m_limits[m_vars.m_selected].m_delay, 0, NUMOF(global::lists::g_timers), global::lists::g_timers));

	add_option(toggle_option(get_string("Enabled"))
		.add_toggle(protection::limits::spawn::vars::m_vars.m_limits[m_vars.m_selected].m_enabled));
}

void protection_spawn_rate_limit_edit_menu::feature_update() {}

protection_spawn_rate_limit_edit_menu* g_instance;
protection_spawn_rate_limit_edit_menu* protection_spawn_rate_limit_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new protection_spawn_rate_limit_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}