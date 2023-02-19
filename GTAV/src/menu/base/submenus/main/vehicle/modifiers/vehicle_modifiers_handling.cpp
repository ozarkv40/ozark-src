#include "vehicle_modifiers_handling.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_modifiers.h"
#include "handling/vehicle_modifiers_handling_main.h"
#include "handling/vehicle_modifiers_handling_load.h"

using namespace vehicle::modifiers::handling::vars;

namespace vehicle::modifiers::handling::vars {
	variables m_vars;
}

void vehicle_modifiers_handling_menu::load() {
	set_name("Handling");
	set_parent<vehicle_modifiers_menu>();

	add_string("Boat Handling");
	add_string("Bike Handling");
	add_string("Flying Handling");
	add_string("Save and Load");
	add_string("Main Handling");
}

void vehicle_modifiers_handling_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous(true);
		return;
	}
}

void vehicle_modifiers_handling_menu::update_once() {
	m_vars.m_in_boat = false;
	m_vars.m_in_bike = false;
	m_vars.m_in_flying = false;

	if (menu::player::get_local_player().m_in_vehicle) {
		uint32_t model = native::get_entity_model(menu::player::get_local_player().m_vehicle);
		m_vars.m_in_boat = native::is_this_model_a_boat(model) || native::is_this_model_an_emergency_boat(model);
		m_vars.m_in_bike = native::is_this_model_a_bicycle(model) || native::is_this_model_a_bike(model);
		m_vars.m_in_flying = native::is_this_model_a_plane(model) || native::is_this_model_a_heli(model);
	}

	clear_options(0);

	add_option(submenu_option(get_string("Save and Load"))
		.add_submenu<vehicle_modifiers_handling_load_menu>());

	add_option(submenu_option(get_string("Main Handling"))
		.add_submenu<vehicle_modifiers_handling_main_menu>()
		.add_click([] { vehicle::modifiers::handling::main::vars::m_vars.m_type = 0; }));

	add_option(submenu_option(get_string("Boat Handling"))
		.add_submenu<vehicle_modifiers_handling_main_menu>()
		.add_click([] { vehicle::modifiers::handling::main::vars::m_vars.m_type = 1; })
		.add_requirement([] { return m_vars.m_in_boat; }));

	add_option(submenu_option(get_string("Bike Handling"))
		.add_submenu<vehicle_modifiers_handling_main_menu>()
		.add_click([] { vehicle::modifiers::handling::main::vars::m_vars.m_type = 2; })
		.add_requirement([] { return m_vars.m_in_bike; }));

	add_option(submenu_option(get_string("Flying Handling"))
		.add_submenu<vehicle_modifiers_handling_main_menu>()
		.add_click([] { vehicle::modifiers::handling::main::vars::m_vars.m_type = 3; })
		.add_requirement([] { return m_vars.m_in_flying; }));

	add_option(button_option("~c~" + get_string("Boat Handling"))
		.add_requirement([] { return !m_vars.m_in_boat; }));

	add_option(button_option("~c~" + get_string("Bike Handling"))
		.add_requirement([] { return !m_vars.m_in_bike; }));

	add_option(button_option("~c~" + get_string("Flying Handling"))
		.add_requirement([] { return !m_vars.m_in_flying; }));
}

void vehicle_modifiers_handling_menu::feature_update() {}

vehicle_modifiers_handling_menu* g_instance;
vehicle_modifiers_handling_menu* vehicle_modifiers_handling_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_modifiers_handling_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}