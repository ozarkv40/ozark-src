#include "vehicle_doors.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle.h"

using namespace vehicle::doors::vars;

namespace vehicle::doors::vars {
	variables m_vars;
}

void vehicle_doors_menu::load() {
	set_name("Doors");
	set_parent<vehicle_menu>();

	add_option(number_option<int>(SCROLLSELECT, "Open Door")
		.add_translate().add_hotkey()
		.add_number(m_vars.m_open_door, "%i", 1).add_min(0).add_max(1)
		.add_update([](number_option<int>* option, int pos) {
			if (menu::player::get_local_player().m_in_vehicle) {
				option->add_max(native::get_number_of_vehicle_doors(menu::player::get_local_player().m_vehicle));
			}
		})
		.add_click([] {
			if (menu::player::get_local_player().m_in_vehicle) {
				vehicle::vars::run_task(menu::player::get_local_player().m_vehicle, [](Vehicle veh) {
					native::set_vehicle_door_open(veh, m_vars.m_open_door, false, false);
				});
			}
		}));

	add_option(number_option<int>(SCROLLSELECT, "Close Door")
		.add_translate().add_hotkey()
		.add_number(m_vars.m_close_door, "%i", 1).add_min(0).add_max(1)
		.add_update([](number_option<int>* option, int pos) {
			if (menu::player::get_local_player().m_in_vehicle) {
				option->add_max(native::get_number_of_vehicle_doors(menu::player::get_local_player().m_vehicle));
			}
		})
		.add_click([] {
			if (menu::player::get_local_player().m_in_vehicle) {
				vehicle::vars::run_task(menu::player::get_local_player().m_vehicle, [](Vehicle veh) {
					native::set_vehicle_door_shut(veh, m_vars.m_close_door, false);
				});
			}
		}));

	add_option(number_option<int>(SCROLLSELECT, "Delete Door")
		.add_translate().add_hotkey()
		.add_number(m_vars.m_delete_door, "%i", 1).add_min(0).add_max(1)
		.add_update([](number_option<int>* option, int pos) {
			if (menu::player::get_local_player().m_in_vehicle) {
				option->add_max(native::get_number_of_vehicle_doors(menu::player::get_local_player().m_vehicle));
			}
		})
		.add_click([] {
			if (menu::player::get_local_player().m_in_vehicle) {
				vehicle::vars::run_task(menu::player::get_local_player().m_vehicle, [](Vehicle veh) {
					native::set_vehicle_door_broken(veh, m_vars.m_delete_door, true);
				});
			}
		}));

	add_option(button_option("Lock Doors")
		.add_translate().add_hotkey()
		.add_click([] {
			if (menu::player::get_local_player().m_in_vehicle) {
				vehicle::vars::run_task(menu::player::get_local_player().m_vehicle, [](Vehicle veh) {
					native::set_vehicle_doors_locked(veh, 4);
				});
			}
		}));

	add_option(button_option("Unlock Doors")
		.add_translate().add_hotkey()
		.add_click([] {
			if (menu::player::get_local_player().m_in_vehicle) {
				vehicle::vars::run_task(menu::player::get_local_player().m_vehicle, [](Vehicle veh) {
					native::set_vehicle_doors_locked(veh, 0);
				});
			}
		}));
}

void vehicle_doors_menu::update() {}

void vehicle_doors_menu::update_once() {}

void vehicle_doors_menu::feature_update() {}

vehicle_doors_menu* g_instance;
vehicle_doors_menu* vehicle_doors_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_doors_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}