#include "vehicle_movement.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle.h"
#include "movement/vehicle_movement_parachute.h"
#include "movement/vehicle_movement_acrobatics.h"

using namespace vehicle::movement::vars;

namespace vehicle::movement::vars {
	variables m_vars;

	void run_acrobatic(Vehicle vehicle, std::pair<math::vector3_<float>, math::vector3_<float>> data) {
		if (vehicle) {
			vehicle::vars::run_task(vehicle, [=] (Vehicle veh){
				native::apply_force_to_entity(veh, 1, data.first.x, data.first.y, data.first.z, data.second.x, data.second.y, data.second.z, 0, true, true, true, false, true);
			});
		}
	}

	void limit_max_speed() {
		native::set_entity_max_speed(menu::player::get_local_player().m_vehicle, m_vars.m_limit_max_speed ? m_vars.m_limit_max_speed_val / global::vars::g_selected_metric_system.first : 500.f);
	}

	void bypass_max_speed() {
		native::set_entity_max_speed(menu::player::get_local_player().m_vehicle, 9999999.f);
	}
}

void vehicle_movement_menu::load() {
	set_name("Movement");
	set_parent<vehicle_menu>();

	add_option(submenu_option("Acrobatics")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_movement_acrobatics_menu>());

	add_option(submenu_option("Parachute")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_movement_parachute_menu>());

	add_option(toggle_option("Bypass Max Speed")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_disable_max_speed).add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Limit Max Speed")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_limit_max_speed)
		.add_number(m_vars.m_limit_max_speed_val, "%.0f", 1.f).add_min(0).add_max(99999)
		.add_click([] { m_vars.m_disable_max_speed = false; vehicle::vars::run_task(menu::player::get_local_player().m_vehicle, [] (Vehicle veh) { limit_max_speed(); }); }).add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(TOGGLE, "Flying Vehicle")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_flying_vehicle)
		.add_number(m_vars.m_flying_vehicle_speed, "%.1f", 0.1f).add_min(0.5f).add_max(1000.f)
		.add_click([] { if (!m_vars.m_flying_vehicle) if (menu::player::get_local_player().m_in_vehicle) native::set_entity_collision(menu::player::get_local_player().m_vehicle, true, true); }));

	add_option(toggle_option("Flying Vehicle Pause")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_flying_vehicle_pause).add_savable(get_submenu_name_stack())
		.add_tooltip("Pause vehicle after input loss")
		.add_requirement([] { return m_vars.m_flying_vehicle; }));
}

void vehicle_movement_menu::update() {}

void vehicle_movement_menu::update_once() {}

void vehicle_movement_menu::feature_update() {
	if (menu::player::get_local_player().m_in_vehicle) {
		if (m_vars.m_flying_vehicle) {
			if (native::get_ped_in_vehicle_seat(menu::player::get_local_player().m_vehicle, -1, 0) == menu::player::get_local_player().m_ped) {
				auto apply_force_relative = [] (std::uint32_t handle, math::vector3<float> direction) {
					native::apply_force_to_entity(handle, true, direction.x, direction.y, direction.z, 0.f, 0.f, 0.f, true, true, true, true, false, true);
				};

				int left_right = native::get_control_value(2, 188);
				int up_down = native::get_control_value(2, 189);

				auto w_down = GetKeyState('W') & 0x8000 || up_down == 0;
				auto s_down = GetKeyState('S') & 0x8000 || up_down == 254;
				auto d_down = GetKeyState('D') & 0x8000 || left_right == 254;
				auto a_down = GetKeyState('A') & 0x8000 || left_right == 0;

				auto veh = menu::player::get_local_player().m_vehicle;

				if (w_down || s_down || d_down || a_down) {
					if (w_down)
						apply_force_relative(veh, math::vector3<float>(0, 1.0f * m_vars.m_flying_vehicle_speed, 0));

					if (s_down)
						apply_force_relative(veh, math::vector3<float>(0, -1.0f * m_vars.m_flying_vehicle_speed, 0));

					if (d_down)
						apply_force_relative(veh, math::vector3<float>(1.0f * m_vars.m_flying_vehicle_speed, 0, 0));

					if (a_down)
						apply_force_relative(veh, math::vector3<float>(-1.0f * m_vars.m_flying_vehicle_speed, 0, 0));
				} else {
					if (m_vars.m_flying_vehicle_pause)
						native::set_entity_velocity(veh, 0, 0, 0);
				}

				auto cam_rot = native::get_gameplay_cam_rot(0);
				native::set_entity_rotation(veh, cam_rot.x, cam_rot.y, cam_rot.z, 0, true);
			}
		}

		if (m_vars.m_disable_max_speed) {
			bypass_max_speed();
		}

		if (m_vars.m_limit_max_speed) {
			limit_max_speed();
		}
	}
}

vehicle_movement_menu* g_instance;
vehicle_movement_menu* vehicle_movement_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_movement_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}