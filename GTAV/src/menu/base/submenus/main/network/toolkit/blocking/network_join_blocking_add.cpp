#include "network_join_blocking_add.h"
#include "menu/base/submenu_handler.h"
#include "../network_join_blocking.h"
#include "network_join_blocking_manual.h"
#include "network_join_blocking_edit.h"
#include "util/util.h"

using namespace network::htoolkit::blocking::add::vars;

namespace network::htoolkit::blocking::add::vars {
	variables m_vars;

	scroll_struct<int> types[] = {
		{ localization("Rockstar ID", true), 0 },
		{ localization("Name", true), 0 },
		{ localization("IP", true), 0 }
	};

	void add_block() {
		network::htoolkit::blocking::vars::user_block user;
		user.m_type = m_vars.m_type + 1;
		user.m_rockstar_id = m_vars.m_rockstar_id;
		user.m_ip = m_vars.m_ip;
		user.m_response = network::htoolkit::blocking::edit::vars::responses[m_vars.m_response].m_result.second;
		user.m_enabled = m_vars.m_enabled;
		strcpy_s(user.m_name, m_vars.m_name);
		network::htoolkit::blocking::vars::m_vars.m_blocked_users.push_back(user);

		menu::submenu::handler::set_submenu_previous(false);
	}

	std::string get_tooltip_str() {
		char option_name[128];

		switch (m_vars.m_type) {
			case 0: // rid
				sprintf_s(option_name, "[Rockstar ID] %lli", m_vars.m_rockstar_id);
				break;

			case 1: // name
				sprintf_s(option_name, "[NAME] %s", m_vars.m_name);
				break;

			case 2: // IP
				sprintf_s(option_name, "[IP] %i.%i.%i.%i", ((m_vars.m_ip & 0xFF000000) >> 24), ((m_vars.m_ip & 0xFF0000) >> 16), ((m_vars.m_ip & 0xFF00) >> 8), (m_vars.m_ip & 0xFF));
				break;
		}

		return option_name;
	}
}

void network_join_blocking_add_menu::load() {
	set_name("Add User Block");
	set_parent<network_join_blocking_manual_menu>();

	add_string("Type");
	add_string("Input Name");
	add_string("Input Rockstar ID");
	add_string("Input IP");
	add_string("Enabled");
	add_string("Add Block");
	add_string("Message");
}

void network_join_blocking_add_menu::update() {}

void network_join_blocking_add_menu::update_once() {
	clear_options(0);

	add_option(scroll_option<int>(SCROLL, get_string("Type"))
		.add_scroll(m_vars.m_type, 0, NUMOF(types), types)
		.add_click([this] { update_once(); })
		.add_update([](scroll_option<int>* option, int pos) { option->set_tooltip(get_tooltip_str()); }));

	switch (m_vars.m_type) {
		case 0:
			add_option(button_option(get_string("Input Rockstar ID"))
				.add_keyboard("Input Rockstar ID of the users account", 30, [](button_option* _this, const char* result) { char* endptr = nullptr; m_vars.m_rockstar_id = strtoull(result, &endptr, 10); })
				.add_update([](button_option* option) { option->set_tooltip(get_tooltip_str()); }));

			break;

		case 1:
			add_option(button_option(get_string("Input Name"))
				.add_keyboard("Input name of the users account", 30, [](button_option* _this, const char* result) { strcpy_s(m_vars.m_name, result); })
				.add_update([](button_option* option) { option->set_tooltip(get_tooltip_str()); }));

			break;

		case 2:
			add_option(button_option(get_string("Input IP"))
				.add_keyboard("Input IP of the users account (format: 1.1.1.1)", 30, [](button_option* _this, const char* result) {
					std::vector<std::string> val = util::split_string(result, ".");
					if (val.size() == 4) {
						uint8_t buffer[4];
						buffer[0] = atoi(val[3].c_str());
						buffer[1] = atoi(val[2].c_str());
						buffer[2] = atoi(val[1].c_str());
						buffer[3] = atoi(val[0].c_str());

						m_vars.m_ip = *(uint32_t*)&buffer[0];
					}
				})
				.add_update([](button_option* option) { option->set_tooltip(get_tooltip_str()); }));

			break;
	}

	add_option(scroll_option<std::pair<std::string, eJoinResponses>>(SCROLL, get_string("Message"))
		.add_scroll(m_vars.m_response, 0, NUMOF(network::htoolkit::blocking::edit::vars::responses), network::htoolkit::blocking::edit::vars::responses)
		.add_update([](scroll_option<std::pair<std::string, eJoinResponses>>* option, int pos) { option->set_tooltip(network::htoolkit::blocking::edit::vars::responses[m_vars.m_response].m_result.first); }));

	add_option(toggle_option(get_string("Enabled"))
		.add_toggle(m_vars.m_enabled)
		.add_update([](toggle_option* option, int pos) { option->set_tooltip(get_tooltip_str()); }));

	add_option(button_option(get_string("Add Block"))
		.add_click(add_block)
		.add_update([](button_option* option) { option->set_tooltip(get_tooltip_str()); }));
}

void network_join_blocking_add_menu::feature_update() {}

network_join_blocking_add_menu* g_instance;
network_join_blocking_add_menu* network_join_blocking_add_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_join_blocking_add_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}