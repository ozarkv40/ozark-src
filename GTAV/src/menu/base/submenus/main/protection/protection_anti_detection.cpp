#include "protection_anti_detection.h"
#include "menu/base/submenu_handler.h"
#include "../protections.h"

using namespace protection::detection::vars;

namespace protection::detection::vars {
	variables m_vars;
}

void protection_anti_detection_menu::load() {
	set_name("Anti Detection");
	set_parent<protection_menu>();

	add_option(toggle_option("Godmode")
		.add_translate()
		.add_toggle(m_vars.m_godmode).add_savable(get_submenu_name_stack())
		.add_tooltip("Disables modders seeing you're in godmode"));

	add_option(toggle_option("Super Jump")
		.add_translate()
		.add_toggle(m_vars.m_super_jump).add_savable(get_submenu_name_stack())
		.add_tooltip("Disables modders seeing you're using super jump"));

	add_option(toggle_option("Health")
		.add_translate()
		.add_toggle(m_vars.m_health).add_savable(get_submenu_name_stack())
		.add_tooltip("Disables modders seeing you have abnormal health"));

	add_option(toggle_option("Armor")
		.add_translate()
		.add_toggle(m_vars.m_armor).add_savable(get_submenu_name_stack())
		.add_tooltip("Disables modders seeing you have abnormal armor"));

	add_option(toggle_option("Spectate")
		.add_translate()
		.add_toggle(m_vars.m_spectate).add_savable(get_submenu_name_stack())
		.add_tooltip("Disables modders seeing you're spectating someone"));
}

void protection_anti_detection_menu::update() {}

void protection_anti_detection_menu::update_once() {}

void protection_anti_detection_menu::feature_update() {}

protection_anti_detection_menu* g_instance;
protection_anti_detection_menu* protection_anti_detection_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new protection_anti_detection_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}