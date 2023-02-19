#include "vehicle.h"
#include "menu/base/submenu_handler.h"
#include "../main.h"
#include "global/lists.h"
#include "menu/base/util/control.h"
#include "vehicle/vehicle_health.h"
#include "vehicle/vehicle_weapons.h"
#include "vehicle/vehicle_particles.h"
#include "vehicle/vehicle_movement.h"
#include "vehicle/vehicle_boost.h"
#include "vehicle/vehicle_collision.h"
#include "vehicle/vehicle_gravity.h"
#include "vehicle/vehicle_multipliers.h"
#include "vehicle/vehicle_modifiers.h"
#include "vehicle/vehicle_autopilot.h"
#include "vehicle/vehicle_ramps.h"
#include "vehicle/vehicle_tyre_tracks.h"
#include "vehicle/vehicle_doors.h"
#include "vehicle/vehicle_speedometer.h"
#include "vehicle/vehicle_seats.h"
#include "vehicle/vehicle_randomization.h"
#include "vehicle/vehicle_customs.h"
#include "menu/base/util/control.h"

using namespace vehicle::vars;

namespace vehicle::vars {
	variables m_vars;

	scroll_struct<int> upgrades[] = {
		{ localization("Performance", true), 0 },
		{ localization("Everything", true), 0 },
	};

	Vehicle clone_vehicle(Vehicle veh) {
		Vehicle spawned_vehicle = 0;

		if (native::does_entity_exist(veh)) {
			uint32_t model = native::get_entity_model(veh);
			menu::control::simple_request_model(model);

			math::vector3<float> coords = native::get_entity_coords(veh, true);
			math::vector3<float> spawn_coords = coords + (native::get_entity_forward_vector(veh) * 5.f);

			spawned_vehicle = native::create_vehicle(model, spawn_coords.x, spawn_coords.y, spawn_coords.z, native::get_entity_heading(veh), true, true, 0);
			if (native::does_entity_exist(spawned_vehicle)) {
				native::set_vehicle_dirt_level(spawned_vehicle, native::get_vehicle_dirt_level(veh));
				native::set_vehicle_tyres_can_burst(spawned_vehicle, native::get_vehicle_tyres_can_burst(veh));
				native::set_vehicle_mod_kit(spawned_vehicle, 0);

				for (int i = MOD_SPOILER; i <= MOD_ARMOR; i++) {
					if (native::get_num_vehicle_mods(veh, i) > 0) {
						native::set_vehicle_mod(spawned_vehicle, i, native::get_vehicle_mod(veh, i), 0);
					}
				}

				for (int i = MOD_PLATEHOLDER; i <= MOD_LIVERY; i++) {
					if (native::get_num_vehicle_mods(veh, i) > 0) {
						native::set_vehicle_mod(spawned_vehicle, i, native::get_vehicle_mod(veh, i), 0);
					}
				}

				native::set_vehicle_wheel_type(spawned_vehicle, native::get_vehicle_wheel_type(veh));
				native::set_vehicle_mod(spawned_vehicle, MOD_FRONTWHEELS, native::get_vehicle_mod(veh, MOD_FRONTWHEELS), native::get_vehicle_mod_variation(veh, MOD_FRONTWHEELS));
				native::set_vehicle_mod(spawned_vehicle, MOD_BACKWHEELS, native::get_vehicle_mod(veh, MOD_BACKWHEELS), native::get_vehicle_mod_variation(veh, MOD_FRONTWHEELS));

				for (int i = MOD_UNK17; i <= MOD_XENONLIGHTS; i++) {
					native::toggle_vehicle_mod(spawned_vehicle, native::get_vehicle_mod_variation(veh, i), true);
				}

				int colors[2];
				int extra_colors[2];
				color_rgba tyre_smoke;
				color_rgba custom_primary;
				color_rgba custom_secondary;
				color_rgba neon;

				native::get_vehicle_custom_primary_colour(veh, &custom_primary.r, &custom_primary.g, &custom_primary.b);
				native::get_vehicle_custom_secondary_colour(veh, &custom_secondary.r, &custom_secondary.g, &custom_secondary.b);
				native::get_vehicle_neon_lights_colour(veh, &neon.r, &neon.g, &neon.b);
				native::get_vehicle_tyre_smoke_color(veh, &tyre_smoke.r, &tyre_smoke.g, &tyre_smoke.b);
				native::get_vehicle_colours(veh, &colors[0], &colors[1]);
				native::get_vehicle_extra_colours(veh, &extra_colors[0], &extra_colors[1]);

				native::set_vehicle_colours(spawned_vehicle, colors[0], colors[1]);
				native::set_vehicle_extra_colours(spawned_vehicle, extra_colors[0], extra_colors[1]);
				native::set_vehicle_window_tint(spawned_vehicle, native::get_vehicle_window_tint(veh));

				native::set_vehicle_tyre_smoke_color(spawned_vehicle, tyre_smoke.r, tyre_smoke.g, tyre_smoke.b);
				native::set_vehicle_custom_primary_colour(spawned_vehicle, custom_primary.r, custom_primary.g, custom_primary.b);
				native::set_vehicle_custom_secondary_colour(spawned_vehicle, custom_secondary.r, custom_secondary.g, custom_secondary.b);

				for (int i = 0; i < 4; i++) {
					native::set_vehicle_neon_light_enabled(spawned_vehicle, i, native::is_vehicle_neon_light_enabled(veh, i));
				}

				native::set_vehicle_neon_lights_colour(spawned_vehicle, neon.r, neon.g, neon.b);
				native::set_vehicle_number_plate_text_index(spawned_vehicle, native::get_vehicle_number_plate_text_index(veh));
				native::set_vehicle_number_plate_text(spawned_vehicle, native::get_vehicle_number_plate_text(veh));
			}
		}

		return spawned_vehicle;
	}

	void run_task(Vehicle veh, std::function<void(Vehicle)> callback) {
		if (veh) {
			if (menu::player::get_local_player().m_in_vehicle) {
				if (menu::player::get_local_player().m_vehicle == veh) {
					if (native::get_ped_in_vehicle_seat(veh, -1, 0) == menu::player::get_local_player().m_ped && !native::network_is_in_session()) {
						callback(veh);
						return;
					} else {
						if (native::network_has_control_of_entity(veh)) {
							callback(veh);
							return;
						}

						menu::control::request_control(veh, [=](Entity v) {
							callback(v);
						});

						return;
					}
				}
			}

			Ped driver = native::get_ped_in_vehicle_seat(veh, -1, 0);
			if (native::does_entity_exist(driver)) {
				if (native::is_ped_a_player(driver)) {
					if (native::network_has_control_of_entity(veh)) {
						callback(veh);
						return;
					}

					menu::control::request_control(veh, [=] (Entity v) {
						callback(v);
					});

					return;
				}
			}

			callback(veh);
		}
	}

	void max_upgrades(Vehicle vehicle, int type) {
		run_task(vehicle, [=](Vehicle veh) {
			if (type == 1) {
				native::set_vehicle_fixed(veh);
				native::set_vehicle_dirt_level(veh, 0);
				native::set_vehicle_tyres_can_burst(veh, false);
				native::set_vehicle_mod_kit(veh, 0);

				for (int i = MOD_SPOILER; i <= MOD_ARMOR; i++) {
					if (native::get_num_vehicle_mods(veh, i) > 0) {
						native::set_vehicle_mod(veh, i, native::get_num_vehicle_mods(veh, i) - 1, 0);
					}
				}

				for (int i = MOD_PLATEHOLDER; i <= MOD_LIVERY; i++) {
					if (native::get_num_vehicle_mods(veh, i) > 0) {
						native::set_vehicle_mod(veh, i, native::get_num_vehicle_mods(veh, i) - 1, 0);
					}
				}

				native::set_vehicle_mod(veh, MOD_HORNS, 30, 0);

				if (native::get_entity_model(veh) != joaat("vigilante")) {
					native::set_vehicle_wheel_type(veh, 7);
					native::set_vehicle_mod(veh, MOD_FRONTWHEELS, 39, 1);
					native::set_vehicle_mod(veh, MOD_BACKWHEELS, 39, 1);
				}

				for (int i = MOD_UNK17; i <= MOD_XENONLIGHTS; i++) {
					native::toggle_vehicle_mod(veh, i, true);
				}

				native::set_vehicle_colours(veh, 160, 160);
				native::set_vehicle_extra_colours(veh, 160, 160);
				native::set_vehicle_window_tint(veh, 5);

				color_rgba temp;
				temp.r = native::get_random_int_in_range(0, 255);
				temp.g = native::get_random_int_in_range(0, 255);
				temp.b = native::get_random_int_in_range(0, 255);

				native::set_vehicle_tyre_smoke_color(veh, temp.r, temp.g, temp.b);
				native::set_vehicle_custom_primary_colour(veh, temp.r, temp.g, temp.b);
				native::set_vehicle_custom_secondary_colour(veh, temp.r, temp.g, temp.b);

				native::set_vehicle_neon_light_enabled(veh, 0, true);
				native::set_vehicle_neon_light_enabled(veh, 1, true);
				native::set_vehicle_neon_light_enabled(veh, 2, true);
				native::set_vehicle_neon_light_enabled(veh, 3, true);
				native::set_vehicle_neon_lights_colour(veh, temp.r, temp.g, temp.b);

				native::set_vehicle_number_plate_text_index(veh, 5);
			} else {
				// Perf: brakes, engine, armor, trans, suspension, turbo
				native::set_vehicle_mod_kit(veh, 0);
				native::set_vehicle_mod(veh, MOD_BRAKES, native::get_num_vehicle_mods(veh, MOD_BRAKES) - 1, 0);
				native::set_vehicle_mod(veh, MOD_ENGINE, native::get_num_vehicle_mods(veh, MOD_ENGINE) - 1, 0);
				native::set_vehicle_mod(veh, MOD_ARMOR, native::get_num_vehicle_mods(veh, MOD_ARMOR) - 1, 0);
				native::set_vehicle_mod(veh, MOD_TRANSMISSION, native::get_num_vehicle_mods(veh, MOD_TRANSMISSION) - 1, 0);
				native::set_vehicle_mod(veh, MOD_SUSPENSION, native::get_num_vehicle_mods(veh, MOD_SUSPENSION) - 1, 0);
				native::toggle_vehicle_mod(veh, MOD_TURBO, true);
			}
		});
	}

	void low_upgrades(Vehicle vehicle, int type) {
		run_task(vehicle, [=](Vehicle veh) {
			if (type == 1) {
				native::set_vehicle_fixed(veh);
				native::set_vehicle_dirt_level(veh, 0);
				native::set_vehicle_tyres_can_burst(veh, true);
				native::set_vehicle_mod_kit(veh, 0);

				for (int i = MOD_SPOILER; i <= MOD_ARMOR; i++) {
					native::remove_vehicle_mod(veh, i);
				}

				for (int i = MOD_PLATEHOLDER; i <= MOD_LIVERY; i++) {
					native::remove_vehicle_mod(veh, i);
				}

				native::remove_vehicle_mod(veh, MOD_HORNS);
				native::remove_vehicle_mod(veh, MOD_FRONTWHEELS);

				for (int i = MOD_UNK17; i <= MOD_XENONLIGHTS; i++) {
					native::toggle_vehicle_mod(veh, i, false);
				}

				native::clear_vehicle_custom_primary_colour(veh);
				native::clear_vehicle_custom_secondary_colour(veh);
				native::set_vehicle_colours(veh, 135, 135);
				native::set_vehicle_extra_colours(veh, 135, 135);
				native::set_vehicle_window_tint(veh, 0);
				native::set_vehicle_number_plate_text_index(veh, 1);

				native::set_vehicle_neon_light_enabled(veh, 0, false);
				native::set_vehicle_neon_light_enabled(veh, 1, false);
				native::set_vehicle_neon_light_enabled(veh, 2, false);
				native::set_vehicle_neon_light_enabled(veh, 3, false);
			} else {
				native::set_vehicle_mod_kit(veh, 0);
				native::remove_vehicle_mod(veh, MOD_BRAKES);
				native::remove_vehicle_mod(veh, MOD_ENGINE);
				native::remove_vehicle_mod(veh, MOD_ARMOR);
				native::remove_vehicle_mod(veh, MOD_TRANSMISSION);
				native::remove_vehicle_mod(veh, MOD_SUSPENSION);
				native::toggle_vehicle_mod(veh, MOD_TURBO, false);
			}
		});
	}
}

void vehicle_menu::load() {
	set_name("Vehicle");
	set_parent<main_menu>();

	add_option(toggle_option("Godmode")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_godmode).add_savable(get_submenu_name_stack())
		.add_click([] { if (!m_vars.m_godmode) run_task(menu::player::get_local_player().m_vehicle, [] (Vehicle veh) { native::set_entity_invincible(veh, false); }); }));

	add_option(toggle_option("Invisibility")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_invisibility).add_savable(get_submenu_name_stack())
		.add_click([] { if (!m_vars.m_invisibility) run_task(menu::player::get_local_player().m_vehicle, [](Vehicle veh) { native::set_entity_visible(veh, true, true); }); }));

	add_option(toggle_option("Seatbelt")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_seatbelt).add_savable(get_submenu_name_stack())
		.add_click([] {
			if (!m_vars.m_seatbelt) {
				native::set_ped_can_be_knocked_off_vehicle(menu::player::get_local_player().m_ped, 0);
				native::set_ped_config_flag(menu::player::get_local_player().m_ped, 32, true);
			}
		}));

	add_option(scroll_option<int>(SCROLLSELECT, "Upgrades")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_upgrades_var, 0, NUMOF(upgrades), upgrades)
		.add_click([] { max_upgrades(menu::player::get_local_player().m_vehicle, m_vars.m_upgrades_var); }));

	add_option(scroll_option<int>(SCROLLSELECT, "Downgrades")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_downgrades_var, 0, NUMOF(upgrades), upgrades)
		.add_click([] { low_upgrades(menu::player::get_local_player().m_vehicle, m_vars.m_downgrades_var); }));

	add_option(submenu_option("Customs")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_customs_menu>()
		.add_click([] { vehicle_customs_menu::get()->update_once(); })
		.add_requirement([] { return vehicle::customs::vars::get_size() > 0; }));

	add_option(submenu_option("Health")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_health_menu>());

	add_option(submenu_option("Weapons")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_weapons_menu>());

	add_option(submenu_option("Particle FX")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_particles_menu>());

	add_option(submenu_option("Movement")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_movement_menu>());

	add_option(submenu_option("Boost")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_boost_menu>());

	add_option(submenu_option("Collision")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_collision_menu>());

	add_option(submenu_option("Gravity")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_gravity_menu>());

	add_option(submenu_option("Multipliers")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_multipliers_menu>());

	add_option(submenu_option("Modifiers")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_modifiers_menu>());

	add_option(submenu_option("Autopilot")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_autopilot_menu>());

	add_option(submenu_option("Ramps")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_ramps_menu>());

	add_option(submenu_option("Randomization")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_randomization_menu>());

	add_option(submenu_option("Seats")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_seats_menu>());

	add_option(submenu_option("Speedometer")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_speedometer_menu>());

	add_option(submenu_option("Doors")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_doors_menu>());

	add_option(submenu_option("Tire Tracks")
		.add_translate().add_hotkey()
		.add_submenu<vehicle_tyre_tracks_menu>());

	add_option(button_option("Clone")
		.add_translate().add_hotkey()
		.add_click([] { if (menu::player::get_local_player().m_in_vehicle) clone_vehicle(menu::player::get_local_player().m_vehicle); }));

	add_option(toggle_option("Burn Shell")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_burn_shell).add_savable(get_submenu_name_stack())
		.add_click([] { if (!m_vars.m_burn_shell) run_task(menu::player::get_local_player().m_vehicle, [](Vehicle veh) { native::set_entity_render_scorched(veh, false); }); }));

	add_option(scroll_option<int>(SCROLL, "Opacity")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_opacity, 0, NUMOF(global::lists::g_opacity), global::lists::g_opacity)
		.add_click([] { run_task(menu::player::get_local_player().m_vehicle, [](Vehicle veh) { native::set_entity_alpha(veh, global::lists::g_opacity[m_vars.m_opacity].m_result, false); }); }));

	add_option(button_option("Delete")
		.add_translate().add_hotkey()
		.add_click([] {
			if (menu::player::get_local_player().m_in_vehicle) {
				run_task(menu::player::get_local_player().m_vehicle, [](Vehicle veh) {
					native::set_entity_as_mission_entity(veh, true, true);
					native::delete_entity(&veh);
				});
			}
		}));
}

void vehicle_menu::update() {
	std::vector<std::shared_ptr<base_option>> options = menu::submenu::handler::get_current()->get_options();
	int count = (int)std::count_if(begin(options), end(options), [](std::shared_ptr<base_option> option) { return option->is_visible(); });

	if (menu::base::get_current_option() > count) {
		menu::base::set_current_option(count - 1);
	}
}

void vehicle_menu::update_once() {}

void vehicle_menu::feature_update() {
	if (menu::player::get_local_player().m_in_vehicle) {
		if (m_vars.m_godmode) {
			native::set_entity_invincible(menu::player::get_local_player().m_vehicle, true);
		}

		if (m_vars.m_invisibility) {
			native::set_entity_visible(menu::player::get_local_player().m_vehicle, false, true);
		}

		if (m_vars.m_seatbelt) {
			native::set_ped_can_be_knocked_off_vehicle(menu::player::get_local_player().m_ped, 1);
			native::set_ped_config_flag(menu::player::get_local_player().m_ped, 32, false);
		}

		if (m_vars.m_burn_shell) {
			native::set_entity_render_scorched(menu::player::get_local_player().m_vehicle, true);
		}
	}
}

vehicle_menu* g_instance;
vehicle_menu* vehicle_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}