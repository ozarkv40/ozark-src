#include "vehicle_weapons.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle.h"
#include "global/lists.h"
#include "menu/base/util/timers.h"
#include "menu/base/util/control.h"

using namespace vehicle::weapons::vars;

namespace vehicle::weapons::vars {
	variables m_vars;

	scroll_struct<int> line_type[] = {
		{ localization("Point", true), 0 },
		{ localization("Cross", true), 1 },
		{ localization("Straight", true), 2 }
	};
}

void vehicle_weapons_menu::load() {
	set_name("Weapons");
	set_parent<vehicle_menu>();

	add_option(toggle_option("Toggle Weapons")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_toggle).add_savable(get_submenu_name_stack()));

	add_option(number_option<float>(SCROLL, "Bullet Speed")
		.add_translate()
		.add_number(m_vars.m_speed, "%.0f", 1.f).add_min(1.f).add_max(10000.f).set_scroll_speed(5).add_savable(get_submenu_name_stack()));

	add_option(scroll_option<int>(TOGGLE, "Aiming Lines")
		.add_translate()
		.add_toggle(m_vars.m_aiming_lines)
		.add_scroll(m_vars.m_aiming_line_type, 0, NUMOF(line_type), line_type).add_savable(get_submenu_name_stack()));

	add_option(break_option("Bullets")
		.add_translate());
}

void vehicle_weapons_menu::update() {}

void vehicle_weapons_menu::update_once() {
	clear_options(4);

	for (scroll_struct<uint32_t> bullet : global::lists::g_vehicle_weapons) {
		add_option(radio_option(bullet.m_name.get())
			.add_radio(m_vars.m_context));
	}
}

void vehicle_weapons_menu::feature_update() {
	if (menu::player::get_local_player().m_in_vehicle) {
		if (m_vars.m_toggle) {
			static int timer = 0;

			math::vector3<float> model_size_min;
			math::vector3<float> model_size_max;
			native::get_model_dimensions(native::get_entity_model(menu::player::get_local_player().m_vehicle), &model_size_min, &model_size_max);

			math::vector3<float> origin_left;
			math::vector3<float> origin_right;
			math::vector3<float> target_left;
			math::vector3<float> target_right;

			math::vector3<float> calculation = model_size_max - model_size_min;

			switch (m_vars.m_aiming_line_type) {
				case 0:
					origin_left = native::get_offset_from_entity_in_world_coords(menu::player::get_local_player().m_vehicle, calculation.x / 4.f, model_size_max.y + 1.f, 0.5f);
					origin_right = native::get_offset_from_entity_in_world_coords(menu::player::get_local_player().m_vehicle, -(calculation.x / 4.f), model_size_max.y + 1.f, 0.5f);
					target_left = native::get_offset_from_entity_in_world_coords(menu::player::get_local_player().m_vehicle, (calculation.x / 4.f) - 0.9f, model_size_max.y + 300.f, 0.5f);
					target_right = native::get_offset_from_entity_in_world_coords(menu::player::get_local_player().m_vehicle, -(calculation.x / 4.f) + 0.9f, model_size_max.y + 300.f, 0.5f);
					
					break;
				case 1:
					origin_left = native::get_offset_from_entity_in_world_coords(menu::player::get_local_player().m_vehicle, calculation.x / 4.f, model_size_max.y + 1.f, 0.5f);
					origin_right = native::get_offset_from_entity_in_world_coords(menu::player::get_local_player().m_vehicle, -(calculation.x / 4.f), model_size_max.y + 1.f, 0.5f);
					target_left = native::get_offset_from_entity_in_world_coords(menu::player::get_local_player().m_vehicle, (calculation.x / 4.f) - 5.f, model_size_max.y + 300.f, 0.5f);
					target_right = native::get_offset_from_entity_in_world_coords(menu::player::get_local_player().m_vehicle, -(calculation.x / 4.f) + 5.f, model_size_max.y + 300.f, 0.5f);
					
					break;
				case 2:
					origin_left = native::get_offset_from_entity_in_world_coords(menu::player::get_local_player().m_vehicle, calculation.x / 4.f, model_size_max.y + 1.f, 0.5f);
					origin_right = native::get_offset_from_entity_in_world_coords(menu::player::get_local_player().m_vehicle, -(calculation.x / 4.f), model_size_max.y + 1.f, 0.5f);
					target_left = native::get_offset_from_entity_in_world_coords(menu::player::get_local_player().m_vehicle, (calculation.x / 4.f) + 8.f, model_size_max.y + 300.f, 0.5f);
					target_right = native::get_offset_from_entity_in_world_coords(menu::player::get_local_player().m_vehicle, -(calculation.x / 4.f) - 8.f, model_size_max.y + 300.f, 0.5f);
					
					break;
			}

			menu::timers::run_timed(&timer, 100, [=] {
				if (native::is_horn_active(menu::player::get_local_player().m_vehicle)) {
					menu::control::request_weapon(global::lists::g_vehicle_weapons[m_vars.m_context.m_selected].m_result, [=] (uint32_t hash) {
						native::shoot_single_bullet_between_coords_ignore_entity(origin_right.x, origin_right.y, origin_right.z, target_right.x, target_right.y, target_right.z, 250, 0, global::lists::g_vehicle_weapons[m_vars.m_context.m_selected].m_result, 0, true, false, native::get_entity_speed(menu::player::get_local_player().m_vehicle) + m_vars.m_speed, menu::player::get_local_player().m_entity, 0);
						native::shoot_single_bullet_between_coords_ignore_entity(origin_left.x, origin_left.y, origin_left.z, target_left.x, target_left.y, target_left.z, 250, 0, global::lists::g_vehicle_weapons[m_vars.m_context.m_selected].m_result, 0, true, false, native::get_entity_speed(menu::player::get_local_player().m_vehicle) + m_vars.m_speed, menu::player::get_local_player().m_entity, 0);
					});
				}
			});

			if (m_vars.m_aiming_lines) {
				native::draw_line(origin_right.x, origin_right.y, origin_right.z, target_right.x, target_right.y, target_right.z, 255, 0, 0, 255);
				native::draw_line(origin_left.x, origin_left.y, origin_left.z, target_left.x, target_left.y, target_left.z, 255, 0, 0, 255);
			}
		}
	}
}

vehicle_weapons_menu* g_instance;
vehicle_weapons_menu* vehicle_weapons_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_weapons_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}