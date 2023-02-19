#include "spawner_vehicle_save.h"
#include "menu/base/submenu_handler.h"
#include "../../spawner.h"
#include "util/dirs.h"
#include "util/log.h"
#include <fstream>

using namespace spawner::vehicle::save::vars;

namespace spawner::vehicle::save::vars {
	variables m_vars;

	void save_vehicle(button_option* _this, const char* name) {
		if (!menu::player::get_local_player().m_in_vehicle) {
			menu::notify::stacked(spawner_vehicle_save_menu::get()->get_name().get(), "You need to be in a vehicle!");
			return;
		}

		try {
			std::ofstream output(util::va::va("%s%s.json", util::dirs::get_path(lsc), name));
			nlohmann::json object;

			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);

			object["Armor"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ARMOR);
			object["Brakes"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_BRAKES);
			object["FrontBumper"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTBUMPER);
			object["RearBumper"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_REARBUMPER);
			object["Engine"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ENGINE);
			object["Exhaust"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_EXHAUST);
			object["Hood"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HOOD);
			object["Horn"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HORNS);
			object["Skirts"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SIDESKIRT);
			object["Suspension"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SUSPENSION);
			object["Transmission"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TRANSMISSION);
			object["Spoiler"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SPOILER);
			object["Grille"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_GRILLE);
			object["LeftFender"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FENDER);
			object["RightFender"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_RIGHTFENDER);
			object["Roof"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ROOF);
			object["Chassis"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_CHASSIS);
			object["FrontWheels"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);
			object["BackWheels"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_BACKWHEELS);

			object["WindowTint"] = native::get_vehicle_window_tint(menu::player::get_local_player().m_vehicle);
			object["Turbo"] = native::is_toggle_mod_on(menu::player::get_local_player().m_vehicle, MOD_TURBO);
			object["Lights"] = native::is_toggle_mod_on(menu::player::get_local_player().m_vehicle, MOD_XENONLIGHTS);
			object["XenonColor"] = native::get_vehicle_xenon_lights_colour(menu::player::get_local_player().m_vehicle);
			object["PlateIndex"] = native::get_vehicle_number_plate_text_index(menu::player::get_local_player().m_vehicle);
			object["PlateText"] = native::get_vehicle_number_plate_text(menu::player::get_local_player().m_vehicle);
			object["WheelType"] = native::get_vehicle_wheel_type(menu::player::get_local_player().m_vehicle);
			object["CustomTires"] = native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);

			object["Unk17"] = native::is_toggle_mod_on(menu::player::get_local_player().m_vehicle, MOD_UNK17);
			object["Unk19"] = native::is_toggle_mod_on(menu::player::get_local_player().m_vehicle, MOD_UNK19);
			object["TireSmoke"] = native::is_toggle_mod_on(menu::player::get_local_player().m_vehicle, MOD_TIRESMOKE);
			object["Unk21"] = native::is_toggle_mod_on(menu::player::get_local_player().m_vehicle, MOD_UNK21);

			// Bennys
			object["BennysPlateholder"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_PLATEHOLDER);
			object["BennysVanityPlate"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_VANITY_PLATES);
			object["BennysTrimDesign"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TRIM_DESIGN);
			object["BennysOrnaments"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ORNAMENTS);
			object["BennysInteriorDesign"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_DASHBOARD);
			object["BennysDials"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_DIAL);
			object["BennysDoors"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_DOOR_SPEAKER);
			object["BennysSeats"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SEATS);
			object["BennysSteeringWheel"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_STEERINGWHEEL);
			object["BennysShifter"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SHIFTER_LEAVERS);
			object["BennysPlaques"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_PLAQUES);
			object["BennysTrunk"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TRUNK);
			object["BennysAudioInstall"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SPEAKERS);
			object["BennysHydraulics"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HYDRULICS);
			object["BennysEngineBlock"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ENGINE_BLOCK);
			object["BennysAirFilters"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_AIR_FILTER);
			object["BennysStuntBrace"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_STRUTS);
			object["BennysArchCovers"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ARCH_COVER);
			object["BennysAerials"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_AERIALS);
			object["BennysRearStripeColor"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TRIM);
			object["BennysTank"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TANK);
			object["BennysWindowMod"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_WINDOWS);
			object["BennysLivery"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_LIVERY);
			object["BennysSpecialFrontRims"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SPECIAL_FRONT_RIMS);
			object["BennysSpecialRearRims"] = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SPECIAL_REAR_RIMS);

			object["LowGrip"] = native::get_vehicle_tyres_are_low_grip(menu::player::get_local_player().m_vehicle);
			object["Bulletproof"] = native::get_vehicle_tyres_can_burst(menu::player::get_local_player().m_vehicle);

			object["Neon"] = {
				native::is_vehicle_neon_light_enabled(menu::player::get_local_player().m_vehicle, 0),
				native::is_vehicle_neon_light_enabled(menu::player::get_local_player().m_vehicle, 1),
				native::is_vehicle_neon_light_enabled(menu::player::get_local_player().m_vehicle, 2),
				native::is_vehicle_neon_light_enabled(menu::player::get_local_player().m_vehicle, 3)
			};

			color_rgba neon_color;
			native::get_vehicle_neon_lights_colour(menu::player::get_local_player().m_vehicle, &neon_color.r, &neon_color.g, &neon_color.b);
			object["NeonColor"] = { neon_color.r, neon_color.g, neon_color.b };

			color_rgba tyre_smoke_color;
			native::get_vehicle_tyre_smoke_color(menu::player::get_local_player().m_vehicle, &tyre_smoke_color.r, &tyre_smoke_color.g, &tyre_smoke_color.b);
			object["TyreSmokeColor"] = { tyre_smoke_color.r, tyre_smoke_color.g, tyre_smoke_color.b };

			color_rgba vehicle_color;
			native::get_vehicle_color(menu::player::get_local_player().m_vehicle, &vehicle_color.r, &vehicle_color.g, &vehicle_color.b);
			object["VehicleColor"] = { vehicle_color.r, vehicle_color.g, vehicle_color.b };

			int pearlescent_color = 0;
			int wheel_color = 0;
			native::get_vehicle_extra_colours(menu::player::get_local_player().m_vehicle, &pearlescent_color, &wheel_color);

			object["PearlescentColor"] = pearlescent_color;
			object["WheelColor"] = wheel_color;

			color_rgba primary_color = vehicle_color;
			color_rgba secondary_color = vehicle_color;

			if (native::get_is_vehicle_primary_colour_custom(menu::player::get_local_player().m_vehicle)) {
				native::get_vehicle_custom_primary_colour(menu::player::get_local_player().m_vehicle, &primary_color.r, &primary_color.g, &primary_color.b);
			}

			if (native::get_is_vehicle_secondary_colour_custom(menu::player::get_local_player().m_vehicle)) {
				native::get_vehicle_custom_secondary_colour(menu::player::get_local_player().m_vehicle, &secondary_color.r, &secondary_color.g, &secondary_color.b);
			}

			object["PrimaryColor"] = { primary_color.r, primary_color.g, primary_color.b };
			object["SecondaryColor"] = { secondary_color.r, secondary_color.g, secondary_color.b };

			object["Traction"] = global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_traction_curve_max;

			output << object.dump(4);
			output.close();
			spawner_vehicle_save_menu::get()->update_once();
		} catch (std::exception& E) {
			LOG_WARN("[JSON] %s", E.what());
		}
	}

	void load_vehicle(std::string file) {
		if (!menu::player::get_local_player().m_in_vehicle) {
			menu::notify::stacked(spawner_vehicle_save_menu::get()->get_name().get(), "You need to be in a vehicle!");
			return;
		}

		try {
			std::ifstream input(util::va::va("%s%s.json", util::dirs::get_path(lsc), file.c_str()));
			if (input.good()) {
				nlohmann::json object = nlohmann::json::parse(input);

				native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);

				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ARMOR, object["Armor"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_BRAKES, object["Brakes"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTBUMPER, object["FrontBumper"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_REARBUMPER, object["RearBumper"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ENGINE, object["Engine"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_EXHAUST, object["Exhaust"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HOOD, object["Hood"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HORNS, object["Horn"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SIDESKIRT, object["Skirts"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SUSPENSION, object["Suspension"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TRANSMISSION, object["Transmission"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SPOILER, object["Spoiler"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_GRILLE, object["Grille"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FENDER, object["LeftFender"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_RIGHTFENDER, object["RightFender"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ROOF, object["Roof"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_CHASSIS, object["Chassis"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, object["FrontWheels"], object["CustomTires"]);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_BACKWHEELS, object["BackWheels"], object["CustomTires"]);

				native::toggle_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TURBO, object["Turbo"]);
				native::toggle_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_XENONLIGHTS, object["Lights"]);
				native::toggle_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_UNK17, object["Unk17"]);
				native::toggle_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_UNK19, object["Unk19"]);
				native::toggle_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TIRESMOKE, object["TireSmoke"]);
				native::toggle_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_UNK21, object["Unk21"]);

				native::set_vehicle_window_tint(menu::player::get_local_player().m_vehicle, object["WindowTint"]);
				native::set_vehicle_xenon_lights_colour(menu::player::get_local_player().m_vehicle, object["XenonColor"]);
				native::set_vehicle_number_plate_text_index(menu::player::get_local_player().m_vehicle, object["PlateIndex"]);
				native::set_vehicle_number_plate_text(menu::player::get_local_player().m_vehicle, object["PlateText"].get<std::string>().c_str());
				native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, object["WheelType"]);

				// Bennys
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_PLATEHOLDER, object["BennysPlateholder"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_VANITY_PLATES, object["BennysVanityPlate"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TRIM_DESIGN, object["BennysTrimDesign"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ORNAMENTS, object["BennysOrnaments"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_DASHBOARD, object["BennysInteriorDesign"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_DIAL, object["BennysDials"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_DOOR_SPEAKER, object["BennysDoors"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SEATS, object["BennysSeats"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_STEERINGWHEEL, object["BennysSteeringWheel"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SHIFTER_LEAVERS, object["BennysShifter"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_PLAQUES, object["BennysPlaques"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TRUNK, object["BennysTrunk"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SPEAKERS, object["BennysAudioInstall"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HYDRULICS, object["BennysHydraulics"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ENGINE_BLOCK, object["BennysEngineBlock"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_AIR_FILTER, object["BennysAirFilters"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_STRUTS, object["BennysStuntBrace"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ARCH_COVER, object["BennysArchCovers"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_AERIALS, object["BennysAerials"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TRIM, object["BennysRearStripeColor"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TANK, object["BennysTank"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_WINDOWS, object["BennysWindowMod"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_LIVERY, object["BennysLivery"], false);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SPECIAL_FRONT_RIMS, object["BennysSpecialFrontRims"], object["CustomTires"]);
				native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SPECIAL_REAR_RIMS, object["BennysSpecialRearRims"], object["CustomTires"]);

				if (!object["LowGrip"].is_null()) {
					native::set_vehicle_tyres_low_grip(menu::player::get_local_player().m_vehicle, object["LowGrip"].get<bool>());
				}

				if (!object["Bulletproof"].is_null()) {
					native::set_vehicle_tyres_can_burst(menu::player::get_local_player().m_vehicle, object["Bulletproof"].get<bool>());
				}

				native::set_vehicle_neon_light_enabled(menu::player::get_local_player().m_vehicle, 0, object["Neon"][0]);
				native::set_vehicle_neon_light_enabled(menu::player::get_local_player().m_vehicle, 1, object["Neon"][1]);
				native::set_vehicle_neon_light_enabled(menu::player::get_local_player().m_vehicle, 2, object["Neon"][2]);
				native::set_vehicle_neon_light_enabled(menu::player::get_local_player().m_vehicle, 3, object["Neon"][3]);

				native::set_vehicle_neon_lights_colour(menu::player::get_local_player().m_vehicle, object["NeonColor"][0], object["NeonColor"][1], object["NeonColor"][2]);
				native::set_vehicle_tyre_smoke_color(menu::player::get_local_player().m_vehicle, object["TyreSmokeColor"][0], object["TyreSmokeColor"][1], object["TyreSmokeColor"][2]);

				native::set_vehicle_custom_primary_colour(menu::player::get_local_player().m_vehicle, object["PrimaryColor"][0], object["PrimaryColor"][1], object["PrimaryColor"][2]);
				native::set_vehicle_custom_secondary_colour(menu::player::get_local_player().m_vehicle, object["SecondaryColor"][0], object["SecondaryColor"][1], object["SecondaryColor"][2]);

				native::set_vehicle_extra_colours(menu::player::get_local_player().m_vehicle, object["PearlescentColor"], object["WheelColor"]);

				global::vars::g_ped_factory->m_local_ped->m_vehicle->m_handling_data->m_traction_curve_max = object["Traction"];
			}
		} catch (std::exception& E) {
			LOG_WARN("[Json] %s", E.what());
		}
	}
}

void spawner_vehicle_save_menu::load() {
	set_name("Save and Load");
	set_parent<spawner_menu>();

	add_string("You need to be in a vehicle!");
	add_string("~m~None");

	add_option(button_option("Save Vehicle Modifications")
		.add_translate()
		.add_keyboard("Enter name of vehicle", 30, save_vehicle));

	add_option(break_option("Vehicles")
		.add_translate());
}

void spawner_vehicle_save_menu::update() {}

void spawner_vehicle_save_menu::update_once() {
	clear_options(2);

	for (std::string file : util::dirs::get_files_in_directory(util::dirs::get_path(lsc), ".json")) {
		add_option(button_option(file)
			.add_click([=] { load_vehicle(file); }));
	}
}

void spawner_vehicle_save_menu::feature_update() {}

spawner_vehicle_save_menu* g_instance;
spawner_vehicle_save_menu* spawner_vehicle_save_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new spawner_vehicle_save_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}