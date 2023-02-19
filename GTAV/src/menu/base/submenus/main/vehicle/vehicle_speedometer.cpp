#include "vehicle_speedometer.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle.h"
#include "menu/base/util/stacked_display.h"

using namespace vehicle::speedometer::vars;

namespace vehicle::speedometer::vars {
	variables m_vars;
}

void vehicle_speedometer_menu::load() {
	set_name("Speedometer");
	set_parent<vehicle_menu>();

	add_option(toggle_option("Basic Speedometer")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_basic_speedometer)
		.add_click([] {
			if (!m_vars.m_basic_speedometer) {
				menu::display::disable("SR_BASICSPEEDO");
			}
		}).add_savable(get_submenu_name_stack()));

	add_option(toggle_option("Numberplate Speedometer")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_number_plate_speedometer)
		.add_click([] {
			if (m_vars.m_number_plate_speedometer) {
				if (menu::player::get_local_player().m_in_vehicle) {
					m_vars.m_previous_number_plate_text = native::get_vehicle_number_plate_text(menu::player::get_local_player().m_vehicle);
				}
			} else {
				native::set_vehicle_number_plate_text(menu::player::get_local_player().m_vehicle, m_vars.m_previous_number_plate_text.c_str());
			}
		}).add_savable(get_submenu_name_stack()));

	add_string("Speed");
}

void vehicle_speedometer_menu::update() {}

void vehicle_speedometer_menu::update_once() {}

void vehicle_speedometer_menu::feature_update() {
	if (menu::player::get_local_player().m_in_vehicle) {
		if (m_vars.m_basic_speedometer) {
			float speed = native::get_entity_speed(menu::player::get_local_player().m_vehicle) * global::vars::g_selected_metric_system.first;
			menu::display::update("SR_BASICSPEEDO", get_string("Speed"), util::va::va("%.0f %s", speed, global::vars::g_selected_metric_system.second.c_str()));
		}

		if (m_vars.m_number_plate_speedometer) {
			float speed = native::get_entity_speed(menu::player::get_local_player().m_vehicle) * global::vars::g_selected_metric_system.first;
			native::set_vehicle_number_plate_text(menu::player::get_local_player().m_vehicle, util::va::va("%.0f %s", speed, global::vars::g_selected_metric_system.second.c_str()));
		}
	}
}

vehicle_speedometer_menu* g_instance;
vehicle_speedometer_menu* vehicle_speedometer_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_speedometer_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}