#include "fx_vehicle.h"
#include "menu/base/submenu_handler.h"
#include "../game_fx.h"
#include "util/memory/memory.h"

using namespace world::fx::vehicle::vars;

namespace world::fx::vehicle::vars {
	variables m_vars;
}

void fx_vehicle_menu::load() {
	set_name("Vehicle");
	set_parent<game_fx_menu>();

	m_vars.m_interior_light_color.m_color = (rage::types::ui_element_color_struct*)memory::read_instruction(global::vars::g_set_vehicle_lights + 0x45, 3, 7);
	m_vars.m_plate_light_color.m_color = (rage::types::ui_element_color_struct*)memory::read_instruction(global::vars::g_set_vehicle_lights + 0x90, 3, 7);
	m_vars.m_dash_light_color.m_color = (rage::types::ui_element_color_struct*)memory::read_instruction(global::vars::g_set_vehicle_lights + 0xa9, 3, 7);
	m_vars.m_door_light_color.m_color = (rage::types::ui_element_color_struct*)memory::read_instruction(global::vars::g_set_vehicle_lights + 0xc2, 3, 7);

	memcpy(&m_vars.m_interior_light_color.m_default_color, m_vars.m_interior_light_color.m_color, sizeof(rage::types::ui_element_color_struct));
	memcpy(&m_vars.m_plate_light_color.m_default_color, m_vars.m_plate_light_color.m_color, sizeof(rage::types::ui_element_color_struct));
	memcpy(&m_vars.m_dash_light_color.m_default_color, m_vars.m_dash_light_color.m_color, sizeof(rage::types::ui_element_color_struct));
	memcpy(&m_vars.m_door_light_color.m_default_color, m_vars.m_door_light_color.m_color, sizeof(rage::types::ui_element_color_struct));

	add_option(submenu_option("Interior Light")
		.add_translate()
		.add_submenu<fx_ui_color_menu>()
		.add_click([] {
			world::fx::ui::color::vars::m_vars.m_color = &m_vars.m_interior_light_color;
			fx_ui_color_menu::get()->set_parent<fx_vehicle_menu>();
		}));

	add_option(submenu_option("Plate Light")
		.add_translate()
		.add_submenu<fx_ui_color_menu>()
		.add_click([] {
			world::fx::ui::color::vars::m_vars.m_color = &m_vars.m_plate_light_color;
			fx_ui_color_menu::get()->set_parent<fx_vehicle_menu>();
		}));

	add_option(submenu_option("Dash Light")
		.add_translate()
		.add_submenu<fx_ui_color_menu>()
		.add_click([] {
			world::fx::ui::color::vars::m_vars.m_color = &m_vars.m_dash_light_color;
			fx_ui_color_menu::get()->set_parent<fx_vehicle_menu>();
		}));

	add_option(submenu_option("Door Light")
		.add_translate()
		.add_submenu<fx_ui_color_menu>()
		.add_click([] {
			world::fx::ui::color::vars::m_vars.m_color = &m_vars.m_door_light_color;
			fx_ui_color_menu::get()->set_parent<fx_vehicle_menu>();
		}));
}

void fx_vehicle_menu::update() {}

void fx_vehicle_menu::update_once() {}

void fx_vehicle_menu::feature_update() {
	if (m_vars.m_interior_light_color.m_rainbow_toggle) {
		m_vars.m_interior_light_color.m_rainbow.run();
		m_vars.m_interior_light_color.m_color->m_color.x = m_vars.m_interior_light_color.m_internal_color.r / 255.f;
		m_vars.m_interior_light_color.m_color->m_color.y = m_vars.m_interior_light_color.m_internal_color.g / 255.f;
		m_vars.m_interior_light_color.m_color->m_color.z = m_vars.m_interior_light_color.m_internal_color.b / 255.f;
	}

	if (m_vars.m_plate_light_color.m_rainbow_toggle) {
		m_vars.m_plate_light_color.m_rainbow.run();
		m_vars.m_plate_light_color.m_color->m_color.x = m_vars.m_plate_light_color.m_internal_color.r / 255.f;
		m_vars.m_plate_light_color.m_color->m_color.y = m_vars.m_plate_light_color.m_internal_color.g / 255.f;
		m_vars.m_plate_light_color.m_color->m_color.z = m_vars.m_plate_light_color.m_internal_color.b / 255.f;
	}

	if (m_vars.m_dash_light_color.m_rainbow_toggle) {
		m_vars.m_dash_light_color.m_rainbow.run();
		m_vars.m_dash_light_color.m_color->m_color.x = m_vars.m_dash_light_color.m_internal_color.r / 255.f;
		m_vars.m_dash_light_color.m_color->m_color.y = m_vars.m_dash_light_color.m_internal_color.g / 255.f;
		m_vars.m_dash_light_color.m_color->m_color.z = m_vars.m_dash_light_color.m_internal_color.b / 255.f;
	}

	if (m_vars.m_door_light_color.m_rainbow_toggle) {
		m_vars.m_door_light_color.m_rainbow.run();
		m_vars.m_door_light_color.m_color->m_color.x = m_vars.m_door_light_color.m_internal_color.r / 255.f;
		m_vars.m_door_light_color.m_color->m_color.y = m_vars.m_door_light_color.m_internal_color.g / 255.f;
		m_vars.m_door_light_color.m_color->m_color.z = m_vars.m_door_light_color.m_internal_color.b / 255.f;
	}
}

fx_vehicle_menu* g_instance;
fx_vehicle_menu* fx_vehicle_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new fx_vehicle_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}