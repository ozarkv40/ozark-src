#include "protection_limits.h"
#include "menu/base/submenu_handler.h"
#include "../protections.h"
#include "limits/protection_message_limit.h"
#include "limits/protection_spawn_rate_limit.h"

using namespace protection::limits::vars;

namespace protection::limits::vars {
	variables m_vars;
}

void protection_limits_menu::load() {
	set_name("Limits");
	set_parent<protection_menu>();

	add_option(submenu_option("Spawn Rate")
		.add_translate()
		.add_submenu<protection_spawn_rate_limit_menu>());

	m_vars.m_text_message_option = add_option(submenu_option("Text Messages")
		.add_translate()
		.add_click([] {
			protection_message_limit_menu::get()->set_name(m_vars.m_text_message_option->get_name().get(), false, false);
			protection::limits::messages::vars::m_vars.m_limit = &m_vars.m_text_message;
		})
		.add_submenu<protection_message_limit_menu>());

	m_vars.m_chat_message_option = add_option(submenu_option("Chat Messages")
		.add_translate()
		.add_click([] {
			protection_message_limit_menu::get()->set_name(m_vars.m_chat_message_option->get_name().get(), false, false);
			protection::limits::messages::vars::m_vars.m_limit = &m_vars.m_chat_message;
		})
		.add_submenu<protection_message_limit_menu>());

	m_vars.m_text_message.m_block_all = util::config::read_bool(get_submenu_name_stack(), "Text", false, { "Block All" });
	m_vars.m_text_message.m_block_spoofed = util::config::read_bool(get_submenu_name_stack(), "Text", false, { "Block Spoofed" });
	m_vars.m_text_message.m_delay = util::config::read_int(get_submenu_name_stack(), "Text", 0, { "Delay" });

	m_vars.m_chat_message.m_block_all = util::config::read_bool(get_submenu_name_stack(), "Chat", false, { "Block All" });
	m_vars.m_chat_message.m_block_spoofed = util::config::read_bool(get_submenu_name_stack(), "Chat", false, { "Block Spoofed" });
	m_vars.m_chat_message.m_delay = util::config::read_int(get_submenu_name_stack(), "Chat", 0, { "Delay" });
}

void protection_limits_menu::update() {}

void protection_limits_menu::update_once() {
	util::config::write_bool(get_submenu_name_stack(), "Text", m_vars.m_text_message.m_block_all, { "Block All" });
	util::config::write_bool(get_submenu_name_stack(), "Text", m_vars.m_text_message.m_block_spoofed, { "Block Spoofed" });
	util::config::write_int(get_submenu_name_stack(), "Text", m_vars.m_text_message.m_delay, { "Delay" });

	util::config::write_bool(get_submenu_name_stack(), "Chat", m_vars.m_chat_message.m_block_all, { "Block All" });
	util::config::write_bool(get_submenu_name_stack(), "Chat", m_vars.m_chat_message.m_block_spoofed, { "Block Spoofed" });
	util::config::write_int(get_submenu_name_stack(), "Chat", m_vars.m_chat_message.m_delay, { "Delay" });
}

void protection_limits_menu::feature_update() {}

protection_limits_menu* g_instance;
protection_limits_menu* protection_limits_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new protection_limits_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}