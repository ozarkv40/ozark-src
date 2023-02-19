#include "teleport_settings.h"
#include "menu/base/submenu_handler.h"
#include "../teleport.h"

using namespace teleport::settings::vars;

namespace teleport::settings::vars {
	variables m_vars;
}

void teleport_settings_menu::load() {
	set_name("Settings");
	set_parent<teleport_menu>();

	add_option(toggle_option("Transition")
		.add_translate().add_hotkey()
		.add_toggle(teleport::vars::m_vars.m_transition).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Auto Teleport to Waypoint")
		.add_translate().add_hotkey()
		.add_toggle(teleport::vars::m_vars.m_auto_waypoint).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Include Current Vehicle")
		.add_translate().add_hotkey()
		.add_toggle(teleport::vars::m_vars.m_include_current_vehicle).add_savable(get_submenu_name_stack())
		.add_tooltip("Teleport your vehicle too"));
}

void teleport_settings_menu::update() {}

void teleport_settings_menu::update_once() {}

void teleport_settings_menu::feature_update() {}

teleport_settings_menu* g_instance;
teleport_settings_menu* teleport_settings_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new teleport_settings_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}