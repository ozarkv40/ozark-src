#include "protection_presence_events.h"
#include "menu/base/submenu_handler.h"
#include "../protections.h"

using namespace protection::events::presence::vars;

namespace protection::events::presence::vars {
	variables m_vars;

	struct context {
		std::string m_name;
		protection_context* m_context;
	};

	scroll_struct<int> types[] = {
		{ localization("Off", true), 0 },
		{ localization("Notify", true), 0 },
		{ localization("Block", true), 0 },
		{ localization("Block + Notify", true), 0 }
	};

	context items[] = {
		{ "Text Message", &m_vars.m_text_message },
		{ "Crew Message", &m_vars.m_crew_message },
		{ "Game Invite", &m_vars.m_game_invite },
		{ "Game Server Rewards", &m_vars.m_game_server_awards },
		{ "Admin Invite", &m_vars.m_admin_invite },
		{ "Stat Update", & m_vars.m_stat_update }
	};
}

void protection_presence_events_menu::load() {
	set_name("Presence Events");
	set_parent<protection_menu>();

	for (context& c : items) {
		add_string(c.m_name);
		c.m_context->m_var = util::config::read_int(get_submenu_name_stack(), c.m_name, c.m_context->m_var);
	}
}

void protection_presence_events_menu::update() {}

void protection_presence_events_menu::update_once() {
	clear_options(0);

	for (context& c : items) {
		add_option(scroll_option<int>(SCROLL, get_string(c.m_name))
			.add_scroll(c.m_context->m_var, 0, NUMOF(types), types)
			.add_click([=] { util::config::write_int(get_submenu_name_stack(), c.m_name, c.m_context->m_var); }));
	}
}

void protection_presence_events_menu::feature_update() {}

protection_presence_events_menu* g_instance;
protection_presence_events_menu* protection_presence_events_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new protection_presence_events_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}