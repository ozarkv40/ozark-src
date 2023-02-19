#include "network_join_blocking_manual_edit.h"
#include "menu/base/submenu_handler.h"
#include "network_join_blocking_manual.h"
#include "network_join_blocking_edit.h"
#include "network_join_blocking_add.h"
#include "util/util.h"

using namespace network::htoolkit::blocking::manual::edit::vars;

namespace network::htoolkit::blocking::manual::edit::vars {
	variables m_vars;
}

void network_join_blocking_manual_edit_menu::load() {
	set_name("Manual User Block");
	set_parent<network_join_blocking_manual_menu>();

	add_string("Type");
	add_string("Input Name");
	add_string("Input Rockstar ID");
	add_string("Input IP");
	add_string("Enabled");
}

void network_join_blocking_manual_edit_menu::update() {}

void network_join_blocking_manual_edit_menu::update_once() {
	clear_options(0);

	for (int i = 0; i < NUMOF(network::htoolkit::blocking::edit::vars::responses); i++) {
		if (network::htoolkit::blocking::edit::vars::responses[i].m_result.second == m_vars.m_selected->m_response) {
			m_vars.m_response = i;
			break;
		}
	}

	m_vars.m_type = m_vars.m_selected->m_type - 1;

	add_option(scroll_option<int>(SCROLL, get_string("Type"))
		.add_scroll(m_vars.m_type, 0, NUMOF(network::htoolkit::blocking::add::vars::types), network::htoolkit::blocking::add::vars::types)
		.add_click([this] { update_once(); m_vars.m_selected->m_type = m_vars.m_type + 1; }));

	switch (m_vars.m_type) {
		case 0:
			add_option(button_option(get_string("Input Rockstar ID"))
				.add_keyboard("Input Rockstar ID of the users account", 30, [](button_option* _this, const char* result) { char* endptr = nullptr; m_vars.m_selected->m_rockstar_id = strtoull(result, &endptr, 10); }));

			break;

		case 1:
			add_option(button_option(get_string("Input Name"))
				.add_keyboard("Input name of the users account", 30, [](button_option* _this, const char* result) { strcpy_s(m_vars.m_selected->m_name, result); }));

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

					m_vars.m_selected->m_ip = *(uint32_t*)&buffer[0];
				}
			}));

			break;
	}

	add_option(scroll_option<std::pair<std::string, eJoinResponses>>(SCROLL, "Message")
		.add_scroll(m_vars.m_response, 0, NUMOF(network::htoolkit::blocking::edit::vars::responses), network::htoolkit::blocking::edit::vars::responses)
		.add_click([] { m_vars.m_selected->m_response = network::htoolkit::blocking::edit::vars::responses[m_vars.m_response].m_result.second; })
		.add_update([](scroll_option<std::pair<std::string, eJoinResponses>>* option, int pos) { option->set_tooltip(network::htoolkit::blocking::edit::vars::responses[m_vars.m_response].m_result.first); }));

	add_option(toggle_option(get_string("Enabled"))
		.add_toggle(m_vars.m_selected->m_enabled));
}

void network_join_blocking_manual_edit_menu::feature_update() {}

network_join_blocking_manual_edit_menu* g_instance;
network_join_blocking_manual_edit_menu* network_join_blocking_manual_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_join_blocking_manual_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}