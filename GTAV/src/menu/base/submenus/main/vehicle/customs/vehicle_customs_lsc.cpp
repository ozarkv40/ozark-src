#include "vehicle_customs_lsc.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_customs.h"
#include "vehicle_customs_bumpers.h"
#include "vehicle_customs_fender.h"
#include "vehicle_customs_horn.h"
#include "vehicle_customs_lights.h"
#include "lights/vehicle_customs_neon.h"

using namespace vehicle::customs::lsc::vars;

namespace vehicle::customs::lsc::vars {
	variables m_vars;

	scroll_struct<int> armor[] = {
		{ localization("Armor Upgrade 20%", true), 0, },
		{ localization("Armor Upgrade 40%", true), 1, },
		{ localization("Armor Upgrade 60%", true), 2, },
		{ localization("Armor Upgrade 80%", true), 3, },
		{ localization("Armor Upgrade 100%", true), 4 },
	};

	scroll_struct<int> suspension[] = {
		{ localization("Lowered Suspension", true), 0, },
		{ localization("Street Suspension", true), 1, },
		{ localization("Sport Suspension", true), 2, },
		{ localization("Competition Suspension", true), 3, },
		{ localization("Race Suspension", true), 4, },
	};

	scroll_struct<int> transmission[] = {
		{ localization("Street Transmission", true), 0, },
		{ localization("Sports Transmission", true), 1, },
		{ localization("Race Transmission", true), 2, },
	};

	scroll_struct<int> brakes[] = {
		{ localization("Street Brakes", true), 0, },
		{ localization("Sport Brakes", true), 1, },
		{ localization("Race Brakes", true), 2, },
		{ localization("Open Wheel Brakes", true), 3 },
	};

	scroll_struct<std::vector<int>> neons[] = {
		{ localization("Front", true), { 2 }, },
		{ localization("Back", true), { 3 }, },
		{ localization("Sides", true), { 0, 1 }, },
		{ localization("Front and Back", true), { 2, 3 }, },
		{ localization("Front and Sides", true), { 2, 0, 1 }, },
		{ localization("Back and Sides", true), { 3, 0, 1 }, },
		{ localization("Front, Back and Sides", true), { 0, 1, 2, 3 } },
	};

	scroll_struct<int> standard_horns[] = {
		{ localization("Stock Horn", true), -1, },
		{ localization("Truck Horn", true), 0, },
		{ localization("Cop Horn", true), 1, },
		{ localization("Clown Horn", true), 2, },
	};

	scroll_struct<int> musical_horns[] = {
		{ localization("Star Spangled Banner 1", true), 28, },
		{ localization("Star Spangled Banner 2", true), 29, },
		{ localization("Star Spangled Banner 3", true), 30, },
		{ localization("Star Spangled Banner 4", true), 31, },
		{ localization("Jazz Horn 1", true), 24, },
		{ localization("Jazz Horn 2", true), 25, },
		{ localization("Jazz Horn 3", true), 26, },
		{ localization("Scale - Do", true), 16, },
		{ localization("Scale - Re", true), 17, },
		{ localization("Scale - Mi", true), 18, },
		{ localization("Scale - Fa", true), 19, },
		{ localization("Scale - Sol", true), 20, },
		{ localization("Scale - La", true), 21, },
		{ localization("Scale - Ti", true), 22, },
		{ localization("Scale - Do (high)", true), 23, },
		{ localization("Classical Horn 1", true), 9, },
		{ localization("Classical Horn 2", true), 10, },
		{ localization("Classical Horn 3", true), 11, },
		{ localization("Classical Horn 4", true), 12, },
		{ localization("Classical Horn 5", true), 13, },
		{ localization("Classical Horn 6", true), 14, },
		{ localization("Classical Horn 7", true), 15, },
		{ localization("Classical Horn 8", true), 32, },
		{ localization("Musical Horn 1", true), 3, },
		{ localization("Musical Horn 2", true), 4, },
		{ localization("Musical Horn 3", true), 5, },
		{ localization("Musical Horn 4", true), 6, },
		{ localization("Musical Horn 5", true), 7, },
		{ localization("Sad Trombone", true), 8 },
	};

	scroll_struct<int> loop_horns[] = {
		{ localization("Jazz Horn Loop", true), 27, },
		{ localization("San Andreas Loop", true), 42, },
		{ localization("Liberty City Loop", true), 44, },
		{ localization("Halloween Loop 1", true), 38, },
		{ localization("Halloween Loop 2", true), 40, },
		{ localization("Festive Loop 1", true), 46, },
		{ localization("Festive Loop 2", true), 48, },
		{ localization("Festive Loop 3", true), 50, },
		{ localization("Air Horn 1", true), 52, },
		{ localization("Air Horn 2", true), 54, },
		{ localization("Air Horn 3", true), 56, },
		{ localization("Classical Horn Loop 1", true), 33, },
		{ localization("Classical Horn Loop 2", true), 34 },
	};

	scroll_struct<int> xenon_colors[] = {
		{ localization("Default", true), -1 },
		{ localization("White", true), 0 },
		{ localization("Blue", true), 1 },
		{ localization("Electric Blue", true), 2 },
		{ localization("Mint Green", true), 3 },
		{ localization("Lime Green", true), 4 },
		{ localization("Yellow", true), 5 },
		{ localization("Golden Shower", true), 6 },
		{ localization("Orange", true), 7 },
		{ localization("Red", true), 8 },
		{ localization("Pony Pink", true), 9 },
		{ localization("Hot PInk", true), 10 },
		{ localization("Purple", true), 11 },
		{ localization("Blacklight", true), 12 },
	};

	scroll_struct<int> window_tints[] = {
		{ localization("Light Smoke", true), 4 },
		{ localization("Dark Smoke", true), 3 },
		{ localization("Limo", true), 2 },
		{ localization("Pure Black", true), 5 },
		{ localization("Green", true), 6 }
	};

	scroll_struct<int> plates[] = {
		{ localization("Blue on White 1", true), 0 },
		{ localization("Blue on White 2", true), 3 },
		{ localization("Blue on White 3", true), 4 },
		{ localization("Yellow on Blue", true), 2 },
		{ localization("Yellow on Black", true), 1 },
		{ localization("Yankton", true), 5 },
	};

	std::unordered_map<eVehicleModTypes, std::string> stock_mod_names = {
		{ MOD_EXHAUST, "Stock" },
		{ MOD_HOOD, "Stock" },
		{ MOD_SPOILER, "None" },
		{ MOD_GRILLE, "Stock" },
		{ MOD_FENDER, "Stock" },
		{ MOD_ROOF, "Stock" },
		{ MOD_CHASSIS, "None" },
		{ MOD_DASHBOARD, "None" },
		{ MOD_DIAL, "Stock" },
		{ MOD_DOOR_SPEAKER, "None" },
		{ MOD_SEATS, "None" },
		{ MOD_STEERINGWHEEL, "Stock" },
		{ MOD_LIVERY, "None" },
	};
}

void vehicle_customs_lsc_menu::load() {
	set_name("Los Santos Customs");
	set_parent<vehicle_customs_menu>();

	add_string("None");
	add_string("Stock EMS");
	add_string("EMS Upgrade, Level 1");
	add_string("EMS Upgrade, Level 2");
	add_string("EMS Upgrade, Level 3");
	add_string("EMS Upgrade, Level 4");
	add_string("EMS Upgrade, Level 5");
	add_string("Stock Suspension");
	add_string("Stock Transmission");
	add_string("Stock Brakes");
	add_string("Turbo Tuning");
	add_string("Stock Skirts");
	add_string("Stock Lights");
	add_string("Xenon Lights");
	add_string("Xenon Color");
	add_string("Stock Front Bumper");
	add_string("Stock Rear Bumper");
	add_string("Stock Left Fender");
	add_string("Stock Right Fender");
	add_string("Stock");
	add_string("Los Santos Customs");
	add_string("Benny's");
}

void vehicle_customs_lsc_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	vehicle::customs::vars::scripts::draw_vehicle_stats(menu::player::get_local_player().m_vehicle);
	if (menu::base::get_scroll_offset() < menu::submenu::handler::get_total_options() - menu::base::get_max_options() && menu::base::get_current_option() - menu::base::get_scroll_offset() >= menu::base::get_max_options()) menu::base::set_scroll_offset(menu::base::get_scroll_offset() + 1);
}

void vehicle_customs_lsc_menu::update_once() {
	if (vehicle::customs::vars::m_vars.m_type == 0) {
		set_name(get_string("Los Santos Customs"), false, false);
	} else set_name(get_string("Benny's"), false, false);

	set_parent<vehicle_customs_menu>();
	clear_options(0);

	vehicle::customs::vars::m_vars.m_update_cache = true;
	// VehicleEditorBennysInteriorMenuVars::m_vars.m_update_cache = true;
	m_vars.m_context.reset();
	m_vars.m_context.m_selected = 0;

	if (m_vars.m_mod_type == MOD_ARMOR) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("None"))
			.add_radio(m_vars.m_context)
			.add_click([] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::vars::m_vars.m_cached_stats.m_armor = -1;
			})
			.add_hover([] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ARMOR, -1, false);
			})));

		for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_ARMOR); i++) {
			temp_options.push_back(add_option(radio_option(armor[i].m_name.get())
				.add_radio(m_vars.m_context)
				.add_click([=] {
					vehicle::customs::vars::update_caches();
					vehicle::customs::vars::m_vars.m_cached_stats.m_armor = armor[i].m_result;
				})
				.add_hover([=] {
					native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
					native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ARMOR, armor[i].m_result, false);
				})));
		}

		if (vehicle::customs::vars::m_vars.m_cached_stats.m_armor != -1) {
			if (vehicle::customs::vars::m_vars.m_cached_stats.m_armor + 1 >= temp_options.size()) return;
			temp_options[vehicle::customs::vars::m_vars.m_cached_stats.m_armor + 1]->update_selected();
			menu::base::set_current_option(vehicle::customs::vars::m_vars.m_cached_stats.m_armor + 1);
		}

		return;
	}

	if (m_vars.m_mod_type == MOD_ENGINE) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock EMS"))
			.add_radio(m_vars.m_context)
			.add_click([] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::vars::m_vars.m_cached_stats.m_engine = -1;
			})
			.add_hover([] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ENGINE, -1, false);
			})));

		for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_ENGINE); i++) {
			temp_options.push_back(add_option(radio_option(get_string(util::va::va("EMS Upgrade, Level %i", i + 1)))
				.add_radio(m_vars.m_context)
				.add_click([=] {
					vehicle::customs::vars::update_caches();
					vehicle::customs::vars::m_vars.m_cached_stats.m_engine = i;
				})
				.add_hover([=] {
					native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
					native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ENGINE, i, false);
				})));
		}

		if (vehicle::customs::vars::m_vars.m_cached_stats.m_engine != -1) {
			if (vehicle::customs::vars::m_vars.m_cached_stats.m_engine + 1 >= temp_options.size()) return;
			temp_options[vehicle::customs::vars::m_vars.m_cached_stats.m_engine + 1]->update_selected();
			menu::base::set_current_option(vehicle::customs::vars::m_vars.m_cached_stats.m_engine + 1);
		}

		return;
	}

	if (m_vars.m_mod_type == MOD_SUSPENSION) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Suspension"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::vars::m_vars.m_cached_stats.m_suspension = -1;
		})
			.add_hover([] {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SUSPENSION, -1, false);
		})));

		for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_SUSPENSION); i++) {
			temp_options.push_back(add_option(radio_option(suspension[i].m_name.get())
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::vars::m_vars.m_cached_stats.m_suspension = suspension[i].m_result;
			})
				.add_hover([=] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SUSPENSION, suspension[i].m_result, false);
			})));
		}

		if (vehicle::customs::vars::m_vars.m_cached_stats.m_suspension != -1) {
			if (vehicle::customs::vars::m_vars.m_cached_stats.m_suspension + 1 >= temp_options.size()) return;
			temp_options[vehicle::customs::vars::m_vars.m_cached_stats.m_suspension + 1]->update_selected();
			menu::base::set_current_option(vehicle::customs::vars::m_vars.m_cached_stats.m_suspension + 1);
		}

		return;
	}

	if (m_vars.m_mod_type == MOD_TRANSMISSION) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Transmission"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::vars::m_vars.m_cached_stats.m_transmission = -1;
		})
			.add_hover([] {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TRANSMISSION, -1, false);
		})));

		for (int i = 0; i < NUMOF(transmission); i++) {
			temp_options.push_back(add_option(radio_option(transmission[i].m_name.get())
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::vars::m_vars.m_cached_stats.m_transmission = transmission[i].m_result;
			})
				.add_hover([=] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TRANSMISSION, transmission[i].m_result, false);
			})));
		}

		if (vehicle::customs::vars::m_vars.m_cached_stats.m_transmission != -1) {
			if (vehicle::customs::vars::m_vars.m_cached_stats.m_transmission + 1 >= temp_options.size()) return;
			temp_options[vehicle::customs::vars::m_vars.m_cached_stats.m_transmission + 1]->update_selected();
			menu::base::set_current_option(vehicle::customs::vars::m_vars.m_cached_stats.m_transmission + 1);
		}

		return;
	}

	if (m_vars.m_mod_type == MOD_BRAKES) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Brakes"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::vars::m_vars.m_cached_stats.m_brakes = -1;
		})
			.add_hover([] {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_BRAKES, -1, false);
		})));

		for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_BRAKES); i++) {
			temp_options.push_back(add_option(radio_option(brakes[i].m_name.get())
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::vars::m_vars.m_cached_stats.m_brakes = brakes[i].m_result;
			})
				.add_hover([=] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_BRAKES, brakes[i].m_result, false);
			})));
		}

		if (vehicle::customs::vars::m_vars.m_cached_stats.m_brakes != -1) {
			if (vehicle::customs::vars::m_vars.m_cached_stats.m_brakes + 1 >= temp_options.size()) return;
			temp_options[vehicle::customs::vars::m_vars.m_cached_stats.m_brakes + 1]->update_selected();
			menu::base::set_current_option(vehicle::customs::vars::m_vars.m_cached_stats.m_brakes + 1);
		}

		return;
	}

	if (m_vars.m_mod_type == MOD_TURBO) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("None"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::vars::m_vars.m_cached_stats.m_turbo = 0;
		})
			.add_hover([] {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::toggle_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TURBO, false);
		})));

		temp_options.push_back(add_option(radio_option(get_string("Turbo Tuning"))
			.add_radio(m_vars.m_context)
			.add_click([=] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::vars::m_vars.m_cached_stats.m_turbo = 1;
		})
			.add_hover([=] {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::toggle_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TURBO, true);
		})));

		if (vehicle::customs::vars::m_vars.m_cached_stats.m_turbo) {
			temp_options[1]->update_selected();
			menu::base::set_current_option(1);
		}

		return;
	}

	if (m_vars.m_mod_type == MOD_SIDESKIRT) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Skirts"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::vars::m_vars.m_cached_stats.m_skirts = -1;
		})
			.add_hover([] {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SIDESKIRT, -1, false);
		})));

		for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_SIDESKIRT); i++) {
			const char* label = native::get_label_text(native::get_mod_text_label(menu::player::get_local_player().m_vehicle, MOD_SIDESKIRT, i));
			if (!strcmp(label, "NULL")) label = "Custom Skirts";

			temp_options.push_back(add_option(radio_option(label)
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::vars::m_vars.m_cached_stats.m_skirts = i;
			})
				.add_hover([=] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SIDESKIRT, i, false);
			})));
		}

		if (vehicle::customs::vars::m_vars.m_cached_stats.m_skirts != -1) {
			if (vehicle::customs::vars::m_vars.m_cached_stats.m_skirts + 1 >= temp_options.size()) return;
			temp_options[vehicle::customs::vars::m_vars.m_cached_stats.m_skirts + 1]->update_selected();
			menu::base::set_current_option(vehicle::customs::vars::m_vars.m_cached_stats.m_skirts + 1);
		}

		return;
	}

	if (m_vars.m_mod_type == MOD_XENONLIGHTS) {
		set_parent<vehicle_customs_lights_menu>();
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Lights"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::vars::m_vars.m_cached_stats.m_lights = 0;
		})
			.add_hover([] {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::toggle_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_XENONLIGHTS, false);
		})));

		temp_options.push_back(add_option(radio_option(get_string("Xenon Lights"))
			.add_radio(m_vars.m_context)
			.add_click([=] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::vars::m_vars.m_cached_stats.m_lights = 1;
		})
			.add_hover([=] {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::toggle_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_XENONLIGHTS, true);
		})));

		add_option(scroll_option<int>(SCROLL, get_string("Xenon Color"))
			.add_scroll(m_vars.m_xenon_color, 0, NUMOF(xenon_colors), xenon_colors)
			.add_click([] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::vars::m_vars.m_cached_stats.m_xenon_color = xenon_colors[m_vars.m_xenon_color].m_result;
			})
			.add_hover([] {
				native::set_vehicle_xenon_lights_colour(menu::player::get_local_player().m_vehicle, xenon_colors[m_vars.m_xenon_color].m_result);
			}).add_requirement([] { return vehicle::customs::vars::m_vars.m_cached_stats.m_lights == 1; }));

		if (vehicle::customs::vars::m_vars.m_cached_stats.m_lights) {
			temp_options[1]->update_selected();
			menu::base::set_current_option(1);
		}

		for (int i = 0; i < NUMOF(xenon_colors); i++) {
			if (vehicle::customs::vars::m_vars.m_cached_stats.m_xenon_color == xenon_colors[i].m_result) {
				m_vars.m_xenon_color = i;
				break;
			}
		}

		return;
	}

	if (m_vars.m_mod_type == MOD_NEON) {
		set_parent<vehicle_customs_neon_menu>();
		std::vector<std::shared_ptr<radio_option>> temp_options;

		auto disable_neons = [] {
			for (int i = 0; i < 4; i++) {
				native::set_vehicle_neon_light_enabled(menu::player::get_local_player().m_vehicle, i, false);
			}
		};

		auto set_neons = [](std::vector<int> Neons) {
			for (auto& Neon : Neons) {
				native::set_vehicle_neon_light_enabled(menu::player::get_local_player().m_vehicle, Neon, true);
			}
		};

		temp_options.push_back(add_option(radio_option(get_string("None"))
			.add_radio(m_vars.m_context)
			.add_click([=] {
				vehicle::customs::vars::update_caches();
				// set neons enabled in vars
				for (int i = 0; i < 4; i++) {
					vehicle::customs::vars::m_vars.m_cached_stats.m_neon[i] = false;
				}
			})
			.add_hover([=] {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			// set neons enabled native
			disable_neons();
		})));

		for (int i = 0; i < NUMOF(neons); i++) {
			temp_options.push_back(add_option(radio_option(neons[i].m_name.get())
				.add_radio(m_vars.m_context)
				.add_click([=] {
					vehicle::customs::vars::update_caches();

					memset(&vehicle::customs::vars::m_vars.m_cached_stats.m_neon, 0, sizeof(vehicle::customs::vars::m_vars.m_cached_stats.m_neon));
					for (auto neon : neons[i].m_result) {
						vehicle::customs::vars::m_vars.m_cached_stats.m_neon[neon] = true;
					}
				})
				.add_hover([=] {
					native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
					disable_neons();
					set_neons(neons[i].m_result);
				})));
		}

		bool Left = vehicle::customs::vars::m_vars.m_cached_stats.m_neon[0];
		bool Right = vehicle::customs::vars::m_vars.m_cached_stats.m_neon[1];
		bool Front = vehicle::customs::vars::m_vars.m_cached_stats.m_neon[2];
		bool Back = vehicle::customs::vars::m_vars.m_cached_stats.m_neon[3];

		if (Front && (!Left && !Right && !Back)) {
			temp_options[1]->update_selected();
			menu::base::set_current_option(1);
		} else if (Back && (!Left && !Right && !Front)) {
			temp_options[2]->update_selected();
			menu::base::set_current_option(2);
		} else if ((Left && Right) && (!Front && !Back)) {
			temp_options[3]->update_selected();
			menu::base::set_current_option(3);
		} else if (Front && Back && (!Left && !Right)) {
			temp_options[4]->update_selected();
			menu::base::set_current_option(4);
		} else if (Front && Left & Right && (!Back)) {
			temp_options[5]->update_selected();
			menu::base::set_current_option(5);
		} else if (Back && Left && Right && (!Front)) {
			temp_options[6]->update_selected();
			menu::base::set_current_option(6);
		} else if (Front && Back && Left && Right) {
			temp_options[7]->update_selected();
			menu::base::set_current_option(7);
		}

		return;
	}

	if (m_vars.m_mod_type == MOD_HORN_STANDARD) {
		set_parent<vehicle_customs_horn_menu>();
		std::vector<std::shared_ptr<radio_option>> temp_options;

		int selected_index = 99;
		int current_mod = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HORNS);

		for (int i = 0; i < NUMOF(standard_horns); i++) {
			auto horn = standard_horns[i];
			temp_options.push_back(add_option(radio_option(horn.m_name.get())
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::vars::m_vars.m_cached_stats.m_horn = horn.m_result;
			})
				.add_hover([=] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HORNS, horn.m_result, false);
			})));

			if (horn.m_result == current_mod) {
				selected_index = i;
			}
		}

		if (selected_index != 0) {
			if (selected_index != 99) {
				temp_options[selected_index]->update_selected();
				menu::base::set_current_option(selected_index);
			} else {
				m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
				m_vars.m_context.m_selected = 99;
				m_vars.m_context.m_toggles[99] = true;
			}
		}

		return;
	}

	if (m_vars.m_mod_type == MOD_HORN_MUSICAL) {
		set_parent<vehicle_customs_horn_menu>();
		std::vector<std::shared_ptr<radio_option>> temp_options;

		int selected_index = 99;
		int current_mod = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HORNS);

		for (int i = 0; i < NUMOF(musical_horns); i++) {
			auto horn = musical_horns[i];
			temp_options.push_back(add_option(radio_option(horn.m_name.get())
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::vars::m_vars.m_cached_stats.m_horn = horn.m_result;
			})
				.add_hover([=] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HORNS, horn.m_result, false);
			})));

			if (horn.m_result == current_mod) {
				selected_index = i;
			}
		}

		if (selected_index != 0) {
			if (selected_index != 99) {
				temp_options[selected_index]->update_selected();
				menu::base::set_current_option(selected_index);
			} else {
				m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
				m_vars.m_context.m_selected = 99;
				m_vars.m_context.m_toggles[99] = true;
			}
		}

		return;
	}

	if (m_vars.m_mod_type == MOD_HORN_LOOP) {
		set_parent<vehicle_customs_horn_menu>();
		std::vector<std::shared_ptr<radio_option>> temp_options;

		int selected_index = 99;
		int current_mod = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HORNS);

		for (int i = 0; i < NUMOF(loop_horns); i++) {
			auto horn = loop_horns[i];
			temp_options.push_back(add_option(radio_option(horn.m_name.get())
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::vars::m_vars.m_cached_stats.m_horn = horn.m_result;
			})
				.add_hover([=] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HORNS, horn.m_result, false);
			})));

			if (horn.m_result == current_mod) {
				selected_index = i;
			}
		}

		if (selected_index != 0) {
			if (selected_index != 99) {
				temp_options[selected_index]->update_selected();
				menu::base::set_current_option(selected_index);
			} else {
				m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
				m_vars.m_context.m_selected = 99;
				m_vars.m_context.m_toggles[99] = true;
			}
		}

		return;
	}

	if (m_vars.m_mod_type == MOD_FRONTBUMPER) {
		set_parent<vehicle_customs_bumper_menu>();
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Front Bumper"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::vars::m_vars.m_cached_stats.m_front_bumper = -1;
		})
			.add_hover([] {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTBUMPER, -1, false);
		})));

		for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FRONTBUMPER); i++) {
			temp_options.push_back(add_option(radio_option(native::get_label_text(native::get_mod_text_label(menu::player::get_local_player().m_vehicle, MOD_FRONTBUMPER, i)))
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::vars::m_vars.m_cached_stats.m_front_bumper = i;
			})
				.add_hover([=] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTBUMPER, i, false);
			})));
		}

		if (vehicle::customs::vars::m_vars.m_cached_stats.m_front_bumper != -1) {
			if (vehicle::customs::vars::m_vars.m_cached_stats.m_front_bumper + 1 >= temp_options.size()) return;
			temp_options[vehicle::customs::vars::m_vars.m_cached_stats.m_front_bumper + 1]->update_selected();
			menu::base::set_current_option(vehicle::customs::vars::m_vars.m_cached_stats.m_front_bumper + 1);
		}

		return;
	}

	if (m_vars.m_mod_type == MOD_REARBUMPER) {
		set_parent<vehicle_customs_bumper_menu>();
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Rear Bumper"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::vars::m_vars.m_cached_stats.m_rear_bumper = -1;
		})
			.add_hover([] {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_REARBUMPER, -1, false);
		})));

		for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_REARBUMPER); i++) {
			temp_options.push_back(add_option(radio_option(native::get_label_text(native::get_mod_text_label(menu::player::get_local_player().m_vehicle, MOD_REARBUMPER, i)))
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::vars::m_vars.m_cached_stats.m_rear_bumper = i;
			})
				.add_hover([=] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_REARBUMPER, i, false);
			})));
		}

		if (vehicle::customs::vars::m_vars.m_cached_stats.m_rear_bumper != -1) {
			if (vehicle::customs::vars::m_vars.m_cached_stats.m_rear_bumper + 1 >= temp_options.size()) return;
			temp_options[vehicle::customs::vars::m_vars.m_cached_stats.m_rear_bumper + 1]->update_selected();
			menu::base::set_current_option(vehicle::customs::vars::m_vars.m_cached_stats.m_rear_bumper + 1);
		}

		return;
	}

	if (m_vars.m_mod_type == MOD_FENDER) {
		set_parent<vehicle_customs_fender_menu>();
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Left Fender"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::vars::m_vars.m_cached_stats.m_left_fender = -1;
		})
			.add_hover([] {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FENDER, -1, false);
		})));

		for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FENDER); i++) {
			temp_options.push_back(add_option(radio_option(native::get_label_text(native::get_mod_text_label(menu::player::get_local_player().m_vehicle, MOD_FENDER, i)))
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::vars::m_vars.m_cached_stats.m_left_fender = i;
			})
				.add_hover([=] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FENDER, i, false);
			})));
		}

		if (vehicle::customs::vars::m_vars.m_cached_stats.m_left_fender != -1) {
			if (vehicle::customs::vars::m_vars.m_cached_stats.m_left_fender + 1 >= temp_options.size()) return;
			temp_options[vehicle::customs::vars::m_vars.m_cached_stats.m_left_fender + 1]->update_selected();
			menu::base::set_current_option(vehicle::customs::vars::m_vars.m_cached_stats.m_left_fender + 1);
		}

		return;
	}

	if (m_vars.m_mod_type == MOD_RIGHTFENDER) {
		set_parent<vehicle_customs_fender_menu>();
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("Stock Right Fender"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::vars::m_vars.m_cached_stats.m_right_fender = -1;
		})
			.add_hover([] {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_RIGHTFENDER, -1, false);
		})));

		for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_RIGHTFENDER); i++) {
			temp_options.push_back(add_option(radio_option(native::get_label_text(native::get_mod_text_label(menu::player::get_local_player().m_vehicle, MOD_RIGHTFENDER, i)))
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::vars::m_vars.m_cached_stats.m_right_fender = i;
			})
				.add_hover([=] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_RIGHTFENDER, i, false);
			})));
		}

		if (vehicle::customs::vars::m_vars.m_cached_stats.m_right_fender != -1) {
			if (vehicle::customs::vars::m_vars.m_cached_stats.m_right_fender + 1 >= temp_options.size()) return;
			temp_options[vehicle::customs::vars::m_vars.m_cached_stats.m_right_fender + 1]->update_selected();
			menu::base::set_current_option(vehicle::customs::vars::m_vars.m_cached_stats.m_right_fender + 1);
		}

		return;
	}

	if (m_vars.m_mod_type == MOD_WINDOWS_CUSTOM) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		temp_options.push_back(add_option(radio_option(get_string("None"))
			.add_radio(m_vars.m_context)
			.add_click([] {
			vehicle::customs::vars::update_caches();
			vehicle::customs::vars::m_vars.m_cached_stats.m_window_tint = 0;
		})
			.add_hover([] {
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_window_tint(menu::player::get_local_player().m_vehicle, 0);
		})));

		for (int i = 0; i < NUMOF(window_tints); i++) {
			temp_options.push_back(add_option(radio_option(window_tints[i].m_name.get())
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::vars::m_vars.m_cached_stats.m_window_tint = window_tints[i].m_result;
			})
				.add_hover([=] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_window_tint(menu::player::get_local_player().m_vehicle, window_tints[i].m_result);
			})));
		}

		if (vehicle::customs::vars::m_vars.m_cached_stats.m_window_tint > 0) {
			if (vehicle::customs::vars::m_vars.m_cached_stats.m_window_tint >= temp_options.size()) return;
			temp_options[vehicle::customs::vars::m_vars.m_cached_stats.m_window_tint]->update_selected(); // crash here
			menu::base::set_current_option(vehicle::customs::vars::m_vars.m_cached_stats.m_window_tint);
		}

		return;
	}

	if (m_vars.m_mod_type == MOD_PLATES) {
		std::vector<std::shared_ptr<radio_option>> temp_options;

		add_option(button_option("Input Custom Plate")
			.add_keyboard("Enter plate text", 8, [](button_option* option, const char* result) {
				native::set_vehicle_number_plate_text(menu::player::get_local_player().m_vehicle, result);
			}));

		for (int i = 0; i < NUMOF(plates); i++) {
			temp_options.push_back(add_option(radio_option(plates[i].m_name.get())
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				vehicle::customs::vars::m_vars.m_cached_stats.m_plate_index = plates[i].m_result;
			})
				.add_hover([=] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_number_plate_text_index(menu::player::get_local_player().m_vehicle, plates[i].m_result);
			})));
		}

		if (vehicle::customs::vars::m_vars.m_cached_stats.m_plate_index != 0) {
			if (vehicle::customs::vars::m_vars.m_cached_stats.m_plate_index >= temp_options.size()) return;
			temp_options[vehicle::customs::vars::m_vars.m_cached_stats.m_plate_index]->update_selected();
			menu::base::set_current_option(vehicle::customs::vars::m_vars.m_cached_stats.m_plate_index + 1);
		}
		return;
	}

	if (m_vars.m_mod_type == MOD_DASHBOARD
		|| m_vars.m_mod_type == MOD_DIAL
		|| m_vars.m_mod_type == MOD_DOOR_SPEAKER
		|| m_vars.m_mod_type == MOD_SEATS
		|| m_vars.m_mod_type == MOD_STEERINGWHEEL
		|| m_vars.m_mod_type == MOD_ORNAMENTS
		|| m_vars.m_mod_type == MOD_SHIFTER_LEAVERS
		|| m_vars.m_mod_type == MOD_SPEAKERS) {
		//SetParentSubmenu<VehicleEditorBennysInteriorMenu>();
	}

	std::vector<std::shared_ptr<radio_option>> temp_options;

	std::string stock_name = get_string("None");
	if (stock_mod_names.find(m_vars.m_mod_type) != stock_mod_names.end()) {
		stock_name = get_string(stock_mod_names[m_vars.m_mod_type]);
	}

	temp_options.push_back(add_option(radio_option(stock_name)
		.add_radio(m_vars.m_context)
		.add_click([=] {
		vehicle::customs::vars::update_caches();
		*m_vars.m_value = -1;
	})
		.add_hover([] {
		native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
		native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, m_vars.m_mod_type, -1, false);
	})));

	for (int i = 0; i < native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, m_vars.m_mod_type); i++) {
		const char* mod_label = native::get_mod_text_label(menu::player::get_local_player().m_vehicle, m_vars.m_mod_type, i);
		if (is_valid_ptr(mod_label)) {
			temp_options.push_back(add_option(radio_option(native::get_label_text(mod_label))
				.add_radio(m_vars.m_context)
				.add_click([=] {
				vehicle::customs::vars::update_caches();
				*m_vars.m_value = i;
			})
				.add_hover([=] {
				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, m_vars.m_mod_type, i, false);
			})));
		}
	}

	if (m_vars.m_value) {
		if (*m_vars.m_value != -1) {
			if (*m_vars.m_value + 1 >= temp_options.size()) return;

			if (temp_options[*m_vars.m_value + 1]) {
				temp_options[*m_vars.m_value + 1]->update_selected();
			}

			menu::base::set_current_option(*m_vars.m_value + 1);
		}
	}
}

void vehicle_customs_lsc_menu::feature_update() {}

vehicle_customs_lsc_menu* g_instance;
vehicle_customs_lsc_menu* vehicle_customs_lsc_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_customs_lsc_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}