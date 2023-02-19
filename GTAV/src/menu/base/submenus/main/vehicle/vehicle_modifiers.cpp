#include "vehicle_modifiers.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle.h"
#include "rage/engine.h"
#include "modifiers/vehicle_modifiers_handling.h"

using namespace vehicle::modifiers::vars;

namespace vehicle::modifiers::vars {
	variables m_vars;

	void set_suspension() {
		if (menu::player::get_local_player().m_in_vehicle) {
			uint64_t address = rage::engine::get_entity_address(menu::player::get_local_player().m_vehicle);
			if (address) {
				if (*(uint32_t*)(address + 0xBE8) <= 10) {
					*(float*)(address + 0x19DC) = -m_vars.m_suspension;
				}
			}
		}
	}

	void set_tire_scale() {
		if (global::vars::g_ped_factory) {
			if (global::vars::g_ped_factory->m_local_ped) {
				if (global::vars::g_ped_factory->m_local_ped->m_vehicle) {
					rage::types::vehicle* veh = global::vars::g_ped_factory->m_local_ped->m_vehicle;
					if (veh->m_vehicle_draw_handler) {
						if (veh->m_vehicle_draw_handler->m_vehicle_stream_render) {
							veh->m_vehicle_draw_handler->m_vehicle_stream_render->m_tire_size = m_vars.m_tire_size;
						}
					}
				}
			}
		}
	}

	void set_tire_width() {
		if (global::vars::g_ped_factory) {
			if (global::vars::g_ped_factory->m_local_ped) {
				if (global::vars::g_ped_factory->m_local_ped->m_vehicle) {
					rage::types::vehicle* veh = global::vars::g_ped_factory->m_local_ped->m_vehicle;
					if (veh->m_vehicle_draw_handler) {
						if (veh->m_vehicle_draw_handler->m_vehicle_stream_render) {
							veh->m_vehicle_draw_handler->m_vehicle_stream_render->m_tire_width = m_vars.m_tire_width;
						}
					}
				}
			}
		}
	}
}

void vehicle_modifiers_menu::load() {
	set_name("Modifiers");
	set_parent<vehicle_menu>();

	add_string("Wheel Scale");
	add_string("Wheel Width");
	add_string("Handling");
	add_string("Advanced Suspension");
}

void vehicle_modifiers_menu::update() {
	m_vars.m_has_suspension = false;
	m_vars.m_has_custom_wheels = false;

	if (menu::player::get_local_player().m_in_vehicle) {
		uint64_t address = rage::engine::get_entity_address(menu::player::get_local_player().m_vehicle);
		if (address) {
			if (*(uint32_t*)(address + 0xBE8) <= 10) {
				m_vars.m_has_suspension = true;
				m_vars.m_suspension = -*(float*)(address + 0x19DC);
			}

			if (global::vars::g_ped_factory) {
				if (global::vars::g_ped_factory->m_local_ped) {
					if (global::vars::g_ped_factory->m_local_ped->m_vehicle) {
						rage::types::vehicle* veh = global::vars::g_ped_factory->m_local_ped->m_vehicle;
						if (veh->m_vehicle_draw_handler) {
							if (veh->m_vehicle_draw_handler->m_vehicle_stream_render) {
								m_vars.m_has_custom_wheels = true;
								m_vars.m_tire_size = veh->m_vehicle_draw_handler->m_vehicle_stream_render->m_tire_size;
								m_vars.m_tire_width = veh->m_vehicle_draw_handler->m_vehicle_stream_render->m_tire_width;
							}
						}
					}
				}
			}
		}
	}
}

void vehicle_modifiers_menu::update_once() {
	clear_options(0);

	add_option(submenu_option(get_string("Handling"))
		.add_submenu<vehicle_modifiers_handling_menu>()
		.add_requirement([] { return menu::player::get_local_player().m_in_vehicle; }));

	add_option(number_option<float>(SCROLL, get_string("Advanced Suspension"))
		.add_number(m_vars.m_suspension, "%.2f", 0.01f).add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max()
		.add_click(set_suspension)
		.add_requirement([] { return m_vars.m_has_suspension; }));

	add_option(number_option<float>(SCROLL, get_string("Wheel Scale"))
		.add_number(m_vars.m_tire_size, "%.2f", 0.01f).add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max()
		.add_click(set_tire_scale)
		.add_requirement([] { return m_vars.m_has_custom_wheels; }));

	add_option(number_option<float>(SCROLL, get_string("Wheel Width"))
		.add_number(m_vars.m_tire_width, "%.2f", 0.01f).add_min(-100.f).add_max(100.f).set_scroll_speed(10).show_max()
		.add_click(set_tire_width)
		.add_requirement([] { return m_vars.m_has_custom_wheels; }));

	add_option(button_option("~c~" + get_string("Handling"))
		.add_requirement([] { return !menu::player::get_local_player().m_in_vehicle; }));

	add_option(button_option("~c~" + get_string("Wheel Scale"))
		.add_requirement([] { return !m_vars.m_has_custom_wheels; })
		.add_tooltip("You need custom tires to edit wheels"));

	add_option(button_option("~c~" + get_string("Wheel Width"))
		.add_requirement([] { return !m_vars.m_has_custom_wheels; })
		.add_tooltip("You need custom tires to edit wheels"));
}

void vehicle_modifiers_menu::feature_update() {}

vehicle_modifiers_menu* g_instance;
vehicle_modifiers_menu* vehicle_modifiers_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_modifiers_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}