#include "helper_rainbow.h"
#include "menu/base/submenu_handler.h"
#include "rainbow/helper_rainbow_load.h"

using namespace helper::rainbow::vars;

namespace helper::rainbow::vars {
	variables m_vars;

	void set_color() {
		if (m_vars.m_rainbow) {
			m_vars.m_rainbow->m_min = m_vars.m_local_rainbow.m_min;
			m_vars.m_rainbow->m_max = m_vars.m_local_rainbow.m_max;
			m_vars.m_rainbow->m_steps = m_vars.m_local_rainbow.m_steps;
		}
	}
}

void helper_rainbow_menu::load() {
	set_name("Rainbow Config");

	add_option(submenu_option("Save and Load")
		.add_translate()
		.add_click([] { helper::rainbow::config::vars::m_vars.m_rainbow = m_vars.m_rainbow; })
		.add_submenu<helper_rainbow_config_menu>());

	m_vars.m_local_rainbow.add(&m_vars.m_local_color);
	m_vars.m_local_rainbow.toggle(true);

	helper_rainbow_config_menu::get();

	add_string("Minimum");
	add_string("Maximum");
	add_string("Steps");
}

void helper_rainbow_menu::update() {
	if (m_vars.m_rainbow) {
		m_vars.m_local_color = m_vars.m_rainbow->m_color;
		m_vars.m_local_rainbow.m_min = m_vars.m_rainbow->m_min;
		m_vars.m_local_rainbow.m_max = m_vars.m_rainbow->m_max;
		m_vars.m_local_rainbow.m_steps = m_vars.m_rainbow->m_steps;
		m_vars.m_local_rainbow.run();
	}
}

void helper_rainbow_menu::update_once() {
	clear_options(1);

	add_option(number_option<int>(SCROLL, get_string("Minimum"))
		.add_number(m_vars.m_local_rainbow.m_min, "%i", 1).add_min(0).add_max(255).can_loop()
		.add_hover([] { menu::renderer::render_color_preview(m_vars.m_local_color.opacity(255)); })
		.add_click(set_color));

	add_option(number_option<int>(SCROLL, get_string("Maximum"))
		.add_number(m_vars.m_local_rainbow.m_max, "%i", 1).add_min(0).add_max(255).can_loop()
		.add_hover([] { menu::renderer::render_color_preview(m_vars.m_local_color.opacity(255)); })
		.add_click(set_color));

	add_option(number_option<int>(SCROLL, get_string("Steps"))
		.add_number(m_vars.m_local_rainbow.m_steps, "%i", 1).add_min(1).add_max(255).can_loop()
		.add_hover([] { menu::renderer::render_color_preview(m_vars.m_local_color.opacity(255)); })
		.add_click(set_color));
}

void helper_rainbow_menu::feature_update() {}

helper_rainbow_menu* g_instance;
helper_rainbow_menu* helper_rainbow_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new helper_rainbow_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}