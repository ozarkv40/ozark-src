#include "vehicle_customs_wheels_type.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_customs_wheels.h"
#include "../../vehicle_customs.h"
#include "vehicle_customs_wheels_type_edit.h"

using namespace vehicle::customs::wheels::type::vars;

namespace vehicle::customs::wheels::type::vars {
	variables m_vars;
}

void vehicle_customs_wheels_type_menu::load() {
	set_name("Wheel Type");
	set_parent<vehicle_customs_wheels_menu>();

	add_string("Front Wheel");
	add_string("Rear Wheel");
	add_string("High End");
	add_string("Lowrider");
	add_string("Muscle");
	add_string("Offroad");
	add_string("Sport");
	add_string("SUV");
	add_string("Tuner");
	add_string("Benny's Original");
	add_string("Benny's Bespoke");
	add_string("Open Wheel");
	add_string("Street");
	add_string("Track");

	vehicle_customs_wheels_type_edit_menu::get();
}

void vehicle_customs_wheels_type_menu::update() {
	if (!menu::player::get_local_player().m_in_vehicle) {
		menu::submenu::handler::set_submenu_previous();
		return;
	}

	vehicle::customs::vars::scripts::draw_vehicle_stats(menu::player::get_local_player().m_vehicle);
	if (menu::base::get_scroll_offset() < menu::submenu::handler::get_total_options() - menu::base::get_max_options() && menu::base::get_current_option() - menu::base::get_scroll_offset() >= menu::base::get_max_options()) menu::base::set_scroll_offset(menu::base::get_scroll_offset() + 1);
}

void vehicle_customs_wheels_type_menu::update_once() {
	clear_options(0);

	if (m_vars.m_update_cache) {
		m_vars.m_update_cache = false;

		if (menu::player::get_local_player().m_in_vehicle) {
			native::set_vehicle_wheel_type(menu::player::get_local_player().m_vehicle, m_vars.m_cached_wheel_type);
			native::set_vehicle_mod_kit(menu::player::get_local_player().m_vehicle, 0);
			native::set_vehicle_mod(menu::player::get_local_player().m_vehicle, m_vars.m_mod_type, m_vars.m_cached_wheel_index, native::get_vehicle_mod_variation(menu::player::get_local_player().m_vehicle, m_vars.m_mod_type));
		}
	}

	if (native::is_this_model_a_bike(native::get_entity_model(menu::player::get_local_player().m_vehicle))) {
		add_option(submenu_option(get_string("Front Wheel"))
			.add_submenu<vehicle_customs_wheels_type_edit_menu>()
			.add_click([this] {
				vehicle_customs_wheels_type_edit_menu::get()->set_name(get_string("Front Wheel"), false, false);
				vehicle::customs::wheels::type::edit::vars::m_vars.m_wheel_type = 1;
				m_vars.m_cached_wheel_index = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);
				m_vars.m_cached_wheel_type = native::get_vehicle_wheel_type(menu::player::get_local_player().m_vehicle);
				m_vars.m_mod_type = MOD_FRONTWHEELS;
			}));

		add_option(submenu_option(get_string("Rear Wheel"))
			.add_submenu<vehicle_customs_wheels_type_edit_menu>()
			.add_click([this] {
			vehicle_customs_wheels_type_edit_menu::get()->set_name(get_string("Rear Wheel"), false, false);
				vehicle::customs::wheels::type::edit::vars::m_vars.m_wheel_type = 2;
				m_vars.m_cached_wheel_index = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_BACKWHEELS);
				m_vars.m_cached_wheel_type = native::get_vehicle_wheel_type(menu::player::get_local_player().m_vehicle);
				m_vars.m_mod_type = MOD_BACKWHEELS;
			}));
	} else {
		add_option(submenu_option(get_string("High End"))
			.add_submenu<vehicle_customs_wheels_type_edit_menu>()
			.add_click([this] {
			vehicle_customs_wheels_type_edit_menu::get()->set_name(get_string("High End"), false, false);
				vehicle::customs::wheels::type::edit::vars::m_vars.m_wheel_type = 3;
				m_vars.m_cached_wheel_index = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);
				m_vars.m_cached_wheel_type = native::get_vehicle_wheel_type(menu::player::get_local_player().m_vehicle);
				m_vars.m_mod_type = MOD_FRONTWHEELS;
			}));

		add_option(submenu_option(get_string("Lowrider"))
			.add_submenu<vehicle_customs_wheels_type_edit_menu>()
			.add_click([this] {
			vehicle_customs_wheels_type_edit_menu::get()->set_name(get_string("Lowrider"), false, false);
				vehicle::customs::wheels::type::edit::vars::m_vars.m_wheel_type = 4;
				m_vars.m_cached_wheel_index = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);
				m_vars.m_cached_wheel_type = native::get_vehicle_wheel_type(menu::player::get_local_player().m_vehicle);
				m_vars.m_mod_type = MOD_FRONTWHEELS;
			}));

		add_option(submenu_option(get_string("Muscle"))
			.add_submenu<vehicle_customs_wheels_type_edit_menu>()
			.add_click([this] {
			vehicle_customs_wheels_type_edit_menu::get()->set_name(get_string("Muscle"), false, false);
				vehicle::customs::wheels::type::edit::vars::m_vars.m_wheel_type = 5;
				m_vars.m_cached_wheel_index = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);
				m_vars.m_cached_wheel_type = native::get_vehicle_wheel_type(menu::player::get_local_player().m_vehicle);
				m_vars.m_mod_type = MOD_FRONTWHEELS;
			}));

		add_option(submenu_option(get_string("Offroad"))
			.add_submenu<vehicle_customs_wheels_type_edit_menu>()
			.add_click([this] {
			vehicle_customs_wheels_type_edit_menu::get()->set_name(get_string("Offroad"), false, false);
				vehicle::customs::wheels::type::edit::vars::m_vars.m_wheel_type = 6;
				m_vars.m_cached_wheel_index = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);
				m_vars.m_cached_wheel_type = native::get_vehicle_wheel_type(menu::player::get_local_player().m_vehicle);
				m_vars.m_mod_type = MOD_FRONTWHEELS;
			}));

		add_option(submenu_option(get_string("Sport"))
			.add_submenu<vehicle_customs_wheels_type_edit_menu>()
			.add_click([this] {
			vehicle_customs_wheels_type_edit_menu::get()->set_name(get_string("Sport"), false, false);
				vehicle::customs::wheels::type::edit::vars::m_vars.m_wheel_type = 7;
				m_vars.m_cached_wheel_index = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);
				m_vars.m_cached_wheel_type = native::get_vehicle_wheel_type(menu::player::get_local_player().m_vehicle);
				m_vars.m_mod_type = MOD_FRONTWHEELS;
			}));

		add_option(submenu_option(get_string("SUV"))
			.add_submenu<vehicle_customs_wheels_type_edit_menu>()
			.add_click([this] {
			vehicle_customs_wheels_type_edit_menu::get()->set_name(get_string("SUV"), false, false);
				vehicle::customs::wheels::type::edit::vars::m_vars.m_wheel_type = 8;
				m_vars.m_cached_wheel_index = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);
				m_vars.m_cached_wheel_type = native::get_vehicle_wheel_type(menu::player::get_local_player().m_vehicle);
				m_vars.m_mod_type = MOD_FRONTWHEELS;
			}));

		add_option(submenu_option(get_string("Tuner"))
			.add_submenu<vehicle_customs_wheels_type_edit_menu>()
			.add_click([this] {
			vehicle_customs_wheels_type_edit_menu::get()->set_name(get_string("Tuner"), false, false);
				vehicle::customs::wheels::type::edit::vars::m_vars.m_wheel_type = 9;
				m_vars.m_cached_wheel_index = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);
				m_vars.m_cached_wheel_type = native::get_vehicle_wheel_type(menu::player::get_local_player().m_vehicle);
				m_vars.m_mod_type = MOD_FRONTWHEELS;
			}));

		add_option(submenu_option(get_string("Benny's Original"))
			.add_submenu<vehicle_customs_wheels_type_edit_menu>()
			.add_click([this] {
			vehicle_customs_wheels_type_edit_menu::get()->set_name(get_string("Benny's Original"), false, false);
				vehicle::customs::wheels::type::edit::vars::m_vars.m_wheel_type = 10;
				m_vars.m_cached_wheel_index = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);
				m_vars.m_cached_wheel_type = native::get_vehicle_wheel_type(menu::player::get_local_player().m_vehicle);
				m_vars.m_mod_type = MOD_FRONTWHEELS;
			}));

		add_option(submenu_option(get_string("Benny's Bespoke"))
			.add_submenu<vehicle_customs_wheels_type_edit_menu>()
			.add_click([this] {
			vehicle_customs_wheels_type_edit_menu::get()->set_name(get_string("Benny's Bespoke"), false, false);
				vehicle::customs::wheels::type::edit::vars::m_vars.m_wheel_type = 11;
				m_vars.m_cached_wheel_index = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);
				m_vars.m_cached_wheel_type = native::get_vehicle_wheel_type(menu::player::get_local_player().m_vehicle);
				m_vars.m_mod_type = MOD_FRONTWHEELS;
			}));

		add_option(submenu_option(get_string("Open Wheel"))
			.add_submenu<vehicle_customs_wheels_type_edit_menu>()
			.add_click([this] {
			vehicle_customs_wheels_type_edit_menu::get()->set_name(get_string("Open Wheel"), false, false);
				vehicle::customs::wheels::type::edit::vars::m_vars.m_wheel_type = 12;
				m_vars.m_cached_wheel_index = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);
				m_vars.m_cached_wheel_type = native::get_vehicle_wheel_type(menu::player::get_local_player().m_vehicle);
				m_vars.m_mod_type = MOD_FRONTWHEELS;
			}));

		add_option(submenu_option(get_string("Street"))
			.add_submenu<vehicle_customs_wheels_type_edit_menu>()
			.add_click([this] {
			vehicle_customs_wheels_type_edit_menu::get()->set_name(get_string("Street"), false, false);
				vehicle::customs::wheels::type::edit::vars::m_vars.m_wheel_type = 13;
				m_vars.m_cached_wheel_index = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);
				m_vars.m_cached_wheel_type = native::get_vehicle_wheel_type(menu::player::get_local_player().m_vehicle);
				m_vars.m_mod_type = MOD_FRONTWHEELS;
			}));

		add_option(submenu_option(get_string("Track"))
			.add_submenu<vehicle_customs_wheels_type_edit_menu>()
			.add_click([this] {
				vehicle_customs_wheels_type_edit_menu::get()->set_name(get_string("Track"), false, false);
				vehicle::customs::wheels::type::edit::vars::m_vars.m_wheel_type = 14;
				m_vars.m_cached_wheel_index = native::get_vehicle_mod(menu::player::get_local_player().m_vehicle, MOD_FRONTWHEELS);
				m_vars.m_cached_wheel_type = native::get_vehicle_wheel_type(menu::player::get_local_player().m_vehicle);
				m_vars.m_mod_type = MOD_FRONTWHEELS;
			}));
	}
}

void vehicle_customs_wheels_type_menu::feature_update() {}

vehicle_customs_wheels_type_menu* g_instance;
vehicle_customs_wheels_type_menu* vehicle_customs_wheels_type_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_customs_wheels_type_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}