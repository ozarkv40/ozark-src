#include "network_spoofing_vehicle_rotation.h"
#include "menu/base/submenu_handler.h"
#include "../network_spoofing.h"
#include "menu/base/submenus/main/vehicle.h"

using namespace network::spoofing::rotation::vehicle::vars;

namespace network::spoofing::rotation::vehicle::vars {
	variables m_vars;

	scroll_struct<int> axis[] = {
		{ localization("Pitch (X)", true), 0 },
		{ localization("Roll (Y)", true), 1 },
		{ localization("Yaw (Z)", true), 2 }
	};
}

void network_spoofing_vehicle_rotation_menu::load() {
	set_name("Vehicle Rotation");
	set_parent<network_spoofing_menu>();

	add_option(toggle_option("Toggle Preview Ghost")
		.add_translate()
		.add_toggle(m_vars.m_ghost)
		.add_tooltip("Spawns a ghost to show you what your changes look like to other players"));

	add_option(number_option<float>(TOGGLE, "Spinbot")
		.add_translate()
		.add_toggle(m_vars.m_spinbot)
		.add_number(m_vars.m_spinbot_speed, "%.0f", 1.f).add_min(0.f).add_max(100.f).set_scroll_speed(10));

	add_option(scroll_option<int>(SCROLL, "Spinbot Axis")
		.add_translate()
		.add_scroll(m_vars.m_spinbot_axis, 0, NUMOF(axis), axis));

	add_option(scroll_option<int>(TOGGLE, "Jitter")
		.add_translate()
		.add_toggle(m_vars.m_jitter)
		.add_scroll(m_vars.m_jitter_axis, 0, NUMOF(axis), axis));

	add_option(toggle_option("Static")
		.add_translate()
		.add_toggle(m_vars.m_static));

	add_option(toggle_option("Relative")
		.add_translate()
		.add_toggle(m_vars.m_relative));

	add_option(break_option("Static")
		.add_translate()
		.add_requirement([] { return m_vars.m_static; }));

	add_option(number_option<float>(TOGGLE, "Pitch (X)")
		.add_translate()
		.add_toggle(m_vars.m_static_toggle.x)
		.add_number(m_vars.m_static_value.x, "%.0f", 1.f).add_min(0.f).add_max(360.f).set_scroll_speed(10)
		.add_requirement([] { return m_vars.m_static; }));

	add_option(number_option<float>(TOGGLE, "Roll (Y)")
		.add_translate()
		.add_toggle(m_vars.m_static_toggle.y)
		.add_number(m_vars.m_static_value.y, "%.0f", 1.f).add_min(0.f).add_max(360.f).set_scroll_speed(10)
		.add_requirement([] { return m_vars.m_static; }));

	add_option(number_option<float>(TOGGLE, "Yaw (Z)")
		.add_translate()
		.add_toggle(m_vars.m_static_toggle.z)
		.add_number(m_vars.m_static_value.z, "%.0f", 1.f).add_min(0.f).add_max(360.f).set_scroll_speed(10)
		.add_requirement([] { return m_vars.m_static; }));
}

void network_spoofing_vehicle_rotation_menu::update() {}

void network_spoofing_vehicle_rotation_menu::update_once() {
	if (menu::player::get_local_player().m_in_vehicle) {
		if (m_vars.m_ghost) {
			// TODO: pack_clone_create blocker for handle
			if (!native::does_entity_exist(m_vars.m_ghost_handle)) {
				m_vars.m_ghost_handle = vehicle::vars::clone_vehicle(menu::player::get_local_player().m_vehicle);

				if (native::does_entity_exist(m_vars.m_ghost_handle)) {
					native::set_entity_alpha(m_vars.m_ghost_handle, 100, false);
					native::set_entity_collision(m_vars.m_ghost_handle, false, false);
					native::attach_entity_to_entity(m_vars.m_ghost_handle, menu::player::get_local_player().m_vehicle, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 1, 1, 1);
				}
			}
		} else {
			if (native::does_entity_exist(m_vars.m_ghost_handle)) {
				native::detach_entity(m_vars.m_ghost_handle, true, false);
				native::delete_entity(&m_vars.m_ghost_handle);
				m_vars.m_ghost_handle = 0;
			}
		}
	}
}

void network_spoofing_vehicle_rotation_menu::feature_update() {
	if (menu::player::get_local_player().m_in_vehicle) {
		m_vars.m_hook_value.x = menu::player::get_local_player().m_rotation.x;
		m_vars.m_hook_value.y = menu::player::get_local_player().m_rotation.y;
		m_vars.m_hook_value.z = menu::player::get_local_player().m_rotation.z;

		if (m_vars.m_static) {
			if (m_vars.m_static_toggle.x) m_vars.m_hook_value.x = m_vars.m_static_value.x + (m_vars.m_relative ? menu::player::get_local_player().m_rotation.x : 0.f);
			if (m_vars.m_static_toggle.y) m_vars.m_hook_value.y = m_vars.m_static_value.y + (m_vars.m_relative ? menu::player::get_local_player().m_rotation.y : 0.f);
			if (m_vars.m_static_toggle.z) m_vars.m_hook_value.z = m_vars.m_static_value.z + (m_vars.m_relative ? menu::player::get_local_player().m_rotation.z : 0.f);
		}

		if (m_vars.m_spinbot) {
			static float value = 0.f;
			value += m_vars.m_spinbot_speed;
			if (value > 360.f) value = (value - 360.f);

			switch (m_vars.m_spinbot_axis) {
				case 0:
					m_vars.m_hook_value.x = value;
					break;

				case 1:
					m_vars.m_hook_value.y = value;
					break;

				case 2:
					m_vars.m_hook_value.z = value;
					break;
			}
		}

		if (m_vars.m_jitter) {
			static float value = 0.f;
			value += native::get_random_float_in_range(5.f, 100.f);
			if (value > 360.f) value = (value - 360.f);

			switch (m_vars.m_jitter_axis) {
				case 0:
					m_vars.m_hook_value.x = value;
					break;

				case 1:
					m_vars.m_hook_value.y = value;
					break;

				case 2:
					m_vars.m_hook_value.z = value;
					break;
			}
		}

		if (m_vars.m_ghost_handle && native::does_entity_exist(m_vars.m_ghost_handle)) {
			native::attach_entity_to_entity(m_vars.m_ghost_handle, menu::player::get_local_player().m_vehicle, 0, 0.0f, 0.0f, 0.0f, m_vars.m_hook_value.x - menu::player::get_local_player().m_rotation.x, m_vars.m_hook_value.y - menu::player::get_local_player().m_rotation.y, m_vars.m_hook_value.z - menu::player::get_local_player().m_rotation.z, 0, 0, 0, 1, 1, 1);
		}

		m_vars.m_hook_value.x *= 0.0174532924f;
		m_vars.m_hook_value.y *= 0.0174532924f;
		m_vars.m_hook_value.z *= 0.0174532924f;
	}
}

network_spoofing_vehicle_rotation_menu* g_instance;
network_spoofing_vehicle_rotation_menu* network_spoofing_vehicle_rotation_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_spoofing_vehicle_rotation_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}