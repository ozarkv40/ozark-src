#include "vehicle_customs_horn.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_customs.h"
#include "vehicle_customs_lsc.h"

using namespace vehicle::customs::horn::vars;

namespace vehicle::customs::horn::vars {
	variables m_vars;
}

void vehicle_customs_horn_menu::load() {
	set_name("Horn");
	set_parent<vehicle_customs_menu>();

	add_option(submenu_option("Standard")
		.add_translate()
		.add_submenu<vehicle_customs_lsc_menu>()
		.add_click([] {
			vehicle::customs::vars::cache_vehicle_stats();
			vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_HORN_STANDARD;
			vehicle::customs::lsc::vars::m_vars.m_value = &vehicle::customs::vars::m_vars.m_cached_stats.m_left_fender;
		}));

	add_option(submenu_option("Musical")
		.add_translate()
		.add_submenu<vehicle_customs_lsc_menu>()
		.add_click([] {
			vehicle::customs::vars::cache_vehicle_stats();
			vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_HORN_MUSICAL;
			vehicle::customs::lsc::vars::m_vars.m_value = &vehicle::customs::vars::m_vars.m_cached_stats.m_left_fender;
		}));

	add_option(submenu_option("Loop")
		.add_translate()
		.add_submenu<vehicle_customs_lsc_menu>()
		.add_click([] {
			vehicle::customs::vars::cache_vehicle_stats();
			vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_HORN_LOOP;
			vehicle::customs::lsc::vars::m_vars.m_value = &vehicle::customs::vars::m_vars.m_cached_stats.m_left_fender;
		}));
}

void vehicle_customs_horn_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	vehicle::customs::vars::scripts::draw_vehicle_stats(menu::player::get_local_player().m_vehicle);
}

void vehicle_customs_horn_menu::update_once() {
	native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
	native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_HORNS, vehicle::customs::vars::m_vars.m_cached_stats.m_horn, false);
}

void vehicle_customs_horn_menu::feature_update() {}

vehicle_customs_horn_menu* g_instance;
vehicle_customs_horn_menu* vehicle_customs_horn_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_customs_horn_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}