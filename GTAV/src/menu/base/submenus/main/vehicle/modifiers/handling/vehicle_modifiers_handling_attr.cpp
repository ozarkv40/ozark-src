#include "vehicle_modifiers_handling_attr.h"
#include "menu/base/submenu_handler.h"
#include "vehicle_modifiers_handling_main.h"

using namespace vehicle::modifiers::handling::attr::vars;

namespace vehicle::modifiers::handling::attr::vars {
	variables m_vars;

	scroll_struct<float> drive_bias[] = {
		{ localization("RWD", true), 0.f },
		{ localization("4WD", true), 0.5f },
		{ localization("FWD", true), 1.f }
	};

	rage::types::handling_data* get_data() {
		static rage::types::handling_data hd;

		if (global::vars::g_ped_factory) {
			if (global::vars::g_ped_factory->m_local_ped) {
				if (global::vars::g_ped_factory->m_local_ped->m_vehicle) {
					if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data) {
						return global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data;
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
					get_data()->m_mass = backup.m_mass;
					get_data()->m_downforce_modifier = backup.m_downforce_modifier;
					get_data()->m_percent_submerged = backup.m_percent_submerged;
					get_data()->m_vec_centre_of_mass_offset = backup.m_vec_centre_of_mass_offset;
					get_data()->m_vec_inertia_multiplier = backup.m_vec_inertia_multiplier;
				}
				break;

			case 1: /* Transmission */
				if (m_vars.m_transmission_restore.find(model) != m_vars.m_transmission_restore.end()) {
					auto& backup = m_vars.m_transmission_restore[model];
					get_data()->m_drive_bias_front = backup.m_drive_bias_front;
					get_data()->m_initial_drive_gears = backup.m_initial_drive_gears;
					get_data()->m_initial_drive_force = backup.m_initial_drive_force;
					get_data()->m_drive_inertia = backup.m_drive_inertia;
					get_data()->m_initial_drive_max_flat_vel = backup.m_initial_drive_max_flat_vel;
					get_data()->m_clutch_change_rate_scale_up_shift = backup.m_clutch_change_rate_scale_up_shift;
					get_data()->m_clutch_change_rate_scale_down_shift = backup.m_clutch_change_rate_scale_down_shift;
					get_data()->m_brake_force = backup.m_brake_force;
					get_data()->m_hand_brake_force = backup.m_hand_brake_force;
					get_data()->m_steering_lock = backup.m_steering_lock;

					if (get_data()->m_drive_bias_front == 0.0f)
						m_vars.m_drive_bias_front = 0;
					else if (get_data()->m_drive_bias_front == 0.5f)
						m_vars.m_drive_bias_front = 1;
					else if (get_data()->m_drive_bias_front == 1.0f)
						m_vars.m_drive_bias_front = 2;
				}
				break;

			case 2: /* Wheel Traction */
				if (m_vars.m_wheel_traction_restore.find(model) != m_vars.m_wheel_traction_restore.end()) {
					auto& backup = m_vars.m_wheel_traction_restore[model];
					get_data()->m_traction_curve_max = backup.m_traction_curve_max;
					get_data()->m_traction_spring_delta_max = backup.m_traction_spring_delta_max;
					get_data()->m_low_speed_traction_loss_mult = backup.m_low_speed_traction_loss_mult;
					get_data()->m_camber_stiffness = backup.m_camber_stiffness;
					get_data()->m_traction_loss_mult = backup.m_traction_loss_mult;
				}
				break;

			case 3: /* Suspension */
				if (m_vars.m_suspension_restore.find(model) != m_vars.m_suspension_restore.end()) {
					auto& backup = m_vars.m_suspension_restore[model];
					get_data()->m_suspension_force = backup.m_suspension_force;
					get_data()->m_suspension_comp_damp = backup.m_suspension_comp_damp;
					get_data()->m_suspension_rebound_damp = backup.m_suspension_rebound_damp;
					get_data()->m_suspension_upper_limit = backup.m_suspension_upper_limit;
					get_data()->m_suspension_lower_limit = backup.m_suspension_lower_limit;
					get_data()->m_anti_roll_bar_force = backup.m_anti_roll_bar_force;
					get_data()->m_roll_centre_height_front = backup.m_roll_centre_height_front;
					get_data()->m_roll_centre_height_rear = backup.m_roll_centre_height_rear;
				}
				break;

			case 4: /* Damage */
				if (m_vars.m_damage_restore.find(model) != m_vars.m_damage_restore.end()) {
					auto& backup = m_vars.m_damage_restore[model];
					get_data()->m_collision_damage_mult = backup.m_collision_damage_mult;
					get_data()->m_weapon_damage_mult = backup.m_weapon_damage_mult;
					get_data()->m_deformation_damage_mult = backup.m_deformation_damage_mult;
					get_data()->m_engine_damage_mult = backup.m_engine_damage_mult;
					get_data()->m_petrol_tank_volume = backup.m_petrol_tank_volume;
				}
				break;

			case 5: /* Misc */
				if (m_vars.m_misc_restore.find(model) != m_vars.m_misc_restore.end()) {
					auto& backup = m_vars.m_misc_restore[model];
					get_data()->m_oil_volume = backup.m_oil_volume;
					get_data()->m_seat_offset = backup.m_seat_offset;
					get_data()->m_monetary_value = backup.m_monetary_value;
				}
				break;
		}
	}

	void cache_physical(uint32_t model) {
		if (m_vars.m_physical_restore.find(model) == m_vars.m_physical_restore.end()) {
			m_vars.m_physical_restore[model] = {
				get_data()->m_mass,
				get_data()->m_downforce_modifier,
				get_data()->m_percent_submerged,
				get_data()->m_vec_centre_of_mass_offset,
				get_data()->m_vec_inertia_multiplier
			};
		}
	}

	void cache_transmission(uint32_t model) {
		if (m_vars.m_transmission_restore.find(model) == m_vars.m_transmission_restore.end()) {
			m_vars.m_transmission_restore[model] = {
				get_data()->m_drive_bias_front,
				get_data()->m_initial_drive_gears,
				get_data()->m_initial_drive_force,
				get_data()->m_drive_inertia,
				get_data()->m_initial_drive_max_flat_vel,
				get_data()->m_clutch_change_rate_scale_up_shift,
				get_data()->m_clutch_change_rate_scale_down_shift,
				get_data()->m_brake_force,
				get_data()->m_hand_brake_force,
				get_data()->m_steering_lock
			};
		}
	}

	void cache_wheel_traction(uint32_t model) {
		if (m_vars.m_wheel_traction_restore.find(model) == m_vars.m_wheel_traction_restore.end()) {
			m_vars.m_wheel_traction_restore[model] = {
				get_data()->m_traction_curve_max,
				get_data()->m_traction_spring_delta_max,
				get_data()->m_low_speed_traction_loss_mult,
				get_data()->m_camber_stiffness,
				get_data()->m_traction_loss_mult
			};
		}
	}

	void cache_suspension(uint32_t model) {
		if (m_vars.m_suspension_restore.find(model) == m_vars.m_suspension_restore.end()) {
			m_vars.m_suspension_restore[model] = {
				get_data()->m_suspension_force,
				get_data()->m_suspension_comp_damp,
				get_data()->m_suspension_rebound_damp,
				get_data()->m_suspension_upper_limit,
				get_data()->m_suspension_lower_limit,
				get_data()->m_anti_roll_bar_force,
				get_data()->m_roll_centre_height_front,
				get_data()->m_roll_centre_height_rear
			};
		}
	}

	void cache_damage(uint32_t model) {
		if (m_vars.m_damage_restore.find(model) == m_vars.m_damage_restore.end()) {
			m_vars.m_damage_restore[model] = {
				get_data()->m_collision_damage_mult,
				get_data()->m_weapon_damage_mult,
				get_data()->m_deformation_damage_mult,
				get_data()->m_engine_damage_mult,
				get_data()->m_petrol_tank_volume,
				get_data()->m_oil_volume
			};
		}
	}

	void cache_misc(uint32_t model) {
		if (m_vars.m_misc_restore.find(model) == m_vars.m_misc_restore.end()) {
			m_vars.m_misc_restore[model] = {
				get_data()->m_oil_volume,
				get_data()->m_seat_offset,
				get_data()->m_monetary_value
			};
		}
	}
}

void vehicle_modifiers_handling_attr_menu::load() {
	set_name("Handling Attributes");
	set_parent<vehicle_modifiers_handling_main_menu>();

	add_option(button_option("Reset to Default")
		.add_translate().add_hotkey()
		.add_sprite({ "ozarktextures", "spinner.png" })
		.add_sprite_scale({ 0.01232f, 0.02184f })
		.add_sprite_rotation()
		.add_click(reset));

	add_string("Mass");
	add_string("Downforce Modifier");
	add_string("Percent Submerged");
	add_string("Center of Mass - Horizontal (X");
	add_string("Center of Mass - Vertical (Y)");
	add_string("Center of Mass - Height (Z)");
	add_string("Inertia Multiplier - Horizontal (X)");
	add_string("Inertia Multiplier - Vertical (Y)");
	add_string("Inertia Multiplier - Height (Z)");

	add_string("Drive Type");
	add_string("Drive Gears");
	add_string("Drive Force");
	add_string("Drive Inertia");
	add_string("Drive Max Flat Velocity");
	add_string("Clutch Shift Up Multiplier");
	add_string("Clutch Shift Down Multiplier");
	add_string("Brake Force");
	add_string("Handbrake Force");
	add_string("Steering Lock");

	add_string("Traction Curve Max");
	add_string("Traction Spring Delta Max");
	add_string("Low Speed Traction Loss Multiplier");
	add_string("Camber Stiffnesss");
	add_string("Traction Loss Multiplier");

	add_string("Suspension Force");
	add_string("Suspension Compression Damping");
	add_string("Suspension Rebound Damping");
	add_string("Suspension Upper Limit");
	add_string("Suspension Lower Limit");
	add_string("Suspension Anti Rollbar force");
	add_string("Roll Centre Height Front");
	add_string("Roll Centre Height Rear");

	add_string("Collision Damage Multiplier");
	add_string("Weapon Damage Multiplier");
	add_string("Deformation Damage Multiplier");
	add_string("Engine Damage Multiplier");
	add_string("Petrol Tank Volume");

	add_string("Oil Volume");
	add_string("Seat Offset - Horizontal (X)");
	add_string("Seat Offset - Vertical (Y)");
	add_string("Seat Offset - Height (Z)");
	add_string("Monetary Value");
}

void vehicle_modifiers_handling_attr_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous(true);
		return;
	}
}

void vehicle_modifiers_handling_attr_menu::update_once() {
	clear_options(1);

	uint32_t model = native::get_entity_model(menu::player::get_local_player().m_vehicle);

	/* Physical */
	if (m_vars.m_type == 0) {
		cache_physical(model);

		add_option(number_option<float>(SCROLL, get_string("Mass"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_mass, "%.0f", 1.f); })
			.add_min(0.0f).add_max(10000.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Downforce Modifier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_downforce_modifier, "%.0f", 1.f); })
			.add_min(0.0f).add_max(10000.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Percent Submerged"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_percent_submerged, "%.1f", 0.1f); })
			.add_min(0.0f).add_max(500.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Center of Mass - Horizontal (X)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_vec_centre_of_mass_offset.x, "%.2f", 0.01f); })
			.add_min(-5.f).add_max(5.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Center of Mass - Vertical (Y)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_vec_centre_of_mass_offset.y, "%.2f", 0.01f); })
			.add_min(-5.f).add_max(5.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Center of Mass - Height (Z)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_vec_centre_of_mass_offset.z, "%.2f", 0.01f); })
			.add_min(-5.f).add_max(5.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Inertia Multiplier - Horizontal (X)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_vec_inertia_multiplier.x, "%.2f", 0.01f); })
			.add_min(-5.f).add_max(5.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Inertia Multiplier - Vertical (Y)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_vec_inertia_multiplier.y, "%.2f", 0.01f); })
			.add_min(-5.f).add_max(5.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Inertia Multiplier - Height (Z)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_vec_inertia_multiplier.z, "%.2f", 0.01f); })
			.add_min(-5.f).add_max(5.f).set_scroll_speed(10).show_max());

		return;
	}

	/* Transmission */
	if (m_vars.m_type == 1) {
		cache_transmission(model);

		if (get_data()->m_drive_bias_front == 0.0f)
			m_vars.m_drive_bias_front = 0;
		else if (get_data()->m_drive_bias_front == 0.5f)
			m_vars.m_drive_bias_front = 1;
		else if (get_data()->m_drive_bias_front == 1.0f)
			m_vars.m_drive_bias_front = 2;

		add_option(scroll_option<float>(SCROLL, get_string("Drive Type"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_scroll(m_vars.m_drive_bias_front, 0, NUMOF(drive_bias), drive_bias)
			.add_update([](scroll_option<float>* option, int pos) { get_data()->m_drive_bias_front = drive_bias[m_vars.m_drive_bias_front].m_result; }));

		add_option(number_option<uint8_t>(SCROLL, get_string("Drive Gears"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<uint8_t>* option, int pos) { option->add_number(get_data()->m_initial_drive_gears, "%i", 1); })
			.add_min(1).add_max(16).show_max());

		add_option(number_option<float>(SCROLL, get_string("Drive Force"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_initial_drive_force, "%.2f", 0.01f); })
			.add_min(0.0f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Drive Inertia"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_drive_inertia, "%.2f", 0.01f); })
			.add_min(0.0f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Drive Max Flat Velocity"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_initial_drive_max_flat_vel, "%.1f", 0.1f); })
			.add_min(0.0f).add_max(500.f).show_max().set_scroll_speed(10));

		add_option(number_option<float>(SCROLL, get_string("Clutch Shift Up Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_clutch_change_rate_scale_up_shift, "%.1f", 0.1f); })
			.add_min(0.0f).add_max(100.f).show_max().set_scroll_speed(10));

		add_option(number_option<float>(SCROLL, get_string("Clutch Shift Down Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_clutch_change_rate_scale_down_shift, "%.1f", 0.1f); })
			.add_min(0.0f).add_max(100.f).show_max().set_scroll_speed(10));

		add_option(number_option<float>(SCROLL, get_string("Brake Force"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_brake_force, "%.1f", 0.1f); })
			.add_min(0.f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Handbrake Force"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_hand_brake_force, "%.1f", 0.1f); })
			.add_min(0.f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Steering Lock"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_steering_lock, "%.1f", 0.1f); })
			.add_min(0.f).add_max(100.f).show_max());

		return;
	}

	/* Wheel Traction */
	if (m_vars.m_type == 2) {
		cache_wheel_traction(model);

		add_option(number_option<float>(SCROLL, get_string("Traction Curve Max"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_traction_curve_max, "%.1f", 0.1f); })
			.add_min(0.f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Traction Spring Delta Max"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_traction_spring_delta_max, "%.1f", 0.1f); })
			.add_min(0.f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Low Speed Traction Loss Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_low_speed_traction_loss_mult, "%.1f", 0.1f); })
			.add_min(0.f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Camber Stiffnesss"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_camber_stiffness, "%.1f", 0.1f); })
			.add_min(0.f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Traction Loss Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_traction_loss_mult, "%.1f", 0.1f); })
			.add_min(0.f).add_max(100.f).show_max());

		return;
	}

	/* Suspension */
	if (m_vars.m_type == 3) {
		cache_suspension(model);

		add_option(number_option<float>(SCROLL, get_string("Suspension Force"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_suspension_force, "%.1f", 0.1f); })
			.add_min(0.1f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Suspension Compression Damping"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_suspension_comp_damp, "%.1f", 0.1f); })
			.add_min(0.1f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Suspension Rebound Damping"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_suspension_rebound_damp, "%.1f", 0.1f); })
			.add_min(0.1f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Suspension Upper Limit"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_suspension_upper_limit, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Suspension Lower Limit"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_suspension_lower_limit, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Suspension Anti Rollbar force"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_anti_roll_bar_force, "%.1f", 0.1f); })
			.add_min(0.1f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Roll Centre Height Front"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_roll_centre_height_front, "%.1f", 0.1f); })
			.add_min(0.1f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Roll Centre Height Rear"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_roll_centre_height_rear, "%.1f", 0.1f); })
			.add_min(0.1f).add_max(100.f).show_max());

		return;
	}

	/* Damage */
	if (m_vars.m_type == 4) {
		cache_damage(model);

		add_option(number_option<float>(SCROLL, get_string("Collision Damage Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_collision_damage_mult, "%.1f", 0.1f); })
			.add_min(0.0f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Weapon Damage Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_weapon_damage_mult, "%.1f", 0.1f); })
			.add_min(0.0f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Deformation Damage Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_deformation_damage_mult, "%.1f", 0.1f); })
			.add_min(0.0f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Engine Damage Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_engine_damage_mult, "%.1f", 0.1f); })
			.add_min(0.0f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Petrol Tank Volume"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_petrol_tank_volume, "%.1f", 0.1f); })
			.add_min(0.0f).add_max(100.f).show_max());

		return;
	}

	/* Misc */
	if (m_vars.m_type == 5) {
		cache_misc(model);

		add_option(number_option<float>(SCROLL, get_string("Oil Volume"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_oil_volume, "%.1f", 0.1f); })
			.add_min(0.0f).add_max(100.f).show_max());

		add_option(number_option<float>(SCROLL, get_string("Seat Offset - Horizontal (X)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_seat_offset.x, "%.2f", 0.01f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Seat Offset - Vertical (Y)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_seat_offset.y, "%.2f", 0.01f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Seat Offset - Height (Z)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_seat_offset.z, "%.2f", 0.01f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<int>(SCROLL, get_string("Monetary Value"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<int>* option, int pos) { option->add_number(get_data()->m_monetary_value, "%i", 1000); })
			.add_min(0).add_max(100000000).set_scroll_speed(0));

		return;
	}
}

void vehicle_modifiers_handling_attr_menu::feature_update() {}

vehicle_modifiers_handling_attr_menu* g_instance;
vehicle_modifiers_handling_attr_menu* vehicle_modifiers_handling_attr_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_modifiers_handling_attr_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
