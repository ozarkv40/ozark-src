#include "vehicle_customs_interior.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_customs.h"
#include "vehicle_customs_lsc.h"

using namespace vehicle::customs::interior::vars;

namespace vehicle::customs::interior::vars {
	variables m_vars;
}

void vehicle_customs_interior_menu::load() {
	set_name("Benny's");
	set_parent<vehicle_customs_menu>();

	add_string("Audio Install");
	add_string("Dash");
	add_string("Dials");
	add_string("Doors");
	add_string("Ornaments");
	add_string("Seats");
	add_string("Shifter");
	add_string("Steering Wheels");
}

void vehicle_customs_interior_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	vehicle::customs::vars::scripts::draw_vehicle_stats(menu::player::get_local_player().m_vehicle);
}

void vehicle_customs_interior_menu::update_once() {
	clear_options(0);

	if (m_vars.m_update_cache) {
		m_vars.m_update_cache = false;

		native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_DASHBOARD, vehicle::customs::vars::m_vars.m_cached_stats.m_bennys_interior_design, false);
		native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_DIAL, vehicle::customs::vars::m_vars.m_cached_stats.m_bennys_dials, false);
		native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_DOOR_SPEAKER, vehicle::customs::vars::m_vars.m_cached_stats.m_bennys_doors, false);
		native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SEATS, vehicle::customs::vars::m_vars.m_cached_stats.m_bennys_seats, false);
		native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_STEERINGWHEEL, vehicle::customs::vars::m_vars.m_cached_stats.m_bennys_steering_wheel, false);
		native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_ORNAMENTS, vehicle::customs::vars::m_vars.m_cached_stats.m_bennys_ornaments, false);
		native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SHIFTER_LEAVERS, vehicle::customs::vars::m_vars.m_cached_stats.m_bennys_shifter, false);
		native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_SPEAKERS, vehicle::customs::vars::m_vars.m_cached_stats.m_bennys_audio_install, false);
	}

	if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_SPEAKERS)) {
		add_option(submenu_option(vehicle::customs::vars::get_vehicle_mod_name(MOD_SPEAKERS, get_string("Audio Install")))
			.add_submenu<vehicle_customs_lsc_menu>()
			.add_click([] {
				vehicle::customs::vars::cache_vehicle_stats();
				vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_SPEAKERS;
				vehicle::customs::lsc::vars::m_vars.m_value = &vehicle::customs::vars::m_vars.m_cached_stats.m_bennys_audio_install;
			}));
	}

	if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_DASHBOARD)) {
		add_option(submenu_option(vehicle::customs::vars::get_vehicle_mod_name(MOD_DASHBOARD, get_string("Dash")))
			.add_submenu<vehicle_customs_lsc_menu>()
			.add_click([] {
			vehicle::customs::vars::cache_vehicle_stats();
			vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_DASHBOARD;
			vehicle::customs::lsc::vars::m_vars.m_value = &vehicle::customs::vars::m_vars.m_cached_stats.m_bennys_interior_design;
		}));
	}

	if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_DIAL)) {
		add_option(submenu_option(vehicle::customs::vars::get_vehicle_mod_name(MOD_DIAL, get_string("Dials")))
			.add_submenu<vehicle_customs_lsc_menu>()
			.add_click([] {
			vehicle::customs::vars::cache_vehicle_stats();
			vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_DIAL;
			vehicle::customs::lsc::vars::m_vars.m_value = &vehicle::customs::vars::m_vars.m_cached_stats.m_bennys_dials;
		}));
	}

	if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_DOOR_SPEAKER)) {
		add_option(submenu_option(vehicle::customs::vars::get_vehicle_mod_name(MOD_DOOR_SPEAKER, get_string("Doors")))
			.add_submenu<vehicle_customs_lsc_menu>()
			.add_click([] {
			vehicle::customs::vars::cache_vehicle_stats();
			vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_DOOR_SPEAKER;
			vehicle::customs::lsc::vars::m_vars.m_value = &vehicle::customs::vars::m_vars.m_cached_stats.m_bennys_doors;
		}));
	}

	if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_ORNAMENTS)) {
		add_option(submenu_option(vehicle::customs::vars::get_vehicle_mod_name(MOD_ORNAMENTS, get_string("Ornaments")))
			.add_submenu<vehicle_customs_lsc_menu>()
			.add_click([] {
			vehicle::customs::vars::cache_vehicle_stats();
			vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_ORNAMENTS;
			vehicle::customs::lsc::vars::m_vars.m_value = &vehicle::customs::vars::m_vars.m_cached_stats.m_bennys_ornaments;
		}));
	}

	if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_SEATS)) {
		add_option(submenu_option(vehicle::customs::vars::get_vehicle_mod_name(MOD_SEATS, get_string("Seats")))
			.add_submenu<vehicle_customs_lsc_menu>()
			.add_click([] {
			vehicle::customs::vars::cache_vehicle_stats();
			vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_SEATS;
			vehicle::customs::lsc::vars::m_vars.m_value = &vehicle::customs::vars::m_vars.m_cached_stats.m_bennys_seats;
		}));
	}

	if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_SHIFTER_LEAVERS)) {
		add_option(submenu_option(vehicle::customs::vars::get_vehicle_mod_name(MOD_SHIFTER_LEAVERS, get_string("Shifter")))
			.add_submenu<vehicle_customs_lsc_menu>()
			.add_click([] {
			vehicle::customs::vars::cache_vehicle_stats();
			vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_SHIFTER_LEAVERS;
			vehicle::customs::lsc::vars::m_vars.m_value = &vehicle::customs::vars::m_vars.m_cached_stats.m_bennys_shifter;
		}));
	}

	if (native::get_num_vehicle_mods(menu::player::get_local_player().m_vehicle, MOD_STEERINGWHEEL)) {
		add_option(submenu_option(vehicle::customs::vars::get_vehicle_mod_name(MOD_STEERINGWHEEL, get_string("Steering Wheels")))
			.add_submenu<vehicle_customs_lsc_menu>()
			.add_click([] {
			vehicle::customs::vars::cache_vehicle_stats();
			vehicle::customs::lsc::vars::m_vars.m_mod_type = MOD_STEERINGWHEEL;
			vehicle::customs::lsc::vars::m_vars.m_value = &vehicle::customs::vars::m_vars.m_cached_stats.m_bennys_steering_wheel;
		}));
	}
}

void vehicle_customs_interior_menu::feature_update() {}

vehicle_customs_interior_menu* g_instance;
vehicle_customs_interior_menu* vehicle_customs_interior_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_customs_interior_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}