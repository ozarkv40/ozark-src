#include "model_swaps_add.h"
#include "menu/base/submenu_handler.h"
#include "model_swaps.h"
#include "util/fiber_pool.h"

using namespace misc::swaps::model::add::vars;

namespace misc::swaps::model::add::vars {
	variables m_vars;
}

void model_swaps_add_menu::load() {
	set_name("Add Swap");
	set_parent<model_swaps_menu>();

	m_vars.m_options.push_back(add_option(button_option("Input Original Model")
		.add_translate()
		.add_keyboard("Input the model! (Hint: name, hash or numeric)", 100, [](button_option* option, const char* model) {
			m_vars.m_original = model;
		})));

	m_vars.m_options.push_back(add_option(button_option("Input New Model")
		.add_translate()
		.add_keyboard("Input the model! (Hint: name, hash or numeric)", 100, [](button_option* option, const char* model) { m_vars.m_new = model; })));

	m_vars.m_options.push_back(add_option(button_option("Add Swap")
		.add_translate()
		.add_click([] {
			if (!m_vars.m_original.empty() && !m_vars.m_new.empty()) {
				util::fiber::pool::add([] {
					misc::swaps::model::vars::model_swap output;
					if (misc::swaps::model::vars::add_swap(m_vars.m_original.c_str(), m_vars.m_new.c_str(), &output)) {
						misc::swaps::model::vars::add_json(output);
					}

					menu::submenu::handler::set_submenu_previous(true);
				});
			}
		})));

	add_string("Current");
	add_string("New");
}

void model_swaps_add_menu::update() {
	char tooltip[100];
	sprintf_s(tooltip, "%s=%s %s=%s", get_string("Current").c_str(),
		m_vars.m_original.empty() ? "~italic~unset~s~" : m_vars.m_original.c_str(),
		get_string("New").c_str(),
		m_vars.m_new.empty() ? "~italic~unset~s~" : m_vars.m_new.c_str());

	for (std::shared_ptr<button_option>& option : m_vars.m_options) {
		option->set_tooltip(tooltip);
	}
}

void model_swaps_add_menu::update_once() {
	m_vars.m_original.clear();
	m_vars.m_new.clear();
}

void model_swaps_add_menu::feature_update() {}

model_swaps_add_menu* g_instance;
model_swaps_add_menu* model_swaps_add_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new model_swaps_add_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}