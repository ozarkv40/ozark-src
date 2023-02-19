#include "vehicle_health.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle.h"

using namespace vehicle::health::vars;

namespace vehicle::health::vars {
	variables m_vars;
}

void vehicle_health_menu::load() {
	set_name("Health");
	set_parent<vehicle_menu>();

	add_option(button_option("Repair Vehicle")
		.add_translate().add_hotkey()
		.add_click([] { vehicle::vars::run_task(menu::player::get_local_player().m_vehicle, [](Vehicle veh) { native::set_vehicle_fixed(veh); }); }));

	add_option(button_option("Wash Vehicle")
		.add_translate().add_hotkey()
		.add_click([] { vehicle::vars::run_task(menu::player::get_local_player().m_vehicle, [](Vehicle veh) { native::set_vehicle_dirt_level(menu::player::get_local_player().m_vehicle, 0.f); }); }));

	add_option(button_option("Dirty Vehicle")
		.add_translate().add_hotkey()
		.add_click([] { vehicle::vars::run_task(menu::player::get_local_player().m_vehicle, [](Vehicle veh) { native::set_vehicle_dirt_level(menu::player::get_local_player().m_vehicle, 15.f); }); }));

	add_option(toggle_option("Auto Repair")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_auto_repair).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Auto Wash")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_auto_wash).add_savable(get_submenu_name_stack()));
}

void vehicle_health_menu::update() {}

void vehicle_health_menu::update_once() {}

void vehicle_health_menu::feature_update() {
	if (menu::player::get_local_player().m_in_vehicle) {
		if (m_vars.m_auto_repair) {
			if (native::is_vehicle_damaged(menu::player::get_local_player().m_vehicle)) {
				vehicle::vars::run_task(menu::player::get_local_player().m_vehicle, [] (Vehicle veh) {
					native::set_vehicle_fixed(veh);
				});
			}
		}

		if (m_vars.m_auto_wash) {
			native::set_vehicle_dirt_level(menu::player::get_local_player().m_vehicle, 0.f);
		}
	}
}

vehicle_health_menu* g_instance;
vehicle_health_menu* vehicle_health_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_health_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}