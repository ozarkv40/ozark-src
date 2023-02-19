#include "vehicle_randomization.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle.h"
#include "global/lists.h"
#include "menu/base/util/timers.h"
#include "menu/base/util/instructionals.h"
#include "../helper/helper_rainbow.h"

using namespace vehicle::randomization::vars;

namespace vehicle::randomization::vars {
	variables m_vars;
}

void vehicle_randomization_menu::load() {
	set_name("Randomization");
	set_parent<vehicle_menu>();

	set_default_instructionals(false);

	add_option(toggle_option("Rainbow Primary Paint")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_rainbow_primary)
		.add_click([] {
			m_vars.m_rainbow_primary_run.toggle(m_vars.m_rainbow_primary);
			if (m_vars.m_rainbow_primary) {
				if (menu::player::get_local_player().m_in_vehicle) {
					native::get_vehicle_custom_primary_colour(menu::player::get_local_player().m_vehicle, &m_vars.m_rainbow_primary_color.r, &m_vars.m_rainbow_primary_color.g, &m_vars.m_rainbow_primary_color.b);
				}

				m_vars.m_rainbow_primary_run.add(&m_vars.m_rainbow_primary_color);
			} else {
				m_vars.m_rainbow_primary_run.remove(&m_vars.m_rainbow_primary_color);
			}
		}).add_hover([] { helper::rainbow::vars::m_vars.m_rainbow = &m_vars.m_rainbow_primary_run; }).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Rainbow Secondary Paint")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_rainbow_secondary)
		.add_click([] {
			m_vars.m_rainbow_secondary_run.toggle(m_vars.m_rainbow_secondary);
			if (m_vars.m_rainbow_secondary) {
				if (menu::player::get_local_player().m_in_vehicle) {
					native::get_vehicle_custom_secondary_colour(menu::player::get_local_player().m_vehicle, &m_vars.m_rainbow_secondary_color.r, &m_vars.m_rainbow_secondary_color.g, &m_vars.m_rainbow_secondary_color.b);
				}

				m_vars.m_rainbow_secondary_run.add(&m_vars.m_rainbow_secondary_color);
			} else {
				m_vars.m_rainbow_secondary_run.remove(&m_vars.m_rainbow_secondary_color);
			}
		}).add_hover([] { helper::rainbow::vars::m_vars.m_rainbow = &m_vars.m_rainbow_secondary_run; }).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Rainbow Tire Smoke")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_rainbow_tire_smoke)
		.add_click([] {
			m_vars.m_rainbow_tire_smoke_run.toggle(m_vars.m_rainbow_tire_smoke);
			if (m_vars.m_rainbow_tire_smoke) {
				if (menu::player::get_local_player().m_in_vehicle) {
					native::get_vehicle_tyre_smoke_color(menu::player::get_local_player().m_vehicle, &m_vars.m_rainbow_tire_smoke_color.r, &m_vars.m_rainbow_tire_smoke_color.g, &m_vars.m_rainbow_tire_smoke_color.b);
				}

				m_vars.m_rainbow_tire_smoke_run.add(&m_vars.m_rainbow_tire_smoke_color);
			} else {
				m_vars.m_rainbow_tire_smoke_run.remove(&m_vars.m_rainbow_tire_smoke_color);
			}
		}).add_hover([] { helper::rainbow::vars::m_vars.m_rainbow = &m_vars.m_rainbow_tire_smoke_run; }).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Rainbow Neons")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_rainbow_neons)
		.add_click([] {
			m_vars.m_rainbow_neons_run.toggle(m_vars.m_rainbow_neons);
			if (m_vars.m_rainbow_neons) {
				if (menu::player::get_local_player().m_in_vehicle) {
					native::get_vehicle_neon_lights_colour(menu::player::get_local_player().m_vehicle, &m_vars.m_rainbow_tire_smoke_color.r, &m_vars.m_rainbow_tire_smoke_color.g, &m_vars.m_rainbow_tire_smoke_color.b);
				}

				m_vars.m_rainbow_neons_run.add(&m_vars.m_rainbow_neons_color);
			} else {
				m_vars.m_rainbow_neons_run.remove(&m_vars.m_rainbow_neons_color);
			}
		}).add_hover([] { helper::rainbow::vars::m_vars.m_rainbow = &m_vars.m_rainbow_neons_run; }).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Random Upgrades")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_random_upgrades).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Random Acrobatics")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_random_acrobatics).add_savable(get_submenu_name_stack()));
}

void vehicle_randomization_menu::update() {
	if (menu::base::get_current_option() > 3) {
		instructionals::standard(false, false, true);
	} else {
		instructionals::rainbow(false, false, true);

		if (menu::input::is_just_pressed(false, ControlFrontendX)) {
			helper_rainbow_menu::get()->set_parent<vehicle_randomization_menu>();
			menu::submenu::handler::set_submenu(helper_rainbow_menu::get());
		}
	}
}

void vehicle_randomization_menu::update_once() {}

void vehicle_randomization_menu::feature_update() {
	if (menu::player::get_local_player().m_in_vehicle) {
		if (m_vars.m_rainbow_neons) {
			m_vars.m_rainbow_neons_run.run();

			for (int i = 0; i < 4; i++) {
				native::set_vehicle_neon_light_enabled(menu::player::get_local_player().m_vehicle, i, true);
			}

			native::set_vehicle_neon_lights_colour(menu::player::get_local_player().m_vehicle, m_vars.m_rainbow_neons_color.r, m_vars.m_rainbow_neons_color.g, m_vars.m_rainbow_neons_color.b);
		}

		if (m_vars.m_rainbow_primary) {
			m_vars.m_rainbow_primary_run.run();

			native::set_vehicle_custom_primary_colour(menu::player::get_local_player().m_vehicle, m_vars.m_rainbow_primary_color.r, m_vars.m_rainbow_primary_color.g, m_vars.m_rainbow_primary_color.b);
		}

		if (m_vars.m_rainbow_secondary) {
			m_vars.m_rainbow_secondary_run.run();

			native::set_vehicle_custom_secondary_colour(menu::player::get_local_player().m_vehicle, m_vars.m_rainbow_secondary_color.r, m_vars.m_rainbow_secondary_color.g, m_vars.m_rainbow_secondary_color.b);
		}

		if (m_vars.m_rainbow_tire_smoke) {
			m_vars.m_rainbow_tire_smoke_run.run();

			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::toggle_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TIRESMOKE, true);
			native::set_vehicle_tyre_smoke_color(menu::player::get_local_player().m_vehicle, m_vars.m_rainbow_tire_smoke_color.r, m_vars.m_rainbow_tire_smoke_color.g, m_vars.m_rainbow_tire_smoke_color.b);
		}

		if (m_vars.m_random_upgrades) {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			int class_ = native::get_random_int_in_range(MOD_SPOILER - 1, MOD_LIVERY - 1);
			int max = native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, class_);
			int mod = native::get_random_int_in_range(-2, max + 1);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, class_, mod, 0);
		}

		if (m_vars.m_random_acrobatics) {
			static int timer = 0;
			menu::timers::run_timed(&timer, 5000, [] {
				vehicle::vars::run_task(menu::player::get_local_player().m_vehicle, [] (Vehicle veh) {
					std::pair<math::vector3_<float>, math::vector3_<float>> data = global::lists::g_acrobatics[native::get_random_int_in_range(0, 9)].m_result;
					native::apply_force_to_entity(veh, 1, data.first.x, data.first.y, data.first.z, data.second.x, data.second.y, data.second.z, 0, true, true, true, false, true);

				});
			});
		}
	}
}

vehicle_randomization_menu* g_instance;
vehicle_randomization_menu* vehicle_randomization_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_randomization_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}