#include "panels_edit.h"
#include "menu/base/submenu_handler.h"
#include "panels_parent.h"
#include "menu/base/util/timers.h"
#include "../misc_panels.h"

using namespace misc::panel::edit::vars;

namespace misc::panel::edit::vars {
	variables m_vars;
}

void panels_edit_menu::load() {
	set_name("Edit");
	set_parent<panels_parent_menu>();

	add_string("Toggle");
	add_string("Column");
	add_string("Index");
}

void panels_edit_menu::update() {
	static bool update_cache = true;
	static int timer_1 = 0;

	static bool write_config = true;
	static int timer_2 = 0;

	menu::timers::run_timed(&timer_1, 100, [&] { update_cache = true; });
	menu::timers::run_timed(&timer_2, 500, [&] { write_config = true; });

	if (update_cache) {
		update_cache = false;

		clear_options(0);
		menu::panels::panel_child& child = menu::panels::get_child(misc::panel::parent::vars::m_vars.m_parent, m_vars.m_id); // account for sorting

		if (write_config) {
			util::config::write_int(panels_menu::get()->get_submenu_name_stack(), "Index", child.m_index, { child.m_parent->m_name, child.m_name });
			util::config::write_int(panels_menu::get()->get_submenu_name_stack(), "Column", child.m_column, { child.m_parent->m_name, child.m_name });
			util::config::write_bool(panels_menu::get()->get_submenu_name_stack(), "Render", child.m_render, { child.m_parent->m_name, child.m_name });
		}

		add_option(toggle_option(get_string("Toggle"))
			.add_toggle(child.m_render));

		if (child.m_parent->m_children_panels.size() == 1) {
			return;
		}

		int max_column = 0;
		for (menu::panels::panel_child& it : child.m_parent->m_children_panels) {
			if (it.m_column > max_column) {
				max_column = it.m_column;
			}
		}

		add_option(number_option<int>(SCROLL, get_string("Column"))
			.add_number(m_vars.m_local_column, "%i", 1).add_min(0).add_max(max_column + 1)
			.add_click([=] { menu::panels::rearrange(child.m_parent, child.m_id, m_vars.m_local_column, m_vars.m_local_index); }));

		add_option(number_option<int>(SCROLL, get_string("Index"))
			.add_number(m_vars.m_local_index, "%i", 1).add_min(0).add_max(1000)
			.add_click([=] { menu::panels::rearrange(child.m_parent, child.m_id, m_vars.m_local_column, m_vars.m_local_index); }));
	}
}

void panels_edit_menu::update_once() {
	menu::panels::panel_child& child = misc::panel::parent::vars::m_vars.m_parent->m_children_panels[m_vars.m_index] ;
	m_vars.m_id = child.m_id;
	m_vars.m_local_column = child.m_column;
	m_vars.m_local_index = child.m_index;
}

void panels_edit_menu::feature_update() {}

panels_edit_menu* g_instance;
panels_edit_menu* panels_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new panels_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}