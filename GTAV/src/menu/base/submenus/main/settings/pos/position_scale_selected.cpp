#include "position_scale_selected.h"
#include "menu/base/submenu_handler.h"
#include "../position_scale.h"

using namespace settings::pos::selected::vars;

namespace settings::pos::selected::vars {
	variables m_vars;
}

void position_scale_selected_menu::load() {
	set_name("Position and Scale", false, false);
	set_parent<position_scale_menu>();

	add_option(number_option<float>(SCROLL, "X (Horizontal)")
		.add_translate()
		.add_number(m_vars.m_selected->x, "%.3f", 0.001f).set_scroll_speed(5)
		.add_update([](number_option<float>* option, int position) { option->add_number(m_vars.m_selected->x, "%.3f", 0.001f); }));

	add_option(number_option<float>(SCROLL, "Y (Vertical)")
		.add_translate()
		.add_number(m_vars.m_selected->y, "%.3f", 0.001f).set_scroll_speed(5)
		.add_update([](number_option<float>* option, int position) { option->add_number(m_vars.m_selected->y, "%.3f", 0.001f); }));
}

void position_scale_selected_menu::update() {}

void position_scale_selected_menu::update_once() {}

void position_scale_selected_menu::feature_update() {}

position_scale_selected_menu* g_instance;
position_scale_selected_menu* position_scale_selected_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new position_scale_selected_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}