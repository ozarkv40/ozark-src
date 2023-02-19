#include "vehicle_customs_wheels.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_customs.h"
#include "wheels/vehicle_customs_wheels_type.h"
#include "wheels/vehicle_customs_wheels_color.h"
#include "wheels/vehicle_customs_wheels_tires.h"

using namespace vehicle::customs::wheels::vars;

namespace vehicle::customs::wheels::vars {
	variables m_vars;
}

void vehicle_customs_wheels_menu::load() {
	set_name("Wheels");
	set_parent<vehicle_customs_menu>();

	add_option(submenu_option("Wheel Type")
		.add_translate()
		.add_submenu<vehicle_customs_wheels_type_menu>());

	add_option(submenu_option("Wheel Color")
		.add_translate()
		.add_submenu<vehicle_customs_wheels_color_menu>());

	add_option(submenu_option("Tires")
		.add_translate()
		.add_submenu<vehicle_customs_wheels_tires_menu>());
}

void vehicle_customs_wheels_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	vehicle::customs::vars::scripts::draw_vehicle_stats(menu::player::get_local_player().m_vehicle);
}

void vehicle_customs_wheels_menu::update_once() {
	if (m_vars.m_update_cache) {
		m_vars.m_update_cache = false;

		int perl = 0;
		int cur = 0;
		native::get_vehicle_extra_colours(menu::player::get_local_player().m_vehicle, &perl, &cur);
		native::set_vehicle_extra_colours(menu::player::get_local_player().m_vehicle, perl, m_vars.m_paint_index);
	}

	int perl = 0;
	native::get_vehicle_extra_colours(menu::player::get_local_player().m_vehicle, &perl, &m_vars.m_paint_index);
}

void vehicle_customs_wheels_menu::feature_update() {}

vehicle_customs_wheels_menu* g_instance;
vehicle_customs_wheels_menu* vehicle_customs_wheels_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_customs_wheels_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}