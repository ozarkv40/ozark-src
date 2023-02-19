#include "vehicle_modifiers_handling_flying.h"
#include "menu/base/submenu_handler.h"
#include "vehicle_modifiers_handling_main.h"

using namespace vehicle::modifiers::handling::flying::vars;

namespace vehicle::modifiers::handling::flying::vars {
	variables m_vars;

	rage::types::flying_handling_data* get_data() {
		static rage::types::flying_handling_data hd;

		if (global::vars::g_ped_factory) {
			if (global::vars::g_ped_factory->m_local_ped) {
				if (global::vars::g_ped_factory->m_local_ped->m_vehicle) {
					if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data) {
						if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_sub_handling_data) {
							if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_sub_handling_data->m_sub_handling_data) {
								return &global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_sub_handling_data->m_sub_handling_data->m_flying_handling_data;
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
			case 0: /* Thrust */
				if (m_vars.m_ThrustRestore.find(model) != m_vars.m_ThrustRestore.end()) {
					auto& Backup = m_vars.m_ThrustRestore[model];
					get_data()->m_thrust = Backup.m_thrust;
					get_data()->m_thrust_fall_off = Backup.m_thrust_fall_off;
					get_data()->m_thrust_vectoring = Backup.m_thrust_vectoring;
				}
				break;

			case 1: /* Movement */
				if (m_vars.m_MovementRestore.find(model) != m_vars.m_MovementRestore.end()) {
					auto& Backup = m_vars.m_MovementRestore[model];
					get_data()->m_side_slip_mult = Backup.m_side_slip_mult;
					get_data()->m_yaw_mult = Backup.m_yaw_mult;
					get_data()->m_yaw_stabilise = Backup.m_yaw_stabilise;
					get_data()->m_roll_mult = Backup.m_roll_mult;
					get_data()->m_roll_stabilise = Backup.m_roll_stabilise;
					get_data()->m_pitch_mult = Backup.m_pitch_mult;
					get_data()->m_pitch_stabilise = Backup.m_pitch_stabilise;
					get_data()->m_form_lift_mult = Backup.m_form_lift_mult;
					get_data()->m_attack_lift_mult = Backup.m_attack_lift_mult;
					get_data()->m_attack_dive_mult = Backup.m_attack_dive_mult;
					get_data()->m_engine_off_glide_multi = Backup.m_engine_off_glide_multi;
				}
				break;

			case 2: /* Resistance */
				if (m_vars.m_ResistanceRestore.find(model) != m_vars.m_ResistanceRestore.end()) {
					auto& Backup = m_vars.m_ResistanceRestore[model];
					get_data()->m_wind_mult = Backup.m_wind_mult;
					get_data()->m_move_res = Backup.m_move_res;
					get_data()->m_vec_turn_resistance = Backup.m_vec_turn_resistance;
					get_data()->m_vec_speed_resistance = Backup.m_vec_speed_resistance;
				}
				break;

			case 3: /* Turbulence */
				if (m_vars.m_TurbulenceRestore.find(model) != m_vars.m_TurbulenceRestore.end()) {
					auto& Backup = m_vars.m_TurbulenceRestore[model];
					get_data()->m_turublence_magnitude_max = Backup.m_turublence_magnitude_max;
					get_data()->m_turublence_force_multi = Backup.m_turublence_force_multi;
					get_data()->m_turublence_roll_torque_multi = Backup.m_turublence_roll_torque_multi;
					get_data()->m_turublence_pitch_torque_multi = Backup.m_turublence_pitch_torque_multi;
				}
				break;

			case 4: /* Gear */
				if (m_vars.m_GearRestore.find(model) != m_vars.m_GearRestore.end()) {
					auto& Backup = m_vars.m_GearRestore[model];
					get_data()->m_gear_down_drag_v = Backup.m_gear_down_drag_v;
					get_data()->m_gear_down_lift_mult = Backup.m_gear_down_lift_mult;
				}
				break;

			case 5: /* Ground */
				if (m_vars.m_GroundRestore.find(model) != m_vars.m_GroundRestore.end()) {
					auto& Backup = m_vars.m_GroundRestore[model];
					get_data()->m_on_ground_yaw_boost_speed_peak = Backup.m_on_ground_yaw_boost_speed_peak;
					get_data()->m_on_ground_yaw_boost_speed_cap = Backup.m_on_ground_yaw_boost_speed_cap;
				}
				break;

			case 6: /* Misc */
				if (m_vars.m_MiscRestore.find(model) != m_vars.m_MiscRestore.end()) {
					auto& Backup = m_vars.m_MiscRestore[model];
					get_data()->m_body_damage_control_effect_mult = Backup.m_body_damage_control_effect_mult;
					get_data()->m_input_sensitivity_for_difficulty = Backup.m_input_sensitivity_for_difficulty;
				}
				break;
		}
	}

	void cache_thrust(uint32_t model) {
		if (m_vars.m_ThrustRestore.find(model) == m_vars.m_ThrustRestore.end()) {
			m_vars.m_ThrustRestore[model] = {
				get_data()->m_thrust,
				get_data()->m_thrust_fall_off,
				get_data()->m_thrust_vectoring
			};
		}
	}

	void cache_movement(uint32_t model) {
		if (m_vars.m_MovementRestore.find(model) == m_vars.m_MovementRestore.end()) {
			m_vars.m_MovementRestore[model] = {
				get_data()->m_side_slip_mult,
				get_data()->m_yaw_mult,
				get_data()->m_yaw_stabilise,
				get_data()->m_roll_mult,
				get_data()->m_roll_stabilise,
				get_data()->m_pitch_mult,
				get_data()->m_pitch_stabilise,
				get_data()->m_form_lift_mult,
				get_data()->m_attack_lift_mult,
				get_data()->m_attack_dive_mult,
				get_data()->m_engine_off_glide_multi,
			};
		}
	}

	void cache_resistance(uint32_t model) {
		if (m_vars.m_ResistanceRestore.find(model) == m_vars.m_ResistanceRestore.end()) {
			m_vars.m_ResistanceRestore[model] = {
				get_data()->m_wind_mult,
				get_data()->m_move_res,
				get_data()->m_vec_turn_resistance,
				get_data()->m_vec_speed_resistance
			};
		}
	}

	void cache_turbulence(uint32_t model) {
		if (m_vars.m_TurbulenceRestore.find(model) == m_vars.m_TurbulenceRestore.end()) {
			m_vars.m_TurbulenceRestore[model] = {
				get_data()->m_turublence_magnitude_max,
				get_data()->m_turublence_force_multi,
				get_data()->m_turublence_roll_torque_multi,
				get_data()->m_turublence_pitch_torque_multi
			};
		}
	}

	void cache_gear(uint32_t model) {
		if (m_vars.m_GearRestore.find(model) == m_vars.m_GearRestore.end()) {
			m_vars.m_GearRestore[model] = {
				get_data()->m_gear_down_drag_v,
				get_data()->m_gear_down_lift_mult
			};
		}
	}

	void cache_ground(uint32_t model) {
		if (m_vars.m_GroundRestore.find(model) == m_vars.m_GroundRestore.end()) {
			m_vars.m_GroundRestore[model] = {
				get_data()->m_on_ground_yaw_boost_speed_peak,
				get_data()->m_on_ground_yaw_boost_speed_cap
			};
		}
	}

	void cache_misc(uint32_t model) {
		if (m_vars.m_MiscRestore.find(model) == m_vars.m_MiscRestore.end()) {
			m_vars.m_MiscRestore[model] = {
				get_data()->m_body_damage_control_effect_mult,
				get_data()->m_input_sensitivity_for_difficulty
			};
		}
	}
}

void vehicle_modifiers_handling_flying_menu::load() {
	set_name("Flying Handling");
	set_parent<vehicle_modifiers_handling_main_menu>();

	add_option(button_option("Reset to Default")
		.add_translate().add_hotkey()
		.add_sprite({ "ozarktextures", "spinner.png" })
		.add_sprite_scale({ 0.01232f, 0.02184f })
		.add_sprite_rotation()
		.add_click(reset));

	add_string("Thrust");
	add_string("Thrust Falloff");
	add_string("Thrust Vectoring");

	add_string("Side Slip Multiplier");
	add_string("Yaw Multiplier");
	add_string("Yaw Stabilize");
	add_string("Roll Multiplier");
	add_string("Roll Stabilize");
	add_string("Pitch Multiplier");
	add_string("Pitch Stabilize");
	add_string("Form Lift Multiplier");
	add_string("Attack Lift Multiplier");
	add_string("Attack Dive Multiplier");
	add_string("Engine Off Glide Multiplier");

	add_string("Wind Multiplier");
	add_string("Move Resistance");
	add_string("Turn Resistance - Horizontal (X)");
	add_string("Turn Resistance - Vertical (Y)");
	add_string("Turn Resistance - Height (Z)");
	add_string("Speed Resistance - Horizontal (X)");
	add_string("Speed Resistance - Vertical (Y)");
	add_string("Speed Resistance - Height (Z)");

	add_string("Maximum Magnitude");
	add_string("Force Multiplier");
	add_string("Roll Torque Multiplier");
	add_string("Pitch Torque Multiplier");

	add_string("Down Drag");
	add_string("Down Lift Multiplier");

	add_string("Yaw Boost Speed Peak");
	add_string("Yaw Boost Speed Cap");

	add_string("Body Damage Multiplier");
	add_string("Input Sensitivity");
}

void vehicle_modifiers_handling_flying_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous(true);
		return;
	}

	uint32_t model = native::get_entity_model(menu::player::get_local_player().m_vehicle);
	if (!(native::is_this_model_a_plane(model) || native::is_this_model_a_heli(model))) {
		menu::submenu::handler::set_submenu_previous(true);
		return;
	}
}

void vehicle_modifiers_handling_flying_menu::update_once() {
	clear_options(1);

	uint32_t model = native::get_entity_model(menu::player::get_local_player().m_vehicle);

	/* Thrust */
	if (m_vars.m_type == 0) {
		cache_thrust(model);

		add_option(number_option<float>(SCROLL, get_string("Thrust"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_thrust, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Thrust Falloff"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_thrust_fall_off, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Thrust Vectoring"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_thrust_vectoring, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());
	}

	/* Movement */
	if (m_vars.m_type == 1) {
		cache_movement(model);

		add_option(number_option<float>(SCROLL, get_string("Side Slip Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_side_slip_mult, "%.2f", 0.01f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Yaw Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_yaw_mult, "%.3f", 0.001f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Yaw Stabilize"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_yaw_stabilise, "%.3f", 0.001f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Roll Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_roll_mult, "%.3f", 0.001f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Roll Stabilize"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_roll_stabilise, "%.3f", 0.001f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Pitch Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_pitch_mult, "%.3f", 0.001f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Pitch Stabilize"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_pitch_stabilise, "%.3f", 0.001f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Form Lift Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_form_lift_mult, "%.2f", 0.01f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Attack Lift Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_attack_lift_mult, "%.2f", 0.01f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Attack Dive Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_attack_dive_mult, "%.3f", 0.001f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Engine Off Glide Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_engine_off_glide_multi, "%.0f", 1.f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());
	}

	/* Resistance */
	if (m_vars.m_type == 2) {
		cache_resistance(model);

		add_option(number_option<float>(SCROLL, get_string("Wind Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_wind_mult, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Move Resistance"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_move_res, "%.3f", 0.001f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Turn Resistance - Horizontal (X)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_vec_turn_resistance.x, "%.2f", 0.01f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Turn Resistance - Vertical (Y)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_vec_turn_resistance.y, "%.2f", 0.01f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Turn Resistance - Height (Z)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_vec_turn_resistance.z, "%.2f", 0.01f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Speed Resistance - Horizontal (X)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_vec_speed_resistance.x, "%.2f", 0.01f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Speed Resistance - Vertical (Y)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_vec_speed_resistance.y, "%.2f", 0.01f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Speed Resistance - Height (Z)"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_vec_speed_resistance.z, "%.2f", 0.01f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());
	}

	/* Turbulence */
	if (m_vars.m_type == 3) {
		cache_turbulence(model);

		add_option(number_option<float>(SCROLL, get_string("Maximum Magnitude"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_turublence_magnitude_max, "%.0f", 1.f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Force Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_turublence_force_multi, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Roll Torque Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_turublence_roll_torque_multi, "%.2f", 0.01f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Pitch Torque Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_turublence_pitch_torque_multi, "%.2f", 0.01f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());
	}

	/* Gear */
	if (m_vars.m_type == 4) {
		cache_gear(model);

		add_option(number_option<float>(SCROLL, get_string("Down Drag"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_gear_down_drag_v, "%.2f", 0.01f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Down Lift Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_gear_down_lift_mult, "%.1f", 0.1f); })
			.add_min(-10.f).add_max(100.f).set_scroll_speed(10).show_max());
	}

	/* Ground */
	if (m_vars.m_type == 5) {
		cache_ground(model);

		add_option(number_option<float>(SCROLL, get_string("Yaw Boost Speed Peak"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_on_ground_yaw_boost_speed_peak, "%.0f", 1.f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Yaw Boost Speed Cap"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_on_ground_yaw_boost_speed_cap, "%.0f", 1.f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());
	}

	/* Miscellaneous */
	if (m_vars.m_type == 6) {
		cache_misc(model);

		add_option(number_option<float>(SCROLL, get_string("Body Damage Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_body_damage_control_effect_mult, "%.1f", 0.1f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Input Sensitivity"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_input_sensitivity_for_difficulty, "%.1f", 0.1f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());
	}
}

void vehicle_modifiers_handling_flying_menu::feature_update() {}

vehicle_modifiers_handling_flying_menu* g_instance;
vehicle_modifiers_handling_flying_menu* vehicle_modifiers_handling_flying_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_modifiers_handling_flying_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
