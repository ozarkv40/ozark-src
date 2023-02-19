#include "vehicle_customs_fender.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_customs.h"
#include "vehicle_customs_lsc.h"

using namespace vehicle::customs::fender::vars;

namespace vehicle::customs::fender::vars {
	variables m_vars;
}

void vehicle_customs_fender_menu::load() {
	set_name("Fenders");
	set_parent<vehicle_customs_menu>();

	add_string("Left Fender");
	add_string("Right Bumper");
}

void vehicle_customs_fender_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	vehicle::customs::vars::scripts::draw_vehicle_stats(menu::player::get_local_player().m_vehicle);
}

void vehicle_customs_fender_menu::update_once() {
	clear_options(0);

	native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
	native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FENDER, vehicle::customs::vars::m_vars.m_cached_stats.m_left_fender, false);
	native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_RIGHTFENDER, vehicle::customs::vars::m_vars.m_cached_stats.m_right_fender, false);

	if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FENDER)) {
		add_option(submenu_option(get_string("Left Fender"))
			.add_submenu<vehicle_customs_lsc_menu>()
			.add_click([] {
				vehicle::customs::vars::cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_FENDER;
				vehicle::customs::lsc::vars::m_vars.m_value = &vehicle::customs::vars::m_vars.m_cached_stats.m_left_fender;
			}));
	}

	if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_RIGHTFENDER)) {
		add_option(submenu_option(get_string("Right Fender"))
			.add_submenu<vehicle_customs_lsc_menu>()
			.add_click([] {
				vehicle::customs::vars::cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_RIGHTFENDER;
				vehicle::customs::lsc::vars::m_vars.m_value = &vehicle::customs::vars::m_vars.m_cached_stats.m_right_fender;
			}));
	}
}

void vehicle_customs_fender_menu::feature_update() {}

vehicle_customs_fender_menu* g_instance;
vehicle_customs_fender_menu* vehicle_customs_fender_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_customs_fender_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}