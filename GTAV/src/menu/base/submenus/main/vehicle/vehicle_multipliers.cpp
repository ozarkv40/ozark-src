#include "vehicle_multipliers.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle.h"
#include "rage/engine.h"

using namespace vehicle::multipliers::vars;

namespace vehicle::multipliers::vars {
	variables m_vars;

	void cache_traction() {
		if (menu::player::get_local_player().m_in_vehicle) {
			rage::types::ped_factory* factory = global::vars::g_ped_factory;
			if (factory) {
				rage::types::ped* Ped = factory->m_local_ped;
				if (Ped) {
					rage::types::vehicle* vehicle = Ped->m_vehicle;
					if (vehicle) {
						rage::types::handling_data* handling = vehicle->m_handling_data;
						if (handling) {
							m_vars.m_traction_curve_max = handling->m_traction_curve_max;
							m_vars.m_cached_traction = true;
							return;
						}
					}
				}
			}
		}

		m_vars.m_cached_traction = false;
	}

	void set_traction() {
		if (menu::player::get_local_player().m_in_vehicle) {
			rage::types::ped_factory* factory = global::vars::g_ped_factory;
			if (factory) {
				rage::types::ped* Ped = factory->m_local_ped;
				if (Ped) {
					rage::types::vehicle* vehicle = Ped->m_vehicle;
					if (vehicle) {
						rage::types::handling_data* handling = vehicle->m_handling_data;
						if (handling) {
							handling->m_traction_curve_max = m_vars.m_traction_curve_max;
						}
					}
				}
			}
		}
	}
}

void vehicle_multipliers_menu::load() {
	set_name("Multipliers");
	set_parent<vehicle_menu>();

	add_option(number_option<float>(SCROLL, "Power (RPM)")
		.add_translate()
		.add_number(m_vars.m_rpm, "%.0f", 1.f).add_min(1.f).add_max(10000.f).show_max().set_scroll_speed(10)
		.add_click([] {
			if (menu::player::get_local_player().m_in_vehicle) {
				native::set_vehicle_engine_power_multiplier(menu::player::get_local_player().m_vehicle, m_vars.m_rpm);
			}
		}));

	add_option(number_option<float>(SCROLL, "Torque")
		.add_translate()
		.add_number(m_vars.m_torque, "%.0f", 1.f).add_min(1.f).add_max(10000.f).show_max().set_scroll_speed(10));

	add_option(number_option<float>(SCROLL, "Headlight")
		.add_translate()
		.add_number(m_vars.m_headlight, "%.0f", 1.f).add_min(1.f).add_max(150.f).show_max().set_scroll_speed(10));

	add_option(number_option<float>(SCROLL, "Traction")
		.add_translate()
		.add_number(m_vars.m_traction_curve_max, "%.1f", 0.1f).add_min(0.f).add_max(1000.f).show_max().set_scroll_speed(10)
		.add_click(set_traction)
		.add_requirement([] { return m_vars.m_cached_traction; }));
}

void vehicle_multipliers_menu::update() {}

void vehicle_multipliers_menu::update_once() {
	cache_traction();
}

void vehicle_multipliers_menu::feature_update() {
	if (menu::player::get_local_player().m_in_vehicle) {
		if (m_vars.m_torque != 1.f) {
			uint64_t address = rage::engine::get_entity_address(menu::player::get_local_player().m_vehicle);
			if (address) {
				*(float*)(address + 0x1360) = m_vars.m_torque;
			}
		}

		if (m_vars.m_headlight != 1.f) {
			native::set_vehicle_light_multiplier(menu::player::get_local_player().m_vehicle, m_vars.m_headlight);
		}
	}
}

vehicle_multipliers_menu* g_instance;
vehicle_multipliers_menu* vehicle_multipliers_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_multipliers_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}