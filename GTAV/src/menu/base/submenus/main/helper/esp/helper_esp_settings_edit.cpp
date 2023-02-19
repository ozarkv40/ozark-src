#include "helper_esp_settings_edit.h"
#include "menu/base/submenu_handler.h"
#include "helper_esp_settings.h"
#include "../../helper/helper_color.h"
#include "menu/base/util/instructionals.h"
#include "../helper_rainbow.h"

using namespace helper::esp::settings::edit::vars;

namespace helper::esp::settings::edit::vars {
	variables m_vars;
}

void helper_esp_settings_edit_menu::load() {
	set_parent<helper_esp_settings_menu>();
	set_default_instructionals(false);

	add_string("Edit Color");
	add_string("Toggle Rainbow");
}

void helper_esp_settings_edit_menu::update() {
	if (menu::base::get_current_option() == 0) {
		instructionals::standard(false, false, false);
	} else {
		instructionals::rainbow();

		if (menu::input::is_just_pressed(false, ControlFrontendX)) {
			helper::rainbow::vars::m_vars.m_rainbow = m_vars.m_rainbow;
			helper_rainbow_menu::get()->set_parent<helper_esp_settings_edit_menu>();
			menu::submenu::handler::set_submenu(helper_rainbow_menu::get());
		}
	}
}

void helper_esp_settings_edit_menu::update_once() {
	clear_options(0);

	add_option(submenu_option(get_string("Edit Color"))
		.add_submenu<helper_color_menu>()
		.add_click([=] {
			helper_color_menu::get()->set_name(get_name().get(), false, false);
			helper_color_menu::get()->set_parent<helper_esp_settings_edit_menu>();
			helper::color::vars::m_vars.m_color = m_vars.m_color;
			helper::color::vars::m_vars.m_callback = [] {};
		})
		.add_icon_override({ "randomha", "lol" }, { 0.2145f, 0.0055f }, { 0.011f, 0.02f }, m_vars.m_color));

	add_option(toggle_option(get_string("Toggle Rainbow"))
		.add_toggle(*m_vars.m_rainbow_toggle)
		.add_click([] {
			m_vars.m_rainbow->toggle(*m_vars.m_rainbow_toggle);
			if (*m_vars.m_rainbow_toggle) {
				m_vars.m_rainbow->add(m_vars.m_color);
			} else {
				m_vars.m_rainbow->remove(m_vars.m_color);
			}
		}));
}

void helper_esp_settings_edit_menu::feature_update() {}

helper_esp_settings_edit_menu* g_instance;
helper_esp_settings_edit_menu* helper_esp_settings_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new helper_esp_settings_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}