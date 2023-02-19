#include "color_sync.h"
#include "menu/base/submenu_handler.h"
#include "../settings_color.h"
#include "../../helper/helper_color.h"

using namespace settings::color::sync::vars;

namespace settings::color::sync::vars {
	variables m_vars;
}

void color_selected_sync_menu::load() {
	set_name("Sync With...");
	set_parent<helper_color_menu>();
}

void color_selected_sync_menu::update() {}

void color_selected_sync_menu::update_once() {
	clear_options(0);

	for (int i = 0; i < NUMOF(settings::color::vars::colors); i++) {
		add_option(button_option(settings::color::vars::colors[i].m_name.get())
			.add_click([=] {
				*m_vars.m_color = *settings::color::vars::colors[i].m_result;
				helper::color::vars::m_vars.m_callback();
				menu::submenu::handler::set_submenu_previous(false);
			})
			.add_hover([=] { menu::renderer::render_color_preview(*settings::color::vars::colors[i].m_result); }));
	}
}

void color_selected_sync_menu::feature_update() {}

color_selected_sync_menu* g_instance;
color_selected_sync_menu* color_selected_sync_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new color_selected_sync_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}