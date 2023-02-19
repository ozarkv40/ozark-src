#include "helper_rainbow_load.h"
#include "menu/base/submenu_handler.h"
#include "../helper_rainbow.h"
#include "util/log.h"
#include "util/dirs.h"
#include <fstream>

using namespace helper::rainbow::config::vars;

namespace helper::rainbow::config::vars {
	variables m_vars;

	void save_config(std::string name) {
		try {
			nlohmann::json json;

			std::ifstream input(util::dirs::get_path(rainbow));
			if (input.good()) {
				input >> json;
				input.close();
			}

			std::ofstream output(util::dirs::get_path(rainbow));
			if (output.good()) {
				json[name] = nlohmann::json::array({ m_vars.m_rainbow->m_min, m_vars.m_rainbow->m_max, m_vars.m_rainbow->m_steps });
				output << json.dump(4);
				output.close();
			}
		} catch (std::exception& E) {
			LOG_WARN("[Json] %s", E.what());
		}
	}

	void load_config(std::string name) {
		try {
			std::ifstream input(util::dirs::get_path(rainbow));
			if (input.good()) {
				nlohmann::json json;
				input >> json;
				input.close();

				if (!json[name].is_null()) {
					m_vars.m_rainbow->m_min = json[name][0].get<int>();
					m_vars.m_rainbow->m_max = json[name][1].get<int>();
					m_vars.m_rainbow->m_steps = json[name][2].get<int>();
				}
			}
		} catch (std::exception& E) {
			LOG_WARN("[Json] %s", E.what());
		}
	}
}

void helper_rainbow_config_menu::load() {
	set_name("Rainbow Config");
	set_parent<helper_rainbow_menu>();

	add_option(button_option("Save Rainbow Config")
		.add_translate()
		.add_keyboard("Enter rainbow config name", 30, [](button_option* option, const char* result) {
			save_config(result);
		}));

	add_option(break_option("Rainbows")
		.add_translate());

	add_string("~m~None");
}

void helper_rainbow_config_menu::update() {}

void helper_rainbow_config_menu::update_once() {
	clear_options(2);

	try {
		std::ifstream input(util::dirs::get_path(rainbow));
		if (input.good()) {
			nlohmann::json json;
			input >> json;
			input.close();

			if (json.size() > 0) {
				std::vector<std::string> names;

				for (auto& it = json.begin(); it != json.end(); ++it) {
					names.push_back(it.key());
				}

				for (std::string name : names) {
					add_option(button_option(name)
						.add_click([=] { load_config(name); }));
				}
			} else {
				add_option(button_option(get_string("~m~None")).ref());
			}
		} else {
			add_option(button_option(get_string("~m~None")).ref());
		}
	} catch (std::exception& e) {
		LOG_WARN("[Json] %s", e.what());
	}
}

void helper_rainbow_config_menu::feature_update() {}

helper_rainbow_config_menu* g_instance;
helper_rainbow_config_menu* helper_rainbow_config_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new helper_rainbow_config_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}