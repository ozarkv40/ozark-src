#include "vehicle_modifiers_handling_bike.h"
#include "menu/base/submenu_handler.h"
#include "vehicle_modifiers_handling_main.h"

using namespace vehicle::modifiers::handling::bike::vars;

namespace vehicle::modifiers::handling::bike::vars {
	variables m_vars;

	rage::types::bike_handling_data* get_data() {
		static rage::types::bike_handling_data hd;

		if (global::vars::g_ped_factory) {
			if (global::vars::g_ped_factory->m_local_ped) {
				if (global::vars::g_ped_factory->m_local_ped->m_vehicle) {
					if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data) {
						if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_sub_handling_data) {
							if (global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_sub_handling_data->m_sub_handling_data) {
								return &global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_sub_handling_data->m_sub_handling_data->m_bike_handling_data;
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
					get_data()->m_lean_fwd_com_mult = backup.m_lean_fwd_com_mult;
					get_data()->m_lean_fwd_force_mult = backup.m_lean_fwd_force_mult;
					get_data()->m_lean_bak_com_mult = backup.m_lean_bak_com_mult;
					get_data()->m_lean_bak_force_mult = backup.m_lean_bak_force_mult;
					get_data()->m_max_bank_angle = backup.m_max_bank_angle;
					get_data()->m_full_anim_angle = backup.m_full_anim_angle;
					get_data()->m_des_lean_return_frac = backup.m_des_lean_return_frac;
					get_data()->m_stick_lean_mult = backup.m_stick_lean_mult;
					get_data()->m_braking_stability_mult = backup.m_braking_stability_mult;
					get_data()->m_in_air_steer_mult = backup.m_in_air_steer_mult;
					get_data()->m_jump_force = backup.m_jump_force;
				}

				break;

			case 1: /* Balance */
				if (m_vars.m_balance_restore.find(model) != m_vars.m_balance_restore.end()) {
					auto& backup = m_vars.m_balance_restore[model];
					get_data()->m_bike_on_stand_steer_angle = backup.m_bike_on_stand_steer_angle;
					get_data()->m_bike_on_stand_lean_angle = backup.m_bike_on_stand_lean_angle;
					get_data()->m_front_balance_mult = backup.m_front_balance_mult;
					get_data()->m_rear_balance_mult = backup.m_rear_balance_mult;
					get_data()->m_wheelie_balance_point = backup.m_wheelie_balance_point;
					get_data()->m_stoppie_balance_point = backup.m_stoppie_balance_point;
					get_data()->m_wheelie_steer_mult = backup.m_wheelie_steer_mult;
				}
				break;

			case 2: /* Friction */
				if (m_vars.m_friction_restore.find(model) != m_vars.m_friction_restore.end()) {
					auto& backup = m_vars.m_friction_restore[model];
					get_data()->m_bike_ground_side_friction_mult = backup.m_bike_ground_side_friction_mult;
					get_data()->m_bike_wheel_ground_side_friction_mult = backup.m_bike_wheel_ground_side_friction_mult;
				}
				break;
		}
	}

	void cache_physical(uint32_t model) {
		if (m_vars.m_physical_restore.find(model) == m_vars.m_physical_restore.end()) {
			m_vars.m_physical_restore[model] = {
				get_data()->m_lean_fwd_com_mult,
				get_data()->m_lean_fwd_force_mult,
				get_data()->m_lean_bak_com_mult,
				get_data()->m_lean_bak_force_mult,
				get_data()->m_max_bank_angle,
				get_data()->m_full_anim_angle,
				get_data()->m_des_lean_return_frac,
				get_data()->m_stick_lean_mult,
				get_data()->m_braking_stability_mult,
				get_data()->m_in_air_steer_mult,
				get_data()->m_jump_force,
			};
		}
	}

	void cache_balance(uint32_t model) {
		if (m_vars.m_balance_restore.find(model) == m_vars.m_balance_restore.end()) {
			m_vars.m_balance_restore[model] = {
				get_data()->m_bike_on_stand_steer_angle,
				get_data()->m_bike_on_stand_lean_angle,
				get_data()->m_front_balance_mult,
				get_data()->m_rear_balance_mult,
				get_data()->m_wheelie_balance_point,
				get_data()->m_stoppie_balance_point,
				get_data()->m_wheelie_steer_mult
			};
		}
	}

	void cache_friction(uint32_t model) {
		if (m_vars.m_friction_restore.find(model) == m_vars.m_friction_restore.end()) {
			m_vars.m_friction_restore[model] = {
				get_data()->m_bike_ground_side_friction_mult,
				get_data()->m_bike_wheel_ground_side_friction_mult
			};
		}
	}
}

void vehicle_modifiers_handling_bike_menu::load() {
	set_name("Bike Handling");
	set_parent<vehicle_modifiers_handling_main_menu>();

	add_option(button_option("Reset to Default")
		.add_translate().add_hotkey()
		.add_sprite({ "ozarktextures", "spinner.png" })
		.add_sprite_scale({ 0.01232f, 0.02184f })
		.add_sprite_rotation()
		.add_click(reset));

	add_string("Lean Forward COM Multiplier");
	add_string("Lean Forward Force Multiplier");
	add_string("Lean Backward COM Multiplier");
	add_string("Lean Backward Force Multiplier");
	add_string("Max Bank Angle");
	add_string("Full Animation Angle");
	add_string("Lean Return Fraction");
	add_string("Stick Lean Multiplier");
	add_string("Braking Stability Multiplier");
	add_string("In Air Steer Multiplier");
	add_string("Jump Force");

	add_string("On Stand Steer Angle");
	add_string("On Stand Lean Angle");
	add_string("Front Balance Multiplier");
	add_string("Rear Balance Multiplier");
	add_string("Wheelie Balance Point");
	add_string("Stoppie Balance Point");
	add_string("Wheelie Steer Multiplier");

	add_string("Ground Side Friction Multiplier");
	add_string("Wheel Ground Side Friction Multiplier");
}

void vehicle_modifiers_handling_bike_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous(true);
		return;
	}

	uint32_t model = native::get_entity_model(menu::player::get_local_player().m_vehicle);
	if (!(native::is_this_model_a_bicycle(model) || native::is_this_model_a_bike(model))) {
		menu::submenu::handler::set_submenu_previous(true);
		return;
	}
}

void vehicle_modifiers_handling_bike_menu::update_once() {
	clear_options(1);

	uint32_t model = native::get_entity_model(menu::player::get_local_player().m_vehicle);

	/* Physical */
	if (m_vars.m_type == 0) {
		cache_physical(model);

		add_option(number_option<float>(SCROLL, get_string("Lean Forward COM Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_lean_fwd_com_mult, "%.1f", 0.1f); })
			.add_min(-500.f).add_max(500.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Lean Forward Force Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_lean_fwd_force_mult, "%.1f", 0.1f); })
			.add_min(-500.f).add_max(500.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Lean Backward COM Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_lean_bak_com_mult, "%.1f", 0.1f); })
			.add_min(-500.f).add_max(500.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Lean Backward Force Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_lean_bak_force_mult, "%.1f", 0.1f); })
			.add_min(-500.f).add_max(500.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Max Bank Angle"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_max_bank_angle, "%.2f", 0.01f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Full Animation Angle"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_full_anim_angle, "%.2f", 0.01f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Lean Return Fraction"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_des_lean_return_frac, "%.2f", 0.01f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Stick Lean Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_stick_lean_mult, "%.1f", 0.1f); })
			.add_min(-500.f).add_max(500.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Braking Stability Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_braking_stability_mult, "%.1f", 0.1f); })
			.add_min(-500.f).add_max(500.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("In Air Steer Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_in_air_steer_mult, "%.1f", 0.1f); })
			.add_min(-500.f).add_max(500.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Jump Force"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_jump_force, "%.1f", 0.1f); })
			.add_min(-500.f).add_max(500.f).set_scroll_speed(10).show_max());
	}

	/* Balance */
	if (m_vars.m_type == 1) {
		cache_balance(model);

		add_option(number_option<float>(SCROLL, get_string("On Stand Steer Angle"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_bike_on_stand_steer_angle, "%.1f", 0.1f); })
			.add_min(-500.f).add_max(500.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("On Stand Lean Angle"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_bike_on_stand_lean_angle, "%.1f", 0.1f); })
			.add_min(-500.f).add_max(500.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Front Balance Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_front_balance_mult, "%.1f", 0.1f); })
			.add_min(-500.f).add_max(500.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Rear Balance Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_rear_balance_mult, "%.1f", 0.1f); })
			.add_min(-500.f).add_max(500.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Wheelie Balance Point"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_wheelie_balance_point, "%.1f", 0.1f); })
			.add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Stoppie Balance Point"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_stoppie_balance_point, "%.1f", 0.1f); })
			.add_min(-100.f).add_max(500.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Wheelie Steer Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_wheelie_steer_mult, "%.1f", 0.1f); })
			.add_min(-500.f).add_max(500.f).set_scroll_speed(10).show_max());
	}

	/* Friction */
	if (m_vars.m_type == 2) {
		cache_friction(model);

		add_option(number_option<float>(SCROLL, get_string("Ground Side Friction Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_bike_ground_side_friction_mult, "%.1f", 0.1f); })
			.add_min(-500.f).add_max(500.f).set_scroll_speed(10).show_max());

		add_option(number_option<float>(SCROLL, get_string("Wheel Ground Side Friction Multiplier"))
			.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; })
			.add_update([](number_option<float>* option, int pos) { option->add_number(get_data()->m_bike_wheel_ground_side_friction_mult, "%.1f", 0.1f); })
			.add_min(-500.f).add_max(500.f).set_scroll_speed(10).show_max());
	}
}

void vehicle_modifiers_handling_bike_menu::feature_update() {}

vehicle_modifiers_handling_bike_menu* g_instance;
vehicle_modifiers_handling_bike_menu* vehicle_modifiers_handling_bike_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_modifiers_handling_bike_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
