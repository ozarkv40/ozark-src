#include "gravity_gun.h"
#include "menu/base/submenu_handler.h"
#include "weapon_mods.h"
#include "menu/base/util/raycast.h"
#include "menu/base/util/control.h"
#include "menu/base/util/camera.h"

using namespace weapon::gravity::vars;

namespace weapon::gravity::vars {
	variables m_vars;

	void gravity_gun() {
		static int timer = 0;
		if (menu::player::get_local_player().m_is_aiming) {
			math::vector3<float> position = native::get_offset_from_entity_in_world_coords(menu::player::get_local_player().m_ped, 0.4f, 0.0f, 0.8f);

			if (native::does_entity_exist(m_vars.m_entity)) {
				native::set_input_exclusive(0, ControlFrontendUp);
				native::set_input_exclusive(0, ControlFrontendDown);

				if (native::is_control_pressed(0, ControlFrontendUp)) {
					m_vars.m_distance++;
				} else if (native::is_control_pressed(0, ControlFrontendDown) && m_vars.m_distance > 3.f) {
					m_vars.m_distance--;
				}

				menu::control::simple_request_control(m_vars.m_entity);

				auto velocity = ((position + (menu::camera::get_direction() * m_vars.m_distance)) - native::get_entity_coords(m_vars.m_entity, false)) * m_vars.m_force;
				native::set_entity_velocity(m_vars.m_entity, velocity.x, velocity.y, velocity.z);

				if (native::is_ped_shooting(menu::player::get_local_player().m_ped)) {
					velocity = ((position + (menu::camera::get_direction() * 5000.f)) - native::get_entity_coords(m_vars.m_entity, false)) * m_vars.m_force;
					native::set_entity_velocity(m_vars.m_entity, velocity.x, velocity.y, velocity.z);
					m_vars.m_entity = 0;
					timer = native::get_game_timer() + 750;
				}
			} else {
				m_vars.m_entity = 0;

				if (native::get_game_timer() > timer) {
					menu::raycast cast = menu::raycast_infront(9999.f);
					if (cast.hit_entity()) {
						m_vars.m_entity = cast.get_entity();

						if (native::is_entity_a_ped(m_vars.m_entity)) {
							if (native::is_ped_in_any_vehicle(m_vars.m_entity, false)) {
								m_vars.m_entity = native::get_vehicle_ped_is_in(m_vars.m_entity, false);
							} else {
								if (native::is_ped_a_player(m_vars.m_entity)) {
									timer = 0;
									m_vars.m_entity = 0;
									return;
								}
							}
						}

						timer = 0;
					}
				}
			}

			return;
		}

		timer = 0;
		m_vars.m_entity = 0;
	}
}

void gravity_gun_menu::load() {
	set_name("Gravity Gun");
	set_parent<weapon_mods_menu>();

	add_option(toggle_option("Toggle Gravity Gun")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_toggle).add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(SCROLL, "Force")
		.add_translate()
		.add_number(m_vars.m_force, "%.1f", 0.1f).add_min(1.f).add_max(200.f).add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(SCROLL, "Distance")
		.add_translate()
		.add_number(m_vars.m_distance, "%.0f", 1.f).add_min(1.f).add_max(200.f).add_savable(get_submenu_name_stack())
		.add_tooltip("Alternatively, you can use UP and DOWN"));
}

void gravity_gun_menu::update() {}

void gravity_gun_menu::update_once() {}

void gravity_gun_menu::feature_update() {
	if (m_vars.m_toggle) {
		gravity_gun();
	}
}

gravity_gun_menu* g_instance;
gravity_gun_menu* gravity_gun_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new gravity_gun_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
