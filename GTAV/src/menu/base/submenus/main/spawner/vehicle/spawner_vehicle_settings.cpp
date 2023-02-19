#include "spawner_vehicle_settings.h"
#include "menu/base/submenu_handler.h"
#include "../../spawner.h"

using namespace spawner::vehicle::settings::vars;

namespace spawner::vehicle::settings::vars {
	variables m_vars;

	scroll_struct<int> upgrades[] = {
		{ localization("Performance", true), 0 },
		{ localization("Everything", true), 0 },
	};
}

void spawner_vehicle_settings_menu::load() {
	set_name("Spawn Settings", true, false);
	set_parent<spawner_menu>();

	get_submenu_name_stack().push("Vehicle");

	add_option(toggle_option("Gift Vehicle")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_gift_vehicle)
		.add_update([] (toggle_option* option, int pos) {
			if (spawner::vars::m_vars.m_flag == spawner::vars::SPAWNER_SESSION) {
				option->add_toggle(m_vars.m_session_gift);
			} else {
				option->add_toggle(menu::player::get_selected_player().m_gift_vehicle);
			}
		})
		.add_requirement([] { return spawner::vars::m_vars.m_flag != spawner::vars::SPAWNER_SELF; })
		.add_tooltip("Vehicles spawned for this player will be gifted to them"));

	add_option(toggle_option("Notification")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_notification).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Blip")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_blip).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Particle FX")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_particle_fx).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Teleport Inside")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_teleport_inside).add_savable(get_submenu_name_stack())
		.add_requirement([] { return spawner::vars::m_vars.m_flag == spawner::vars::SPAWNER_SELF; }));

	add_option(toggle_option("Godmode")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_godmode).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Fade")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_fade).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Air Vehicles In Air")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_air_vehicles_in_air).add_savable(get_submenu_name_stack())
		.add_requirement([] { return spawner::vars::m_vars.m_flag == spawner::vars::SPAWNER_SELF; }));

	add_option(number_option<float>(SCROLL, "Air Vehicles Height")
		.add_translate()
		.add_number(m_vars.m_spawn_height, "%.0f", 1.f).add_min(0.f).add_max(1000.f).add_savable(get_submenu_name_stack())
		.add_requirement([] { return spawner::vars::m_vars.m_flag == spawner::vars::SPAWNER_SELF; }));

	add_option(toggle_option("Delete Current")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_delete_current).add_savable(get_submenu_name_stack())
		.add_requirement([] { return spawner::vars::m_vars.m_flag == spawner::vars::SPAWNER_SELF; }));

	add_option(scroll_option<int>(TOGGLE, "Upgrades")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_upgrades)
		.add_scroll(m_vars.m_upgrades_var, 0, NUMOF(upgrades), upgrades).add_savable(get_submenu_name_stack()));
}

void spawner_vehicle_settings_menu::update() {}

void spawner_vehicle_settings_menu::update_once() {}

void spawner_vehicle_settings_menu::feature_update() {}

spawner_vehicle_settings_menu* g_instance;
spawner_vehicle_settings_menu* spawner_vehicle_settings_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new spawner_vehicle_settings_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}