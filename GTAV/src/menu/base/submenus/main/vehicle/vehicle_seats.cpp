#include "vehicle_seats.h"
#include "menu/base/submenu_handler.h"
#include "../vehicle.h"
#include "seats/vehicle_seats_edit.h"

using namespace vehicle::seats::vars;

namespace vehicle::seats::vars {
	variables m_vars;

	void kick(bool exclude) {
		if (!menu::player::get_local_player().m_in_vehicle) return;

		for (int i = -1; i < native::get_vehicle_max_number_of_passengers(menu::player::get_local_player().m_vehicle); i++) {
			if (!native::is_vehicle_seat_free(menu::player::get_local_player().m_vehicle, i, 0)) {
				if (exclude && native::get_ped_in_vehicle_seat(menu::player::get_local_player().m_vehicle, i, 0) == menu::player::get_local_player().m_ped) break;
				native::clear_ped_tasks_immediately(native::get_ped_in_vehicle_seat(menu::player::get_local_player().m_vehicle, i, 0));
			}
		}
	}

	void kick_driver() {
		if (!native::is_vehicle_seat_free(menu::player::get_local_player().m_vehicle, -1, 0)) {
			native::clear_ped_tasks_immediately(native::get_ped_in_vehicle_seat(menu::player::get_local_player().m_vehicle, -1, 0));
		}
	}
}

void vehicle_seats_menu::load() {
	set_name("Seats");
	set_parent<vehicle_menu>();

	add_option(button_option("Kick All Seats")
		.add_translate().add_hotkey()
		.add_click([] { kick(false); }));

	add_option(button_option("Kick All Seats (Exclude Me)")
		.add_translate().add_hotkey()
		.add_click([] { kick(true); }));

	add_option(button_option("Kick Driver")
		.add_translate().add_hotkey()
		.add_click(kick_driver));

	add_option(break_option("Seats")
		.add_translate());
}

void vehicle_seats_menu::update() {}

void vehicle_seats_menu::update_once() {
	clear_options(4);

	if (!menu::player::get_local_player().m_in_vehicle) return;

	for (int i = -1; i < native::get_vehicle_max_number_of_passengers(menu::player::get_local_player().m_vehicle); i++) {
		bool free = native::is_vehicle_seat_free(menu::player::get_local_player().m_vehicle, i, 0);
		bool driver = i == -1;

		std::string n = "";
		if (free) n = "Free Seat";
		else {
			Ped ped = native::get_ped_in_vehicle_seat(menu::player::get_local_player().m_vehicle, i, 0);
			menu::player::for_each([&](menu::player::player_context& player) {
				if (player.m_ped == ped) {
					n = player.m_name;
					if (player.m_id == menu::player::get_local_player().m_id) {
						n = "Me";
					}
				}
			}, true);

			if (n.empty()) {
				n = "Ped - " + std::to_string(ped);
			}
		}

		char name[100];
		sprintf_s(name, "[Seat %i] %s%s", i + 1, driver ? "[Driver] " : "", n.c_str());

		add_option(submenu_option(name)
			.add_submenu<vehicle_seats_edit_menu>()
			.add_click([=] { vehicle::seats::edit::vars::m_vars.m_seat = i; }));
	}
}

void vehicle_seats_menu::feature_update() {}

vehicle_seats_menu* g_instance;
vehicle_seats_menu* vehicle_seats_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new vehicle_seats_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}