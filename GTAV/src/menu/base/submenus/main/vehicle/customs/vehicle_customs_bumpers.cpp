#include "vehicle_customs_bumpers.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_customs.h"
#include "vehicle_customs_lsc.h"

using namespace vehicle::customs::bumper::vars;

namespace vehicle::customs::bumper::vars {
	variables m_vars;
}

void vehicle_customs_bumper_menu::load() {
	set_name("Bumpers");
	set_parent<vehicle_customs_menu>();

	add_string("Front Bumper");
	add_string("Rear Bumper");
}

void vehicle_customs_bumper_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	vehicle::customs::vars::scripts::draw_vehicle_stats(menu::player::get_local_player().m_vehicle);
}

void vehicle_customs_bumper_menu::update_once() {
	clear_options(0);

	native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
	native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTBUMPER, vehicle::customs::vars::m_vars.m_cached_stats.m_front_bumper, false);
	native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_REARBUMPER, vehicle::customs::vars::m_vars.m_cached_stats.m_rear_bumper, false);

	if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_FRONTBUMPER)) {
		add_option(submenu_option(get_string("Front Bumper"))
			.add_submenu<vehicle_customs_lsc_menu>()
			.add_click([] {
				vehicle::customs::vars::cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_FRONTBUMPER;
				vehicle::customs::lsc::vars::m_vars.m_value = &vehicle::customs::vars::m_vars.m_cached_stats.m_front_bumper;
			}));
	}

	if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_REARBUMPER)) {
		add_option(submenu_option(get_string("Rear Bumper"))
			.add_submenu<vehicle_customs_lsc_menu>()
			.add_click([] {
				vehicle::customs::vars::cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_REARBUMPER;
				vehicle::customs::lsc::vars::m_vars.m_value = &vehicle::customs::vars::m_vars.m_cached_stats.m_rear_bumper;
			}));
	}
}

void vehicle_customs_bumper_menu::feature_update() {}

vehicle_customs_bumper_menu* g_instance;
vehicle_customs_bumper_menu* vehicle_customs_bumper_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_customs_bumper_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}