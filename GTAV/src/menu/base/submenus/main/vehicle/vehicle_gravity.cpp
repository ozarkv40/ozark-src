#include "vehicle_gravity.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle.h"
#include "global/lists.h"
#include "menu/base/util/control.h"
#include "rage/engine.h"

using namespace vehicle::gravity::vars;

namespace vehicle::gravity::vars {
	variables m_vars;

	void gravity() {
		if (menu::player::get_local_player().m_in_vehicle) {
			if (rage::engine::get_entity_address(menu::player::get_local_player().m_vehicle) == 0) return;
			vehicle::vars::run_task(menu::player::get_local_player().m_vehicle, [](Vehicle veh) {
				rage::engine::set_vehicle_gravity(rage::engine::get_entity_address(veh), global::lists::g_gravity[m_vars.m_gravity].m_result);
			});
		}
	}
}

void vehicle_gravity_menu::load() {
	set_name("Gravity");
	set_parent<vehicle_menu>();

	add_option(scroll_option<float>(SCROLL, "Gravity")
		.add_translate()
		.add_scroll(m_vars.m_gravity, 0, NUMOF(global::lists::g_gravity), global::lists::g_gravity)
		.add_click(gravity));

	add_option(toggle_option("Drive on Water")
		.add_translate()
		.add_toggle(m_vars.m_drive_on_water)
		.add_click([] {
			if (!m_vars.m_drive_on_water) {
				if (native::does_entity_exist(m_vars.m_drive_on_water_entity)) {
					native::set_entity_as_mission_entity(m_vars.m_drive_on_water_entity, true, true);
					native::delete_entity(&m_vars.m_drive_on_water_entity);
				}
			}
		}));

	add_option(toggle_option("Slippy Wheels")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_slippy_wheels).add_savable(get_submenu_name_stack())
		.add_click([] { if (!m_vars.m_slippy_wheels) if (menu::player::get_local_player().m_in_vehicle) native::set_vehicle_reduce_grip(menu::player::get_local_player().m_vehicle, false); }));

	add_option(toggle_option("Freeze")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_freeze).add_savable(get_submenu_name_stack())
		.add_click([] { if (!m_vars.m_freeze) if (menu::player::get_local_player().m_in_vehicle) native::freeze_entity_position(menu::player::get_local_player().m_vehicle, false); }));

	add_option(toggle_option("Stick to Ground")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_stick_to_ground).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Auto Flip")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_auto_flip).add_savable(get_submenu_name_stack()));

	add_option(button_option("Place on Ground")
		.add_translate().add_hotkey()
		.add_click([] { if (menu::player::get_local_player().m_in_vehicle) vehicle::vars::run_task(menu::player::get_local_player().m_vehicle, [](Vehicle veh) { native::set_vehicle_on_ground_properly(veh, 0); }); }));

}

void vehicle_gravity_menu::update() {}

void vehicle_gravity_menu::update_once() {}

void vehicle_gravity_menu::feature_update() {
	if (menu::player::get_local_player().m_in_vehicle) {
		if (m_vars.m_slippy_wheels) {
			native::set_vehicle_reduce_grip(menu::player::get_local_player().m_vehicle, true);
		}

		if (m_vars.m_drive_on_water) {
			math::vector3<float> coords = menu::player::get_local_player().m_coords;

			float water_height = 0.f;
			native::get_water_height(coords.x, coords.y, coords.z, &water_height);

			math::vector3<float> adjusted = { coords.x, coords.y, water_height - 1.9f };

			if (coords.z - water_height <= 3.f) {
				if (!native::does_entity_exist(m_vars.m_drive_on_water_entity)) {
					menu::control::simple_request_model(0xC42C019A);
					m_vars.m_drive_on_water_entity = native::create_object(0xC42C019A, coords.x, coords.y, coords.z, true, false, false);
					native::set_model_as_no_longer_needed(0xC42C019A);
				} else {
					native::set_entity_visible(m_vars.m_drive_on_water_entity, false, true);
					native::set_entity_rotation(m_vars.m_drive_on_water_entity, 180.f, 90.f, 180.f, 2, false);
					native::set_entity_coords(m_vars.m_drive_on_water_entity, adjusted.x, adjusted.y, adjusted.z, true, false, false, true);
					native::freeze_entity_position(m_vars.m_drive_on_water_entity, true);
				}
			}
		}

		if (m_vars.m_freeze) {
			native::freeze_entity_position(menu::player::get_local_player().m_vehicle, true);
		}

		if (m_vars.m_stick_to_ground) {
			native::set_vehicle_on_ground_properly(menu::player::get_local_player().m_vehicle, 0);
		}

		if (m_vars.m_auto_flip) {
			if (!native::is_entity_upright(menu::player::get_local_player().m_vehicle, 120.f)) {
				math::vector3<float> rotation = native::get_entity_rotation(menu::player::get_local_player().m_vehicle, 0);
				native::set_entity_rotation(menu::player::get_local_player().m_vehicle, 0.f, rotation.y, rotation.z, 0, true);
			}
		}
	}
}

vehicle_gravity_menu* g_instance;
vehicle_gravity_menu* vehicle_gravity_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_gravity_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}