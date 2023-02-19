#include "vehicle_seats_edit.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle_seats.h"

using namespace vehicle::seats::edit::vars;

namespace vehicle::seats::edit::vars {
	variables m_vars;

	void click() {
		if (menu::player::get_local_player().m_in_vehicle) {
			native::clear_ped_tasks_immediately(native::get_ped_in_vehicle_seat(menu::player::get_local_player().m_vehicle, m_vars.m_seat, 0));
		}
	}
}

void vehicle_seats_edit_menu::load() {
	set_name("Seats");
	set_parent<vehicle_seats_menu>();

	add_option(button_option("Kick")
		.add_translate()
		.add_click(click));
}

void vehicle_seats_edit_menu::update() {}

void vehicle_seats_edit_menu::update_once() {}

void vehicle_seats_edit_menu::feature_update() {}

vehicle_seats_edit_menu* g_instance;
vehicle_seats_edit_menu* vehicle_seats_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_seats_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}