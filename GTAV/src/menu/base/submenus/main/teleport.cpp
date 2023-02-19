#include "teleport.h"
#include "menu/base/submenu_handler.h"
#include "../main.h"
#include "teleport/teleport_save_load.h"
#include "teleport/teleport_settings.h"
#include "teleport/teleport_selected.h"
#include "teleport/teleport_directional.h"
#include "teleport/teleport_ipl.h"
#include "teleport/teleport_stores.h"
#include "menu/base/util/control.h"
#include "util/fiber_pool.h"
#include "util/fiber.h"
#include "global/lists.h"

using namespace teleport::vars;

namespace teleport::vars {
	variables m_vars;

	scroll_struct<int> vehicle_types[] = {
		{ localization("Inside", true), 0 },
		{ localization("Outside", true), 1 },
	};

	scroll_struct<math::vector3<float>> airstrips[] = {
		{ localization("Arcadius - Helipad", true), { -143.71f, -593.77f, 211.78f } },
		{ localization("Casino - Helipad", true), { 974.41f, 48.71f, 123.12f } },
		{ localization("Davis Hospital - Helipad", true), { 318.68f, -1451.53f, 46.51f } },
		{ localization("Del Perro - Helipad", true), { -1224.19f, -829.52f, 29.41f } },
		{ localization("Del Perro - Helipad 2", true), { -1390.84f, -478.36f, 91.25f } },
		{ localization("Del Perro - Helipad 3", true), { -1582.87f, -569.21f, 116.33f } },
		{ localization("Downtown Vinewood - PD Helipad", true), { 571.07f, 4.87f, 103.23f } },
		{ localization("Elysian Island - Helipad", true), { 484.33f, -3375.14f, 6.07f } },
		{ localization("Fort Zancudo - Hangar", true), { -1828.f, 2974.f, 32.81f } },
		{ localization("Fort Zancudo - Helipad", true), { -1859.f, 2816.f, 32.81f } },
		{ localization("Fort Zancudo - Jet Spawn", true), { -2242.52f, 3229.81f, 32.81f } },
		{ localization("Fort Zancudo - North Runway", true), { -2022.53f, 2867.f, 32.91f } },
		{ localization("Grapeseed - East Runway", true), { 2136.51f, 4810.95f, 41.20f } },
		{ localization("Humane Labs - Helipad", true), { 2510.61f, -341.90f, 118.19f } },
		{ localization("La Mesa - Helipad", true), { 910.54f, -1680.18f, 51.13f } },
		{ localization("La Puerta - Helipad", true), { -726.48f, -1423.14f, 5.f } },
		{ localization("Little Seoul - Helipad", true), { -583.80f, -930.93f, 36.83f } },
		{ localization("LSIA - Hangar", true), { -998.97f, -3025.83f, 13.95f } },
		{ localization("LSIA - Helipad", true), { -1159.51f, -2889.13f, 13.95f } },
		{ localization("LSIA - East Runway", true), { -1328.78f, -2197.64f, 13.94f } },
		{ localization("LSIA - North Runway", true), { -940.38f, -3371.61f, 13.94f } },
		{ localization("Maze Bank - Helipad", true), { -75.02f, -826.03f, 326.18f } },
		{ localization("Mission Row - Helipad", true), { 476.71f, -1107.70f, 43.08f } },
		{ localization("Mission Row - Helipad 2", true), { 450.16f, -981.89f, 43.69f } },
		{ localization("Rockford Hills - Helipad", true), { -903.96f, -373.48f, 136.26f } },
		{ localization("Sandy Shores - East Runway", true), { 1707.08f, 3251.56f, 41.02f } },
		{ localization("Sandy Shores - Helipad", true), { 1781.56f, 3249.81f, 42.12f } },
		{ localization("Vespucci Canals - Helipad", true), { -1094.59f, -834.67f, 37.68f } },
	};

	scroll_struct<math::vector3<float>> docks[] = {
		{ localization("Del Perro Beach", true), { -1799.99f, -1224.71f, 1.58f } },
		{ localization("Elysian Island - Harbor", true), { -69.52f, -2775.38f, 6.08f } },
		{ localization("Elysian Island - South Docks", true), { -499.00f, -2923.25f, 6.00f } },
		{ localization("Galilee", true), { 1302.69f, 4233.84f, 33.91f } },
		{ localization("La Puerta", true), { -800.71f, -1512.88f, 1.60f } },
		{ localization("Paleto Cove", true), { -1609.46f, 5255.05f, 3.97f } },
		{ localization("San Chianski Mountain Range", true), { 3865.21f, 4463.74f, 2.72f } },
	};

	scroll_struct<math::vector3<float>> zones[] = {
		{ localization("Chumash", true), { -3126.20f, 1122.80f, 20.61f } },
		{ localization("Downtown Los Santos", true), { 21.25f, -750.30f, 44.10f } },
		{ localization("Del Perro", true), { -1434.20f, -736.68f, 23.51f, } },
		{ localization("East Los Santos", true), { 773.83f, -2047.25f, 29.24f, } },
		{ localization("Elysian Island", true), { 198.34f, -2572.42f, 6.12f, } },
		{ localization("Grapeseed", true), { 2168.62f, 4922.48f, 40.68f } },
		{ localization("Harmony", true), { 580.02f, 2701.47f, 41.75f } },
		{ localization("La Puerta", true), { -419.77f, -1753.76f, 20.21f, } },
		{ localization("Little Seoul", true), { -551.83f, -970.10f, 23.42f, } },
		{ localization("Pacific Bluffs", true), { -2022.12f, -277.07f, 32.10f, } },
		{ localization("Paleto Bay", true), { -59.84f, 6290.79f, 31.41f } },
		{ localization("Rocksford Hills", true), { -848.61f, -57.22f, 37.84f, } },
		{ localization("Sandy Shores", true), { 2050.89f, 3723.60f, 32.92f } },
		{ localization("South Los Santos", true), { -176.76f, -1634.20f, 33.32f, } },
		{ localization("Vespucci", true), { -1147.62f, -1298.82f, 5.12f, } },
		{ localization("Vinewood", true), { 27.00f, 270.65f, 109.48f, } },
		{ localization("Vinewood Hills", true), { 293.96f, 823.40f, 191.21f, } },
	};

	scroll_struct<math::vector3<float>> interiors[] = {
		{ localization("Apartment Complex", true), { -1159.14f, -225.50f, 37.94f, } },
		{ localization("FIB Floor 47", true), { 137.60f, -767.00f, 234.15f, } },
		{ localization("FIB Floor 49", true), { 142.09f, -768.82f, 242.15f, } },
		{ localization("FIB Floors 50 & 51", true), { 142.18f, -769.20f, 250.15f, } },
		{ localization("LSIA", true), { -1559.07f, -3236.76f, 29.63f, } },
		{ localization("LSIA Hangar", true), { -931.94f, -2922.82f, 13.95f, } },
		{ localization("Motel", true), { 152.26f, -1004.46f, -99.00f, } },
		{ localization("Mount Chilliad Mill", true), { -579.96f, 5313.40f, 70.21f, } },
		{ localization("Pacific Standard Bank", true), { 224.28f, 210.89f, 105.55f, } },
		{ localization("Rundown Motel", true), { 1552.53f, 3557.59f, 35.36f, } },
		{ localization("Sandy Shores Air Control", true), { 1699.77f, 3299.43f, 41.15f, } },
		{ localization("Solomon's Office", true), { -1003.96f, -477.95f, 50.03f, } },
	};

	int get_ideal_switch(math::vector3<float> from, math::vector3<float> to) {
		return native::get_ideal_player_switch_type(from.x, from.y, from.z, to.x, to.y, to.z);
	}

	void teleport(math::vector3<float> coords, bool only_player, std::function<void(math::vector3<float>)> callback, bool no_tp) {
		if (m_vars.m_transition) {
			util::fiber::pool::add([=] {
				uint32_t hash = native::get_hash_key(menu::player::get_local_player().m_connected ? "mp_m_freemode_01" : "player_zero");
				menu::control::request_model(hash, [=](uint32_t model) {
					Ped ped = native::create_ped(13, model, coords.x, coords.y, coords.z, 0.f, true, false);
					if (native::does_entity_exist(ped)) {
						native::start_player_switch(menu::player::get_local_player().m_ped, ped, 0, get_ideal_switch(menu::player::get_local_player().m_coords, coords));
						native::set_entity_as_mission_entity(ped, true, true);
						native::delete_entity(&ped);

						if (native::is_player_switch_in_progress()) {
							while (native::get_player_switch_state() != 8) {
								util::fiber::sleep(100);

								if (native::get_player_switch_state() == 12) break;
							}

							if (m_vars.m_include_current_vehicle && !only_player) {
								if (menu::player::get_local_player().m_in_vehicle) {
									Ped driver = native::get_ped_in_vehicle_seat(menu::player::get_local_player().m_vehicle, -1, 0);
									if (driver == menu::player::get_local_player().m_ped) {
										if (!no_tp) native::set_entity_coords(menu::player::get_local_player().m_vehicle, coords.x, coords.y, coords.z, false, false, false, false);
										callback(coords);
									} else {
										// request control
										menu::control::request_control(menu::player::get_local_player().m_vehicle, [=](Entity entity) {
											if (!no_tp) native::set_entity_coords(entity, coords.x, coords.y, coords.z, false, false, false, false);
											callback(coords);
										});
									}
								} else {
									if (!no_tp) native::set_entity_coords(menu::player::get_local_player().m_ped, coords.x, coords.y, coords.z, false, false, false, false);
									callback(coords);
								}
							} else {
								if (!no_tp) native::set_entity_coords(menu::player::get_local_player().m_ped, coords.x, coords.y, coords.z, false, false, false, false);
								callback(coords);
							}
						}
					}
				});
			});
		} else {
			if (m_vars.m_include_current_vehicle && !only_player) {
				if (menu::player::get_local_player().m_in_vehicle) {
					Ped driver = native::get_ped_in_vehicle_seat(menu::player::get_local_player().m_vehicle, -1, 0);
					if (driver == menu::player::get_local_player().m_ped) {
						if (!no_tp) native::set_entity_coords(menu::player::get_local_player().m_vehicle, coords.x, coords.y, coords.z, false, false, false, false);
						callback(coords);
					} else {
						// request control
						menu::control::request_control(menu::player::get_local_player().m_vehicle, [=](Entity entity) {
							if (!no_tp) native::set_entity_coords(entity, coords.x, coords.y, coords.z, false, false, false, false);
							callback(coords);
						});
					}
				} else {
					if (!no_tp) native::set_entity_coords(menu::player::get_local_player().m_ped, coords.x, coords.y, coords.z, false, false, false, false);
					callback(coords);
				}
			} else {
				if (!no_tp) native::set_entity_coords(menu::player::get_local_player().m_ped, coords.x, coords.y, coords.z, false, false, false, false);
				callback(coords);
			}
		}
	}

	void teleport_to_objective() {
		teleport_menu* instance = teleport_menu::get();
		bool teleported = false;

		rage::types::blip_list* list = global::vars::g_blip_list;
		if (list) {
			for (int i = 0; i < 1500; i++) {
				rage::types::blip* blip = list->m_blips[i];
				if (blip) {
					int color = blip->m_color;
					int icon = blip->m_sprite;

					if ((icon == 306) || (color == 66 && icon == 1) || (color == 60 && icon == 1) ||
						(color == 5 && icon == 1) || (color == 0 && icon == 38) || (color == 2 && icon == 1) || (color == 3 && icon == 1)) {
						math::vector3<float> coords = math::vector3_<float>::to_padded(blip->m_coords);
						if (coords.is_null()) {
							menu::notify::stacked(instance->get_string("Teleport"), instance->get_string("Failed to teleport to objective"));
						} else {
							teleported = true;
							teleport(coords);
							break;
						}
					}
				}
			}
		}

		if (!teleported) {
			menu::notify::stacked(instance->get_string("Teleport"), instance->get_string("Failed to find objective"));
		}
	}

	void teleport_to_nearest_player() {
		float closest_distance = std::numeric_limits<float>::max();
		Player closest_player = -1;

		menu::player::for_each([&](menu::player::player_context& player) {
			float distance = player.m_coords.get_distance(menu::player::get_local_player().m_coords);
			if (distance < closest_distance) {
				closest_distance = distance;
				closest_player = player.m_id;
			}
		});

		if (closest_player != -1) {
			teleport(menu::player::get_player(closest_player).m_coords);
		}
	}

	void teleport_to_nearest_vehicle() {
		float closest_distance = std::numeric_limits<float>::max();
		Vehicle closest_vehicle = -1;
		int vehicle_seat = -2;

		global::vars::g_vehicle_pool->for_each([&](Entity vehicle, void* veh) {
			if (menu::player::get_local_player().m_in_vehicle && vehicle == menu::player::get_local_player().m_vehicle) return;

			math::vector3<float> coords = native::get_entity_coords(vehicle, true);

			float distance = coords.get_distance(menu::player::get_local_player().m_coords);
			if (distance < closest_distance) {
				Ped driver = native::get_ped_in_vehicle_seat(vehicle, -1, 0);
				if (!native::does_entity_exist(driver) || !native::is_ped_a_player(driver)) {
					closest_distance = distance;
					closest_vehicle = vehicle;
					vehicle_seat = -1;
					return;
				}
				
				for (int i = 0; i < native::get_vehicle_max_number_of_passengers(vehicle); i++) {
					Ped ped = native::get_ped_in_vehicle_seat(vehicle, i, 0);
					if (!native::does_entity_exist(ped)) {
						closest_distance = distance;
						closest_vehicle = vehicle;
						vehicle_seat = i;
						return;
					}
				}
			}
		});

		if (closest_vehicle != -1) {
			if (native::does_entity_exist(closest_vehicle)) {
				if (m_vars.m_nearest_vehicle == 0) {
					// inside
					Ped driver = native::get_ped_in_vehicle_seat(closest_vehicle, -1, 0);
					if (native::does_entity_exist(driver)) {
						if (native::is_ped_a_player(driver)) {
							menu::control::request_control(closest_vehicle, [](Entity, int) {}, true);
						} else {
							native::clear_ped_tasks_immediately(driver);
						}
					}

					native::set_ped_into_vehicle(menu::player::get_local_player().m_ped, closest_vehicle, vehicle_seat);
				} else {
					// outside
					teleport(native::get_entity_coords(closest_vehicle, true), true);
				}
			}
		}
	}

	void teleport_to_personal_vehicle() {
		bool found = false;

		for (int i = 225; i < 227; i++) {
			int handle = native::get_first_blip_info_id(i);
			if (native::does_blip_exist(handle)) {
				math::vector3<float> coords = native::get_blip_coords(handle);
				if (!coords.is_null()) {
					found = true;

					Vehicle vehicle = native::get_closest_vehicle(coords.x, coords.y, coords.z, 5.f, 0, 70);
					if (m_vars.m_personal_vehicle == 0) {
						// inside
						Ped driver = native::get_ped_in_vehicle_seat(vehicle, -1, 0);
						if (native::does_entity_exist(driver)) {
							if (native::is_ped_a_player(driver)) {
								menu::control::request_control(vehicle, [](Entity, int) {}, true);
							} else {
								native::clear_ped_tasks_immediately(driver);
							}
						}

						native::set_ped_into_vehicle(menu::player::get_local_player().m_ped, vehicle, -1);
					} else {
						// outside
						teleport(native::get_entity_coords(vehicle, true), true);
					}

					break;
				}
			}
		}

		if (!found) {
			teleport_menu* _this = teleport_menu::get();
			menu::notify::stacked(_this->get_string("Teleport"), _this->get_string("Failed to find personal vehicle"));
		}
	}

	void teleport_to_last_vehicle() {
		Vehicle vehicle = native::get_players_last_vehicle();
		if (native::does_entity_exist(vehicle)) {
			if (m_vars.m_last_vehicle == 0) {
				// inside
				Ped driver = native::get_ped_in_vehicle_seat(vehicle, -1, 0);
				if (native::does_entity_exist(driver)) {
					if (native::is_ped_a_player(driver)) {
						menu::control::request_control(vehicle, [](Entity, int) {}, true);
					} else {
						native::clear_ped_tasks_immediately(driver);
					}
				}

				native::set_ped_into_vehicle(menu::player::get_local_player().m_ped, vehicle, -1);
			} else {
				// outside
				teleport(native::get_entity_coords(vehicle, true), true);
			}
		} else {
			teleport_menu* _this = teleport_menu::get();
			menu::notify::stacked(_this->get_string("Teleport"), _this->get_string("Failed to find last vehicle"));
		}
	}

	void teleport_to_waypoint() {
		util::fiber::pool::add([=] {
			math::vector3<float> coords = native::get_blip_info_id_coord(native::get_first_blip_info_id(8));
			if (coords.is_null()) {
				teleport_menu* _this = teleport_menu::get();
				menu::notify::stacked(_this->get_string("Teleport"), _this->get_string("Failed to find waypoint"));
				return;
			}

			Entity entity = menu::player::get_local_player().m_ped;
			if (m_vars.m_include_current_vehicle && menu::player::get_local_player().m_in_vehicle) {
				entity = menu::player::get_local_player().m_vehicle;
			}

			bool ground_found = false;
			float ground_check_height[] = { 100.0f, 150.0f, 50.0f, 0.0f, 200.0f, 250.0f, 300.0f, 350.0f, 400.0f, 450.0f, 500.0f, 550.0f, 600.0f, 650.0f, 700.0f, 750.0f, 800.0f };
			for (int i = 0; i < sizeof(ground_check_height) / sizeof(float); i++) {
				native::set_entity_coords_no_offset(entity, coords.x, coords.y, ground_check_height[i], 0, 0, 1);
				util::fiber::sleep(100);
				if (native::get_ground_z_for_3d_coord(coords.x, coords.y, ground_check_height[i], &coords.z, 0)) {
					ground_found = true;
					break;
				}
			}

			if (!ground_found) {
				coords.z = 1000.0f;
				native::give_delayed_weapon_to_ped(menu::player::get_local_player().m_ped, 0xFBAB5776, 1, 0);
			}

			native::set_entity_coords(entity, coords.x, coords.y, coords.z, false, false, false, false);
		});
	}
}

void teleport_menu::load() {
	set_name("Teleport");
	set_parent<main_menu>();

	add_string("Teleport");
	add_string("Failed to teleport to objective");
	add_string("Failed to find objective");
	add_string("Failed to find personal vehicle");
	add_string("Failed to find waypoint");
	add_string("Failed to find last vehicle");

	teleport::selected::vars::m_vars.m_selected = airstrips;
	teleport::selected::vars::m_vars.m_size = NUMOF(airstrips);

	add_option(submenu_option("Settings")
		.add_translate().add_hotkey()
		.add_submenu<teleport_settings_menu>());

	add_option(submenu_option("Save and Load")
		.add_translate().add_hotkey()
		.add_submenu<teleport_save_load_menu>());

	m_vars.m_popular = add_option(submenu_option("Popular")
		.add_translate().add_hotkey()
		.add_submenu<teleport_selected_menu>()
		.add_click([] {
			teleport::selected::vars::m_vars.m_selected = global::lists::g_popular_locations;
			teleport::selected::vars::m_vars.m_size = NUMOF(global::lists::g_popular_locations);
			teleport_selected_menu::get()->set_name(m_vars.m_popular->get_name().get(), false, false);
		}));

	add_option(submenu_option("Stores")
		.add_translate().add_hotkey()
		.add_submenu<teleport_stores_menu>());

	m_vars.m_airstrips = add_option(submenu_option("Airstrips and Helipads")
		.add_translate().add_hotkey()
		.add_submenu<teleport_selected_menu>()
		.add_click([] {
			teleport::selected::vars::m_vars.m_selected = airstrips;
			teleport::selected::vars::m_vars.m_size = NUMOF(airstrips);
			teleport_selected_menu::get()->set_name(m_vars.m_airstrips->get_name().get(), false, false);
		}));

	m_vars.m_zones = add_option(submenu_option("Zones")
		.add_translate().add_hotkey()
		.add_submenu<teleport_selected_menu>()
		.add_click([] {
			teleport::selected::vars::m_vars.m_selected = zones;
			teleport::selected::vars::m_vars.m_size = NUMOF(zones);
			teleport_selected_menu::get()->set_name(m_vars.m_zones->get_name().get(), false, false);
		}));

	m_vars.m_docks = add_option(submenu_option("Docks")
		.add_translate().add_hotkey()
		.add_submenu<teleport_selected_menu>()
		.add_click([] {
			teleport::selected::vars::m_vars.m_selected = docks;
			teleport::selected::vars::m_vars.m_size = NUMOF(docks);
			teleport_selected_menu::get()->set_name(m_vars.m_docks->get_name().get(), false, false);
		}));

	m_vars.m_interiors = add_option(submenu_option("Interiors")
		.add_translate().add_hotkey()
		.add_submenu<teleport_selected_menu>()
		.add_click([] {
			teleport::selected::vars::m_vars.m_selected = interiors;
			teleport::selected::vars::m_vars.m_size = NUMOF(interiors);
			teleport_selected_menu::get()->set_name(m_vars.m_interiors->get_name().get(), false, false);
		}));

	add_option(submenu_option("IPL")
		.add_translate().add_hotkey()
		.add_submenu<teleport_ipl_menu>());

	add_option(submenu_option("Directional")
		.add_translate().add_hotkey()
		.add_submenu<teleport_directional_menu>());

	add_option(button_option("Teleport to Objective")
		.add_translate().add_hotkey()
		.add_click(teleport_to_objective));

	add_option(button_option("Teleport to Waypoint")
		.add_translate().add_hotkey()
		.add_click(teleport_to_waypoint));

	add_option(button_option("Teleport to Nearest Player")
		.add_translate().add_hotkey()
		.add_click(teleport_to_nearest_player));

	add_option(scroll_option<int>(SCROLLSELECT, "Teleport to Nearest Vehicle")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_nearest_vehicle, 0, NUMOF(vehicle_types), vehicle_types)
		.add_click(teleport_to_nearest_vehicle));

	add_option(scroll_option<int>(SCROLLSELECT, "Teleport to Personal Vehicle")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_personal_vehicle, 0, NUMOF(vehicle_types), vehicle_types)
		.add_click(teleport_to_personal_vehicle));

	add_option(scroll_option<int>(SCROLLSELECT, "Teleport to Last Vehicle")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_last_vehicle, 0, NUMOF(vehicle_types), vehicle_types)
		.add_click(teleport_to_last_vehicle));
}

void teleport_menu::update() {}

void teleport_menu::update_once() {}

void teleport_menu::feature_update() {
	if (m_vars.m_auto_waypoint) {
		if (native::is_waypoint_active() && !m_vars.m_has_teleported_flag) {
			teleport_to_waypoint();
			m_vars.m_has_teleported_flag = true;
			m_vars.m_waypoint_timer = GetTickCount() + 3000;
		}

		if (m_vars.m_waypoint_timer < GetTickCount()) {
			m_vars.m_has_teleported_flag = false;
		}
	}
}

teleport_menu* g_instance;
teleport_menu* teleport_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new teleport_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}