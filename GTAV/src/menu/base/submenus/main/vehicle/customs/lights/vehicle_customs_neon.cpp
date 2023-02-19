#include "vehicle_customs_neon.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_customs_lights.h"
#include "../../vehicle_customs.h"
#include "../vehicle_customs_lsc.h"
#include "neon/vehicle_customs_neon_color.h"

using namespace vehicle::customs::neon::vars;

namespace vehicle::customs::neon::vars {
	variables m_vars;
}

void vehicle_customs_neon_menu::load() {
	set_name("Neon Kits");
	set_parent<vehicle_customs_lights_menu>();

	add_option(submenu_option("Neon Layout")
		.add_translate()
		.add_submenu<vehicle_customs_lsc_menu>()
		.add_click([] { vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_NEON; }));

	add_option(submenu_option("Neon Color")
		.add_translate()
		.add_submenu<vehicle_customs_neon_color_menu>());
}

void vehicle_customs_neon_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	vehicle::customs::vars::scripts::draw_vehicle_stats(menu::player::get_local_player().m_vehicle);
}

void vehicle_customs_neon_menu::update_once() {
	for (int i = 0; i < 4; i++) {
		native::set_vehicle_neon_light_enabled(menu::player::get_local_player().m_vehicle, i, vehicle::customs::vars::m_vars.m_cached_stats.m_neon[i]);
	}

	native::set_vehicle_neon_lights_colour(menu::player::get_local_player().m_vehicle, vehicle::customs::vars::m_vars.m_cached_stats.m_neon_color.r, vehicle::customs::vars::m_vars.m_cached_stats.m_neon_color.g, vehicle::customs::vars::m_vars.m_cached_stats.m_neon_color.b);
}

void vehicle_customs_neon_menu::feature_update() {}

vehicle_customs_neon_menu* g_instance;
vehicle_customs_neon_menu* vehicle_customs_neon_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_customs_neon_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}