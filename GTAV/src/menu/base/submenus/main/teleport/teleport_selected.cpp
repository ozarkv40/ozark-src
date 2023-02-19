#include "teleport_selected.h"
#include "menu/base/submenu_handler.h"
#include "../teleport.h"

using namespace teleport::selected::vars;

namespace teleport::selected::vars {
	variables m_vars;
}

void teleport_selected_menu::load() {
	set_name("Placeholder", false, false);
	set_parent<teleport_menu>();
}

void teleport_selected_menu::update() {}

void teleport_selected_menu::update_once() {
	clear_options(0);

	for (int i = 0; i < m_vars.m_size; i++) {
		add_option(button_option(m_vars.m_selected[i].m_name.get())
			.add_click([=] { teleport::vars::teleport(m_vars.m_selected[i].m_result); }));
	}
}

void teleport_selected_menu::feature_update() {}

teleport_selected_menu* g_instance;
teleport_selected_menu* teleport_selected_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new teleport_selected_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}