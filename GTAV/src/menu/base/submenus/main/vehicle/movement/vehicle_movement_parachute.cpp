#include "vehicle_movement_parachute.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_movement.h"
#include "rage/engine.h"
#include "../../vehicle.h"

using namespace vehicle::movement::parachute::vars;

namespace vehicle::movement::parachute::vars {
	variables m_vars;

	void deploy() {
		if (menu::player::get_local_player().m_in_vehicle) {
			if (native::get_entity_height_above_ground(menu::player::get_local_player().m_vehicle) > 5.f) {
				if (native::is_this_model_a_heli(native::get_entity_model(menu::player::get_local_player().m_vehicle))) return;

				vehicle::vars::run_task(menu::player::get_local_player().m_vehicle, [=] (Vehicle veh) {
					uint64_t address = rage::engine::get_entity_address(veh);
					if (address) {
						uint64_t model_info = *(uint64_t*)(address + 0x20);
						if (model_info) {
							*(uint8_t*)(model_info + 0x58C) |= 1;
						}

						*(bool*)(address + 0x1A5D) = true;
						native::set_vehicle_parachute_active(veh, true);
					}
				});
			}
		}
	}
}

void vehicle_movement_parachute_menu::load() {
	set_name("Parachute");
	set_parent<vehicle_movement_menu>();

	add_option(button_option("Deploy")
		.add_translate().add_hotkey()
		.add_click(deploy));

	add_option(toggle_option("Auto Deploy")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_auto_deploy).add_savable(get_submenu_name_stack()));
}

void vehicle_movement_parachute_menu::update() {}

void vehicle_movement_parachute_menu::update_once() {}

void vehicle_movement_parachute_menu::feature_update() {
	if (m_vars.m_auto_deploy) {
		deploy();
	}
}

vehicle_movement_parachute_menu* g_instance;
vehicle_movement_parachute_menu* vehicle_movement_parachute_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_movement_parachute_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}