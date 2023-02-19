#include "protection_spawn_rate_limit.h"
#include "menu/base/submenu_handler.h"
#include "../protection_limits.h"
#include "entity/protection_spawn_rate_limit_add.h"
#include "entity/protection_spawn_rate_limit_edit.h"
#include "util/log.h"
#include "util/dirs.h"
#include <fstream>

using namespace protection::limits::spawn::vars;

namespace protection::limits::spawn::vars {
	variables m_vars;

	bool cache_limits() {
		try {
			std::ifstream input(util::dirs::get_path(entity_limits));
			if (input.good()) {
				nlohmann::json json = nlohmann::json::parse(input);
				input.close();

				if (!json.empty()) {
					m_vars.m_limits.clear();

					for (auto& it = json.begin(); it != json.end(); ++it) {
						nlohmann::json& elements = *it;

						entity_rate_limit limit;
						limit.m_model = elements[0];
						limit.m_delay = elements[1];
						limit.m_enabled = elements[2];
						strcpy_s(limit.m_comment, it.key().c_str());
						m_vars.m_limits.push_back(limit);
					}

					return true;
				}
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
		
		return false;
	}
}

void protection_spawn_rate_limit_menu::load() {
	set_name("Spawn Rate");
	set_parent<protection_limits_menu>();

	add_option(submenu_option("Add Rate Limit")
		.add_translate()
		.add_submenu<protection_spawn_rate_limit_add_menu>());

	add_option(break_option("Limits")
		.add_translate());

	add_string("~m~None");
	cache_limits();

	if (!cache_limits()) {
		try {
			std::ofstream output(util::dirs::get_path(entity_limits));
			if (output.good()) {
				nlohmann::json json;
				json["Jet"] = { 0x3f119114, 6, true };
				json["Another Jet"] = { 0x15F27762, 6, true };

				output << json.dump(4);
				output.close();
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}

	protection_spawn_rate_limit_edit_menu::get();
}

void protection_spawn_rate_limit_menu::update() {}

void protection_spawn_rate_limit_menu::update_once() {
	if (menu::submenu::handler::get_previous() == protection_spawn_rate_limit_add_menu::get()) {
		if (!m_vars.m_limits.empty()) {
			try {
				std::ofstream output(util::dirs::get_path(entity_limits));
				if (output.good()) {
					nlohmann::json json;
					
					for (entity_rate_limit& limit : m_vars.m_limits) {
						json[limit.m_comment] = { limit.m_model, limit.m_delay, limit.m_enabled };
					}

					output << json.dump(4);
					output.close();
				}
			} catch (std::exception& e) {
				LOG_WARN("[Json] %s", e.what());
			}
		}
	}

	clear_options(2);

	for (std::size_t i = 0; i < m_vars.m_limits.size(); i++) {
		entity_rate_limit& limit = m_vars.m_limits[i];

		add_option(submenu_option(util::va::va("%X - %s", limit.m_model, limit.m_comment))
			.add_click([=] { protection::limits::spawn::edit::vars::m_vars.m_selected = i; })
			.add_submenu<protection_spawn_rate_limit_edit_menu>());
	}
}

void protection_spawn_rate_limit_menu::feature_update() {}

protection_spawn_rate_limit_menu* g_instance;
protection_spawn_rate_limit_menu* protection_spawn_rate_limit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new protection_spawn_rate_limit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}