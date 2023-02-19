#include "misc_panels.h"
#include "menu/base/submenu_handler.h"
#include "../misc.h"
#include "panels/panels_parent.h"
#include "menu/base/submenus/main/network/network_players.h"

void panels_menu::load() {
	set_name("Panels");
	set_parent<misc_menu>();

	for (menu::panels::panel_parent* parent : menu::panels::get_panels()) {
		for (menu::panels::panel_child& child : parent->m_children_panels) {
			int index = util::config::read_int(get_submenu_name_stack(), "Index", child.m_index, { parent->m_name, child.m_name });
			int column = util::config::read_int(get_submenu_name_stack(), "Column", child.m_column, { parent->m_name, child.m_name });
			child.m_render = util::config::read_bool(get_submenu_name_stack(), "Render", child.m_render, { parent->m_name, child.m_name });

			menu::panels::rearrange(parent, child.m_id, column, index);
		}
	}
}

void panels_menu::update() {}

void panels_menu::update_once() {
	clear_options(0);

	for (menu::panels::panel_parent* parent : menu::panels::get_panels()) {
		add_option(submenu_option(parent->m_name)
			.add_click([=] {
				misc::panel::parent::vars::m_vars.m_parent = parent;
				panels_parent_menu::get()->set_name(parent->m_name, false, false);
			})
			.add_hover([=](submenu_option*) {
				for (menu::panels::panel_parent* p : menu::panels::get_panels()) {
					if (p != parent) {
						p->m_render = false;
					}
				}

				network::players::vars::m_vars.m_selected_player = menu::player::get_local_player().m_id; // for panel preview

				for (menu::panels::panel_child& child : parent->m_children_panels) {
					menu::panels::null_structure(child);
				}

				parent->m_render = true;
			})
			.add_submenu<panels_parent_menu>());
	}
}

void panels_menu::feature_update() {}

panels_menu* g_instance;
panels_menu* panels_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new panels_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}