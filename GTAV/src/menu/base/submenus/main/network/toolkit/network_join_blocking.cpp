#include "network_join_blocking.h"
#include "menu/base/submenu_handler.h"
#include "../network_host_toolkit.h"
#include "blocking/network_join_blocking_edit.h"
#include "blocking/network_join_blocking_add.h"
#include "blocking/network_join_blocking_manual.h"

using namespace network::htoolkit::blocking::vars;

namespace network::htoolkit::blocking::vars {
	variables m_vars;

	scroll_struct<int> who_can_join[] = {
		{ localization("Anybody", true), 0 },
		{ localization("Nobody", true), 1 },
		{ localization("Friends Only", true), 2 },
	};

	const char* strings[] = {
		"Spoofed - Host Token",
		"Spoofed - Rockstar ID",
		"Spoofed - Name",
		"Spoofed - IP",
		"Rockstar Developer"
	};
}

void network_join_blocking_menu::load() {
	set_name("Join Blocking");
	set_parent<network_host_toolkit_menu>();

	for (int i = 0; i < NUMOF(strings); i++) {
		m_vars.m_responses[i].m_enabled = util::config::read_bool(get_submenu_name_stack(), "Toggled", false, { strings[i] });
		m_vars.m_responses[i].m_notify = util::config::read_bool(get_submenu_name_stack(), "Notify", true, { strings[i] });
		m_vars.m_responses[i].m_context.m_selected = util::config::read_int(get_submenu_name_stack(), "Selected", 1, { strings[i] });
	}

	add_option(submenu_option("Manual User Block")
		.add_translate().add_hotkey()
		.add_submenu<network_join_blocking_manual_menu>()
		.add_tooltip("Manually add a user to be blocked from joining"));

	add_option(scroll_option<int>(SCROLL, "Who Can Join?")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_who_can_join, 0, NUMOF(who_can_join), who_can_join).add_savable(get_submenu_name_stack())
		.add_tooltip("Who can join your session?"));

	add_option(break_option("Block Spoofed Joiners")
		.add_translate());

	add_option(submenu_option("Spoofed - Host Token")
		.add_translate().add_hotkey()
		.add_click_this([] (submenu_option* option) {
			network_join_blocking_edit_menu::get()->set_name(option->get_name().get(), false, false);
			network::htoolkit::blocking::edit::vars::m_vars.m_selected = &m_vars.m_responses[TOOLKIT_NEXT_SESSION_HOST];
		})
		.add_submenu<network_join_blocking_edit_menu>()
		.add_tooltip("Blocks most force host spoofs from joining the session. You have to be host!"));

	add_option(submenu_option("Spoofed - Rockstar ID")
		.add_translate().add_hotkey()
		.add_click_this([](submenu_option* option) {
			network_join_blocking_edit_menu::get()->set_name(option->get_name().get(), false, false);
			network::htoolkit::blocking::edit::vars::m_vars.m_selected = &m_vars.m_responses[TOOLKIT_RID];
		})
		.add_submenu<network_join_blocking_edit_menu>()
		.add_tooltip("Blocks most Rockstar ID spoofs from joining the session. You have to be host!"));

	add_option(submenu_option("Spoofed - Name")
		.add_translate().add_hotkey()
		.add_click_this([](submenu_option* option) {
			network_join_blocking_edit_menu::get()->set_name(option->get_name().get(), false, false);
			network::htoolkit::blocking::edit::vars::m_vars.m_selected = &m_vars.m_responses[TOOLKIT_NAME];
		})
		.add_submenu<network_join_blocking_edit_menu>()
		.add_tooltip("Blocks obvious name spoofs from joining the session. You have to be host!"));

	add_option(submenu_option("Spoofed - IP")
		.add_translate().add_hotkey()
		.add_click_this([](submenu_option* option) {
			network_join_blocking_edit_menu::get()->set_name(option->get_name().get(), false, false);
			network::htoolkit::blocking::edit::vars::m_vars.m_selected = &m_vars.m_responses[TOOLKIT_IP];
		})
		.add_submenu<network_join_blocking_edit_menu>()
		.add_tooltip("Blocks IP spoofs from joining the session. You have to be host!"));

	add_option(submenu_option("Rockstar Developer")
		.add_translate().add_hotkey()
		.add_click_this([] (submenu_option* option) {
			network_join_blocking_edit_menu::get()->set_name(option->get_name().get(), false, false);
			network::htoolkit::blocking::edit::vars::m_vars.m_selected = &m_vars.m_responses[TOOLKIT_DEV];
		})
		.add_submenu<network_join_blocking_edit_menu>()
		.add_tooltip("Blocks players joining with developer flag set (and potentially real rockstar staff, be careful!). You have to be host!"));
}

void network_join_blocking_menu::update() {}

void network_join_blocking_menu::update_once() {
	for (int i = 0; i < NUMOF(strings); i++) {
		util::config::write_bool(get_submenu_name_stack(), "Toggled", m_vars.m_responses[i].m_enabled, { strings[i] });
		util::config::write_bool(get_submenu_name_stack(), "Notify", m_vars.m_responses[i].m_notify, { strings[i] });
		util::config::write_int(get_submenu_name_stack(), "Selected", m_vars.m_responses[i].m_context.m_selected, { strings[i] });
	}
}

void network_join_blocking_menu::feature_update() {}

network_join_blocking_menu* g_instance;
network_join_blocking_menu* network_join_blocking_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_join_blocking_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}