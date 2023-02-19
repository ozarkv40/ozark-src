#include "vehicle_customs_lights.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_customs.h"
#include "vehicle_customs_lsc.h"
#include "lights/vehicle_customs_neon.h"

using namespace vehicle::customs::lights::vars;

namespace vehicle::customs::lights::vars {
	variables m_vars;
}

void vehicle_customs_lights_menu::load() {
	set_name("Lights");
	set_parent<vehicle_customs_menu>();

	add_option(submenu_option("Headlights")
		.add_translate()
		.add_submenu<vehicle_customs_lsc_menu>()
		.add_click([] {
			vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_XENONLIGHTS;
			vehicle::customs::lsc::vars::m_vars.m_value = &vehicle::customs::vars::m_vars.m_cached_stats.m_lights;
		}));

	add_option(submenu_option("Neon Kits")
		.add_translate()
		.add_submenu<vehicle_customs_neon_menu>()
		.add_requirement([] { return native::is_this_model_a_car(native::get_entity_model(menu::player::get_local_player().m_vehicle)); }));
}

void vehicle_customs_lights_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	vehicle::customs::vars::scripts::draw_vehicle_stats(menu::player::get_local_player().m_vehicle);
}

void vehicle_customs_lights_menu::update_once() {
	native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
	native::toggle_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_XENONLIGHTS, vehicle::customs::vars::m_vars.m_cached_stats.m_lights);
}

void vehicle_customs_lights_menu::feature_update() {}

vehicle_customs_lights_menu* g_instance;
vehicle_customs_lights_menu* vehicle_customs_lights_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_customs_lights_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}