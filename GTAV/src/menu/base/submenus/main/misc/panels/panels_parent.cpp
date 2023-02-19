#include "panels_parent.h"
#include "menu/base/submenu_handler.h"
#include "../misc_panels.h"
#include "panels_edit.h"

using namespace misc::panel::parent::vars;

namespace misc::panel::parent::vars {
	variables m_vars;
}

void panels_parent_menu::load() {
	set_name("Parent");
	set_parent<panels_menu>();
}

void panels_parent_menu::update() {}

void panels_parent_menu::update_once() {
	clear_options(0);

	if (!m_vars.m_parent || m_vars.m_parent->m_children_panels.size() <= 0) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	for (std::size_t i = 0; i < m_vars.m_parent->m_children_panels.size(); i++) {
		menu::panels::panel_child& child = m_vars.m_parent->m_children_panels[i];

		add_option(submenu_option(child.m_name)
			.add_click([=] {
				misc::panel::edit::vars::m_vars.m_index = i;
				panels_edit_menu::get()->set_name(child.m_name, false, false);
			})
			.add_submenu<panels_edit_menu>());
	}
}

void panels_parent_menu::feature_update() {}

panels_parent_menu* g_instance;
panels_parent_menu* panels_parent_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new panels_parent_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}