#include "spawner_object_settings.h"
#include "menu/base/submenu_handler.h"
#include "../../spawner.h"

using namespace spawner::object::settings::vars;

namespace spawner::object::settings::vars {
	variables m_vars;
}

void spawner_object_settings_menu::load() {
	set_name("Spawn Settings", true, false);
	set_parent<spawner_menu>();

	add_option(toggle_option("Notification")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_notification).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Blip")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_blip).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Particle FX")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_particle_fx).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Fade")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_fade).add_savable(get_submenu_name_stack()));
}

void spawner_object_settings_menu::update() {}

void spawner_object_settings_menu::update_once() {}

void spawner_object_settings_menu::feature_update() {}

spawner_object_settings_menu* g_instance;
spawner_object_settings_menu* spawner_object_settings_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new spawner_object_settings_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}