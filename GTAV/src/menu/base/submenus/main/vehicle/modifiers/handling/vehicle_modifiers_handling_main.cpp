#include "vehicle_modifiers_handling_main.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_modifiers_handling.h"
#include "vehicle_modifiers_handling_attr.h"
#include "vehicle_modifiers_handling_boat.h"
#include "vehicle_modifiers_handling_bike.h"
#include "vehicle_modifiers_handling_flying.h"

using namespace vehicle::modifiers::handling::main::vars;

namespace vehicle::modifiers::handling::main::vars {
	variables m_vars;
}

void vehicle_modifiers_handling_main_menu::load() {
	set_name("Handling");
	set_parent<vehicle_modifiers_handling_menu>();

	add_string("Physical Attributes");
	add_string("Transmission Attributes");
	add_string("Wheel Traction Attributes");
	add_string("Suspension Attributes");
	add_string("Damage Attributes");
	add_string("Miscellaneous Attributes");

	add_string("Aquaplane Attributes");
	add_string("Rudder Attributes");
	add_string("Resistance Attributes");

	add_string("Balance Attributes");
	add_string("Friction Attributes");

	add_string("Thrust Attributes");
	add_string("Movement Attributes");
	add_string("Turbulence Attributes");
	add_string("Gear Attributes");
	add_string("Ground Attributes");
}

void vehicle_modifiers_handling_main_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous(true);
		return;
	}
}

void vehicle_modifiers_handling_main_menu::update_once() {
	clear_options(0);

	/* Vehicle Handling */
	if (m_vars.m_type == 0) {
		add_option(submenu_option(get_string("Physical Attributes"))
			.add_submenu<vehicle_modifiers_handling_attr_menu>()
			.add_click([] { vehicle::modifiers::handling::attr::vars::m_vars.m_type = 0; }));

		add_option(submenu_option(get_string("Transmission Attributes"))
			.add_submenu<vehicle_modifiers_handling_attr_menu>()
			.add_click([] { vehicle::modifiers::handling::attr::vars::m_vars.m_type = 1; }));

		add_option(submenu_option(get_string("Wheel Traction Attributes"))
			.add_submenu<vehicle_modifiers_handling_attr_menu>()
			.add_click([] { vehicle::modifiers::handling::attr::vars::m_vars.m_type = 2; }));

		add_option(submenu_option(get_string("Suspension Attributes"))
			.add_submenu<vehicle_modifiers_handling_attr_menu>()
			.add_click([] { vehicle::modifiers::handling::attr::vars::m_vars.m_type = 3; }));

		add_option(submenu_option(get_string("Damage Attributes"))
			.add_submenu<vehicle_modifiers_handling_attr_menu>()
			.add_click([] { vehicle::modifiers::handling::attr::vars::m_vars.m_type = 4; }));

		add_option(submenu_option(get_string("Miscellaneous Attributes"))
			.add_submenu<vehicle_modifiers_handling_attr_menu>()
			.add_click([] { vehicle::modifiers::handling::attr::vars::m_vars.m_type = 5; }));
	}

	/* Boat */
	if (m_vars.m_type == 1) {
		add_option(submenu_option(get_string("Physical Attributes"))
			.add_submenu<vehicle_modifiers_handling_boat_menu>()
			.add_click([] { vehicle::modifiers::handling::boat::vars::m_vars.m_type = 0; }));

		add_option(submenu_option(get_string("Aquaplane Attributes"))
			.add_submenu<vehicle_modifiers_handling_boat_menu>()
			.add_click([] { vehicle::modifiers::handling::boat::vars::m_vars.m_type = 1; }));

		add_option(submenu_option(get_string("Rudder Attributes"))
			.add_submenu<vehicle_modifiers_handling_boat_menu>()
			.add_click([] { vehicle::modifiers::handling::boat::vars::m_vars.m_type = 2; }));

		add_option(submenu_option(get_string("Resistance Attributes"))
			.add_submenu<vehicle_modifiers_handling_boat_menu>()
			.add_click([] { vehicle::modifiers::handling::boat::vars::m_vars.m_type = 3; }));

		add_option(submenu_option(get_string("Miscellaneous Attributes"))
			.add_submenu<vehicle_modifiers_handling_boat_menu>()
			.add_click([] { vehicle::modifiers::handling::boat::vars::m_vars.m_type = 4; }));
	}

	/* Bike */
	if (m_vars.m_type == 2) {
		add_option(submenu_option(get_string("Physical Attributes"))
			.add_submenu<vehicle_modifiers_handling_bike_menu>()
			.add_click([] { vehicle::modifiers::handling::bike::vars::m_vars.m_type = 0; }));

		add_option(submenu_option(get_string("Balance Attributes"))
			.add_submenu<vehicle_modifiers_handling_bike_menu>()
			.add_click([] { vehicle::modifiers::handling::bike::vars::m_vars.m_type = 1; }));

		add_option(submenu_option(get_string("Friction Attributes"))
			.add_submenu<vehicle_modifiers_handling_bike_menu>()
			.add_click([] { vehicle::modifiers::handling::bike::vars::m_vars.m_type = 2; }));
	}

	/* Flying */
	if (m_vars.m_type == 3) {
		add_option(submenu_option(get_string("Thrust Attributes"))
			.add_submenu<vehicle_modifiers_handling_flying_menu>()
			.add_click([] { vehicle::modifiers::handling::flying::vars::m_vars.m_type = 0; }));

		add_option(submenu_option(get_string("Movement Attributes"))
			.add_submenu<vehicle_modifiers_handling_flying_menu>()
			.add_click([] { vehicle::modifiers::handling::flying::vars::m_vars.m_type = 1; }));

		add_option(submenu_option(get_string("Resistance Attributes"))
			.add_submenu<vehicle_modifiers_handling_flying_menu>()
			.add_click([] { vehicle::modifiers::handling::flying::vars::m_vars.m_type = 2; }));

		add_option(submenu_option(get_string("Turbulence Attributes"))
			.add_submenu<vehicle_modifiers_handling_flying_menu>()
			.add_click([] { vehicle::modifiers::handling::flying::vars::m_vars.m_type = 3; }));

		add_option(submenu_option(get_string("Gear Attributes"))
			.add_submenu<vehicle_modifiers_handling_flying_menu>()
			.add_click([] { vehicle::modifiers::handling::flying::vars::m_vars.m_type = 4; }));

		add_option(submenu_option(get_string("Ground Attributes"))
			.add_submenu<vehicle_modifiers_handling_flying_menu>()
			.add_click([] { vehicle::modifiers::handling::flying::vars::m_vars.m_type = 5; }));

		add_option(submenu_option(get_string("Miscellaneous Attributes"))
			.add_submenu<vehicle_modifiers_handling_flying_menu>()
			.add_click([] { vehicle::modifiers::handling::flying::vars::m_vars.m_type = 6; }));
	}
}

void vehicle_modifiers_handling_main_menu::feature_update() {}

vehicle_modifiers_handling_main_menu* g_instance;
vehicle_modifiers_handling_main_menu* vehicle_modifiers_handling_main_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_modifiers_handling_main_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}