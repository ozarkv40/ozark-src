#include "vehicle_modifiers_handling_boat.h"
#include "menu/base/submenu_handler.h"
#include "vehicle_modifiers_handling_main.h"

using namespace vehicle::modifiers::handling::boat::vars;

namespace vehicle::modifiers::handling::boat::vars {
	variables m_vars;

	rage::types::boat_handling_data* get_data() {
		static rage::types::boat_handling_data hd;

		if (global::vars::g_ped_factory) {
			if (global::vars::g_ped_factory->m_local_ped) {
				if (global::vars::g_ped_factory->m_local_ped->m_vehicle) {
					if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data) {
						if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_sub_handling_data) {
							if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_sub_handling_data->m_sub_handling_data) {
								return &global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_sub_handling_data->m_sub_handling_data->m_boat_handling_data;
							}
						}
					}
				}
			}
		}

		return &hd;
	}

	void reset() {
		uint32_t model = native::get_entity_model(menu::player::get_local_player().m_vehicle);

		switch (m_vars.m_type) {
			case 0: /* Physical */
				if (m_vars.m_physical_restore.find(model) != m_vars.m_physical_restore.end()) {
					auto& backup = m_vars.m_physical_restore[model];
					get_data()->m_box_front_mult = backup.m_box_front_mult;
					get_data()->m_box_rear_mult = backup.m_box_rear_mult;
					get_data()->m_box_side_mult = backup.m_box_side_mult;
					get_data()->m_sample_top = backup.m_sample_top;
					get_data()->m_sample_bottom = backup.m_sample_bottom;
				}
				break;

			case 1: /* Aquaplane */
				if (m_vars.m_aquaplane_restore.find(model) != m_vars.m_aquaplane_restore.end()) {
					auto& backup = m_vars.m_aquaplane_restore[model];
					get_data()->m_aquaplane_force = backup.m_aquaplane_force;
					get_data()->m_aquaplane_push_water_mult = backup.m_aquaplane_push_water_mult;
					get_data()->m_aquaplane_push_water_cap = backup.m_aquaplane_push_water_cap;
					get_data()->m_aquaplane_push_water_apply = backup.m_aquaplane_push_water_apply;
					get_data()->m_keel_sphere_size = backup.m_keel_sphere_size;
					get_data()->m_prop_radius = backup.m_prop_radius;
					get_data()->m_impeller_offset = backup.m_impeller_offset;
					get_data()->m_impeller_force_mult = backup.m_impeller_force_mult;
					get_data()->m_prow_raise_mult = backup.m_prow_raise_mult;
				}
				break;

			case 2: /* Rudder */
				if (m_vars.m_rudder_restore.find(model) != m_vars.m_rudder_restore.end()) {
					auto& backup = m_vars.m_rudder_restore[model];
					get_data()->m_rudder_force = backup.m_rudder_force;
					get_data()->m_rudder_offset_submerge = backup.m_rudder_offset_submerge;
					get_data()->m_rudder_offset_force = backup.m_rudder_offset_force;
					get_data()->m_rudder_offset_force_z_mult = backup.m_rudder_offset_force_z_mult;
				}
				break;

			case 3: /* Resistance */
				if (m_vars.m_resistance_restore.find(model) != m_vars.m_resistance_restore.end()) {
					auto& backup = m_vars.m_resistance_restore[model];
					get_data()->m_drag_coefficient = backup.m_drag_coefficient;
					get_data()->m_vec_move_resistance = backup.m_vec_move_resistance;
					get_data()->m_vec_turn_resistance = backup.m_vec_turn_resistance;
				}
				break;

			case 4: /* Misc */
				if (m_vars.m_misc_restore.find(model) != m_vars.m_misc_restore.end()) {
					auto& backup = m_vars.m_misc_restore[model];
					get_data()->m_wave_audio_mult = backup.m_wave_audio_mult;
					get_data()->m_look_lr_cam_height = backup.m_look_lr_cam_height;
					get_data()->m_low_lod_ang_offset = backup.m_low_lod_ang_offset;
					get_data()->m_low_lod_draught_offset = backup.m_low_lod_draught_offset;
					get_data()->m_dinghy_sphere_buoy_const = backup.m_dinghy_sphere_buoy_const;
				}
				break;
		}
	}

	void cache_physical(uint32_t model) {
		if (m_vars.m_physical_restore.find(model) == m_vars.m_physical_restore.end()) {
			m_vars.m_physical_restore[model] = {
				get_data()->m_box_front_mult,
				get_data()->m_box_rear_mult,
				get_data()->m_box_side_mult,
				get_data()->m_sample_top,
				get_data()->m_sample_bottom
			};
		}
	}

	void cache_aquaplane(uint32_t model) {
		if (m_vars.m_aquaplane_restore.find(model) == m_vars.m_aquaplane_restore.end()) {
			m_vars.m_aquaplane_restore[model] = {
				get_data()->m_aquaplane_force,
				get_data()->m_aquaplane_push_water_mult,
				get_data()->m_aquaplane_push_water_cap,
				get_data()->m_aquaplane_push_water_apply,
				get_data()->m_keel_sphere_size,
				get_data()->m_prop_radius,
				get_data()->m_impeller_offset,
				get_data()->m_impeller_force_mult,
				get_data()->m_prow_raise_mult
			};
		}
	}

	void cache_rudder(uint32_t model) {
		if (m_vars.m_rudder_restore.find(model) == m_vars.m_rudder_restore.end()) {
			m_vars.m_rudder_restore[model] = {
				get_data()->m_rudder_force,
				get_data()->m_rudder_offset_submerge,
				get_data()->m_rudder_offset_force,
				get_data()->m_rudder_offset_force_z_mult
			};
		}
	}

	void cache_resistance(uint32_t model) {
		if (m_vars.m_resistance_restore.find(model) == m_vars.m_resistance_restore.end()) {
			m_vars.m_resistance_restore[model] = {
				get_data()->m_drag_coefficient,
				get_data()->m_vec_move_resistance,
				get_data()->m_vec_turn_resistance
			};
		}
	}

	void cache_misc(uint32_t model) {
		if (m_vars.m_misc_restore.find(model) == m_vars.m_misc_restore.end()) {
			m_vars.m_misc_restore[model] = {
				get_data()->m_wave_audio_mult,
				get_data()->m_look_lr_cam_height,
				get_data()->m_low_lod_ang_offset,
				get_data()->m_low_lod_draught_offset,
				get_data()->m_dinghy_sphere_buoy_const
			};
		}
	}
}

void vehicle_modifiers_handling_boat_menu::load() {
	set_name("Boat Handling");
	set_parent<vehicle_modifiers_handling_main_menu>();

	add_option(button_option("Reset to Default")
		.add_translate().add_hotkey()
		.add_sprite({ "ozarktextures", "spinner.png" })
		.add_sprite_scale({ 0.01232f, 0.02184f })
		.add_sprite_rotation()
		.add_click(reset));

	add_string("Box Front Multiplier");
	add_string("Box Rear Multiplier");
	add_string("Box Side Multiplier");
	add_string("Sample Top");
	add_string("Sample Bottom");

	add_string("Aquaplane Force");
	add_string("Aquaplane Push Water Multiplier");
	add_string("Aquaplane Push Water Cap");
	add_string("Aquaplane Push Water Apply");
	add_string("Keel Sphere Size");
	add_string("Propeller Radius");
	add_string("Impeller Offset");
	add_string("Impeller Force Multiplier");
	add_string("Prow Raise Multiplier");

	add_string("Rudder Force");
	add_string("Rudder Offset Submerge");
	add_string("Rudder Offset Force");
	add_string("Rudder Offset Force Z Multiplier");

	add_string("Drag Coefficient");
	add_string("Move Resistance - Horizontal (X)");
	add_string("Move Resistance - Vertical (Y)");
	add_string("Move Resistance - Height (Z)");
	add_string("Turn Resistance - Horizontal (X)");
	add_string("Turn Resistance - Vertical (Y)");
	add_string("Turn Resistance - Height (Z)");

	add_string("Wave Audio Multiplier");
	add_string("Look L/R Cam Height");
	add_string("Low Lod Angular Offset");
	add_string("Low Lod Draught Offset");
	add_string("Dinghy Sphere Buoy Const");
}

void vehicle_modifiers_handling_boat_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous(true);
		return;
	}

	uint32_t model = native::get_entity_model(menu::player::get_local_player().m_vehicle);
	if (!(native::is_this_model_a_boat(model) || native::is_this_model_an_emergency_boat(model))) {
		menu::submenu::handler::set_submenu_previous(true);
		return;
	}
}

void vehicle_modifiers_handling_boat_menu::update_once() {
	clear_options(1);

	uint32_t model = native::get_entity_model(menu::player::get_local_player().m_vehicle);

	/* Physical */
	if (m_vars.m_type == 0) {
		cache_physical(model);

		add_option(number_option<float>(SCROLL, get_string("Box Front Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_box_front_mult, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Box Rear Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_box_rear_mult, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Box Side Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_box_side_mult, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Sample Top"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_sample_top, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Sample Bottom"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_sample_bottom, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());
	}

	/* Aquaplane */
	if (m_vars.m_type == 1) {
		cache_aquaplane(model);

		add_option(number_option<float>(SCROLL, get_string("Aquaplane Force"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_aquaplane_force, "%.2f", 0.01f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Aquaplane Push Water Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_aquaplane_push_water_mult, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Aquaplane Push Water Cap"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_aquaplane_push_water_cap, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Aquaplane Push Water Apply"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_aquaplane_push_water_apply, "%.3f", 0.3f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Keel Sphere Size"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_keel_sphere_size, "%.0f", 1.f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Propeller Radius"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_prop_radius, "%.1f", 0.1f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Impeller Offset"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_impeller_offset, "%.0f", 1.f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Impeller Force Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_impeller_force_mult, "%.0f", 1.f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Prow Raise Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_prow_raise_mult, "%.1f", 0.1f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());
	}

	/* Rudder */
	if (m_vars.m_type == 2) {
		cache_rudder(model);

		add_option(number_option<float>(SCROLL, get_string("Rudder Force"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_rudder_force, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Rudder Offset Submerge"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_rudder_offset_submerge, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Rudder Offset Force"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_rudder_offset_force, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Rudder Offset Force Z Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_rudder_offset_force_z_mult, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());
	}

	/* Resistance */
	if (m_vars.m_type == 3) {
		cache_resistance(model);

		add_option(number_option<float>(SCROLL, get_string("Drag Coefficient"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_drag_coefficient, "%.0f", 1.f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Move Resistance - Horizontal (X)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_vec_move_resistance.x, "%.0f", 1.f); })
			.add_min(-10000.f).add_max(10000.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Move Resistance - Vertical (Y)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_vec_move_resistance.y, "%.0f", 1.f); })
			.add_min(-10000.f).add_max(10000.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Move Resistance - Height (Z)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_vec_move_resistance.z, "%.0f", 1.f); })
			.add_min(-10000.f).add_max(10000.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Turn Resistance - Horizontal (X)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_vec_turn_resistance.x, "%.1f", 0.1f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Turn Resistance - Vertical (Y)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_vec_turn_resistance.y, "%.1f", 0.1f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Turn Resistance - Height (Z)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_vec_turn_resistance.z, "%.1f", 0.1f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());
	}

	/* Miscellaneous */
	if (m_vars.m_type == 4) {
		cache_misc(model);

		add_option(number_option<float>(SCROLL, get_string("Wave Audio Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_wave_audio_mult, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Look L/R Cam Height"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_look_lr_cam_height, "%.0f", 1.f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Low Lod Angular Offset"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_low_lod_ang_offset, "%.2f", 0.01f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Low Lod Draught Offset"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_low_lod_draught_offset, "%.3f", 0.3f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Dinghy Sphere Buoy Const"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_dinghy_sphere_buoy_const, "%.0f", 1.f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());
	}
}

void vehicle_modifiers_handling_boat_menu::feature_update() {}

vehicle_modifiers_handling_boat_menu* g_instance;
vehicle_modifiers_handling_boat_menu* vehicle_modifiers_handling_boat_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_modifiers_handling_boat_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
