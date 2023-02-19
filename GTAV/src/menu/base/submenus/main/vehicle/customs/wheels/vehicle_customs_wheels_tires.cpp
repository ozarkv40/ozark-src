#include "vehicle_customs_wheels_tires.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_customs_wheels.h"
#include "../../vehicle_customs.h"
#include "vehicle_customs_wheels_tires_edit.h"

using namespace vehicle::customs::wheels::tires::vars;

namespace vehicle::customs::wheels::tires::vars {
	variables m_vars;
}

void vehicle_customs_wheels_tires_menu::load() {
	set_name("Tires");
	set_parent<vehicle_customs_wheels_menu>();

	add_option(submenu_option("Tire Design")
		.add_translate()
		.add_submenu<vehicle_customs_wheels_tires_edit_menu>()
		.add_click([] { vehicle::customs::wheels::tires::edit::vars::m_vars.m_type = 1; }));

	add_option(submenu_option("Tire Enhancements")
		.add_translate()
		.add_submenu<vehicle_customs_wheels_tires_edit_menu>()
		.add_click([] { vehicle::customs::wheels::tires::edit::vars::m_vars.m_type = 2; }));

	add_option(submenu_option("Tire Smoke")
		.add_translate()
		.add_submenu<vehicle_customs_wheels_tires_edit_menu>()
		.add_click([] { vehicle::customs::wheels::tires::edit::vars::m_vars.m_type = 3; }));
}

void vehicle_customs_wheels_tires_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	vehicle::customs::vars::scripts::draw_vehicle_stats(menu::player::get_local_player().m_vehicle);
}

void vehicle_customs_wheels_tires_menu::update_once() {
	if (m_vars.m_update_cache) {
		m_vars.m_update_cache = false;

		native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
		native::set_vehicle_tyres_low_grip(menu::player::get_local_player().m_vehicle, m_vars.m_tires_low_grip);
		native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS, native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS), m_vars.m_custom_tires);
		native::toggle_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_TIRESMOKE, m_vars.m_tire_smoke);
		native::set_vehicle_tyre_smoke_color(menu::player::get_local_player().m_vehicle, m_vars.m_tire_smoke_color.r, m_vars.m_tire_smoke_color.g, m_vars.m_tire_smoke_color.b);
	}

	m_vars.m_tires_low_grip = native::get_vehicle_tyres_are_low_grip(menu::player::get_local_player().m_vehicle);
	m_vars.m_custom_tires = native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);
	m_vars.m_tire_smoke = native::is_toggle_mod_on(menu::player::get_local_player().m_vehicle, MOD_TIRESMOKE);
	native::get_vehicle_tyre_smoke_color(menu::player::get_local_player().m_vehicle, &m_vars.m_tire_smoke_color.r, &m_vars.m_tire_smoke_color.g, &m_vars.m_tire_smoke_color.b);
}

void vehicle_customs_wheels_tires_menu::feature_update() {}

vehicle_customs_wheels_tires_menu* g_instance;
vehicle_customs_wheels_tires_menu* vehicle_customs_wheels_tires_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_customs_wheels_tires_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}