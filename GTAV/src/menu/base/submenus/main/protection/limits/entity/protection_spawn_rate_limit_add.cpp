#include "protection_spawn_rate_limit_add.h"
#include "menu/base/submenu_handler.h"
#include "../protection_spawn_rate_limit.h"
#include "global/lists.h"

using namespace protection::limits::spawn::add::vars;

namespace protection::limits::spawn::add::vars {
	variables m_vars;

	void add_rate_limit() {
		if (m_vars.m_model == 0) return;

		protection::limits::spawn::vars::entity_rate_limit limit;
		limit.m_model = m_vars.m_model;
		limit.m_delay = m_vars.m_delay;
		limit.m_enabled = true;
		strcpy_s(limit.m_comment, m_vars.m_comment.c_str());
		protection::limits::spawn::vars::m_vars.m_limits.push_back(limit);

		menu::submenu::handler::set_submenu_previous(true);
	}
}

void protection_spawn_rate_limit_add_menu::load() {
	set_name("Add Rate Limit");
	set_parent<protection_spawn_rate_limit_menu>();

	m_vars.m_options.push_back(add_option(button_option("Input Model")
		.add_translate()
		.add_keyboard("Input the model! (Hint: name, hash or numeric)", 30, [](button_option* option, const char* result) {
			if (result) {
				m_vars.m_comment = result;

				if (result[0] == '0' && (result[1] == 'x' || result[1] == 'X')) {
					// hash
					m_vars.m_model = (uint32_t)_strtoui64(result, 0, 0);
				} else {
					std::string string_name(result);
					if (std::find_if(string_name.begin(), string_name.end(), [](unsigned char c) { return !std::isdigit(c); }) == string_name.end()) {
						// numeric
						m_vars.m_model = (uint32_t)atoi(result);
					} else {
						// name
						m_vars.m_model = native::get_hash_key(result);
					}
				}
			}
		})));

	m_vars.m_options.push_back(add_option(button_option("Input Comment")
		.add_translate()
		.add_keyboard("Input custom comment", 0x100, [](button_option* option, const char* result) {
			m_vars.m_comment = result;
		})));

	m_vars.m_options.push_back(add_option(scroll_option<uint32_t>(SCROLL, "Delay Per Spawn")
		.add_translate()
		.add_scroll(m_vars.m_delay, 0, NUMOF(global::lists::g_timers), global::lists::g_timers)));

	m_vars.m_options.push_back(add_option(button_option("Add Rate Limit")
		.add_translate()
		.add_click(add_rate_limit)));

	add_string("Model");
	add_string("Comment");
}

void protection_spawn_rate_limit_add_menu::update() {
	char tooltip[0x150];
	sprintf_s(tooltip, "%s=%X %s=%s", 
		get_string("Model").c_str(),
		m_vars.m_model,
		get_string("Comment").c_str(),
		m_vars.m_comment.c_str());

	for (std::shared_ptr<base_option>& option : m_vars.m_options) {
		option->set_tooltip(tooltip);
	}
}

void protection_spawn_rate_limit_add_menu::update_once() {
	m_vars.m_comment.clear();
	m_vars.m_model = 0;
	m_vars.m_delay = 0;
}

void protection_spawn_rate_limit_add_menu::feature_update() {}

protection_spawn_rate_limit_add_menu* g_instance;
protection_spawn_rate_limit_add_menu* protection_spawn_rate_limit_add_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new protection_spawn_rate_limit_add_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}