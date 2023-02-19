#include "vehicle_autopilot.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle.h"

using namespace vehicle::autopilot::vars;

namespace vehicle::autopilot::vars {
	variables m_vars;

	scroll_struct<math::vector3_<float>> destinations[] = {
		{ localization("Wander", true), { 0.f, 0.f, 0.f } },
		{ localization("Waypoint", true), { 0.f, 0.f, 0.f } },
		{ localization("Eclipse Towers", true), { -775.0500f, 312.32f, 85.7f } },
		{ localization("Los Santos Airport", true), { -1102.2910f, -2894.5160f, 13.9467f } },
		{ localization("Fort Zancudo", true), { -2012.8470f, 2956.5270f, 32.8101f } },
		{ localization("Mount Chiliad", true), { 430.2037f, 5614.7340f, 766.1684f } },
		{ localization("Diamond Casino", true), { 919.94f, 50.7f, 80.90f } },
	};

	scroll_struct<int> styles[] = {
		{ localization("Normal", true), 786603 },
		{ localization("Ignore Stops", true), 2883621 },
		{ localization("Rushed", true), 1074528293 }
	};

	void disable() {
		native::clear_ped_tasks_immediately(menu::player::get_local_player().m_ped);
		native::set_ped_into_vehicle(menu::player::get_local_player().m_ped, menu::player::get_local_player().m_vehicle, -1);
	}

	void enable() {
		disable();

		vehicle::vars::run_task(menu::player::get_local_player().m_vehicle, [](Vehicle veh) {
			switch (m_vars.m_destinations) {
				case 0:
					native::task_vehicle_drive_wander(menu::player::get_local_player().m_ped, veh, m_vars.m_speed, styles[m_vars.m_styles].m_result);
					break;

				case 1:
					if (native::does_blip_exist(native::get_first_blip_info_id(8))) {
						math::vector3<float> coords = native::get_blip_coords(native::get_first_blip_info_id(8));
						native::task_vehicle_drive_to_coord_longrange(menu::player::get_local_player().m_ped, veh, coords.x, coords.y, coords.z, m_vars.m_speed, styles[m_vars.m_styles].m_result, 15.f);
					} else {
						menu::notify::stacked(vehicle_autopilot_menu::get()->get_string("Autopilot"), vehicle_autopilot_menu::get()->get_string("No waypoint found"));
					}

					break;

				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
					math::vector3_<float> coords = destinations[m_vars.m_destinations].m_result;
					native::task_vehicle_drive_to_coord_longrange(menu::player::get_local_player().m_ped, veh, coords.x, coords.y, coords.z, m_vars.m_speed, styles[m_vars.m_styles].m_result, 15.f);
					break;
			}
		});
	}
}

void vehicle_autopilot_menu::load() {
	set_name("Autopilot");
	set_parent<vehicle_menu>();

	add_string("Autopilot");
	add_string("No waypoint found");

	add_option(scroll_option<math::vector3_<float>>(SCROLL, "Destination")
		.add_translate()
		.add_scroll(m_vars.m_destinations, 0, NUMOF(destinations), destinations));

	add_option(scroll_option<int>(SCROLL, "Style")
		.add_translate()
		.add_scroll(m_vars.m_styles, 0, NUMOF(styles), styles));

	add_option(number_option<float>(SCROLL, "Speed")
		.add_translate()
		.add_number(m_vars.m_speed, "%.0f", 1.f).add_min(0).add_max(200.f).show_max());

	add_option(button_option("Enable Autopilot")
		.add_translate().add_hotkey()
		.add_click(enable));

	add_option(button_option("Disable Autopilot")
		.add_translate().add_hotkey()
		.add_click(disable));
}

void vehicle_autopilot_menu::update() {}

void vehicle_autopilot_menu::update_once() {}

void vehicle_autopilot_menu::feature_update() {}

vehicle_autopilot_menu* g_instance;
vehicle_autopilot_menu* vehicle_autopilot_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_autopilot_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}