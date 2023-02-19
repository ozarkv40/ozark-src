#include "network_players_teleport.h"
#include "menu/base/submenu_handler.h"
#include "network_players_selected.h"
#include "menu/base/util/control.h"
#include "teleport/network_players_teleport_apartments.h"
#include "menu/base/submenus/main/network/network_session.h"

using namespace network::players::teleport::vars;

namespace network::players::teleport::vars {
	variables m_vars;

	void teleport_all_players_to_me() {
		menu::player::for_each([&] (menu::player::player_context& player) {
			if (player.m_in_vehicle) {
				menu::control::request_control(player.m_entity, [=] (Entity veh) {
					math::vector3<float> forward = native::get_entity_forward_vector(menu::player::get_local_player().m_entity);
					math::vector3<float> coords = menu::player::get_local_player().m_coords + (forward * (2.f + (player.m_id * 2.f)));
					native::set_entity_coords(veh, coords.x, coords.y, coords.z, true, true, true, false);
				});
			}
		});
	}

	void teleport_to_player(menu::player::player_context& player) {
		native::set_entity_coords(menu::player::get_local_player().m_entity, player.m_coords.x, player.m_coords.y, player.m_coords.z, true, true, true, false);
	}

	void teleport_to_vehicle(menu::player::player_context& player) {
		if (player.m_in_vehicle) {
			menu::control::request_control(player.m_entity, [] (Entity veh) {
				math::vector3<float> forward = native::get_entity_forward_vector(veh);
				math::vector3<float> coords = native::get_entity_coords(veh, true) + (forward * 5.f);
				native::set_entity_coords(menu::player::get_local_player().m_entity, coords.x, coords.y, coords.z, true, true, true, false);
			});
		} else {
			menu::notify::stacked(network_players_teleport_menu::get()->get_name().get(), util::va::va("%s %s", network_players_teleport_menu::get()->get_string("Failed to get a vehicle handle for").c_str(), player.m_name.c_str()));
		}
	}

	void teleport_to_me(menu::player::player_context& player) {
		if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
			if (player.m_in_vehicle) {
				menu::control::request_control(player.m_vehicle, [] (Entity veh) {
					math::vector3<float> forward = native::get_entity_forward_vector(menu::player::get_local_player().m_vehicle);
					math::vector3<float> coords = menu::player::get_local_player().m_coords + (forward * 5.f);
					native::set_entity_coords(veh, coords.x, coords.y, coords.z, true, true, true, false);
				});
			} else {
				menu::notify::stacked(network_players_teleport_menu::get()->get_name().get(), util::va::va("%s %s", network_players_teleport_menu::get()->get_string("Failed to get a vehicle handle for").c_str(), player.m_name.c_str()));
			}
		} else {
			teleport_all_players_to_me();
		}
	}

	void teleport_into_vehicle(menu::player::player_context& player) {
		if (player.m_in_vehicle) {
			bool inside = false;
			for (int i = -1; i < native::get_vehicle_max_number_of_passengers(player.m_vehicle); i++) {
				if (native::is_vehicle_seat_free(player.m_vehicle, i, 1)) {
					native::set_ped_into_vehicle(menu::player::get_local_player().m_ped, player.m_vehicle, i);
					inside = true;
					break;
				}
			}

			if (!inside) {
				menu::notify::stacked(network_players_teleport_menu::get()->get_name().get(), network_players_teleport_menu::get()->get_string("No free seats, or they're too far away").c_str());
			}
		} else {
			menu::notify::stacked(network_players_teleport_menu::get()->get_name().get(), util::va::va("%s %s", network_players_teleport_menu::get()->get_string("Failed to get a vehicle handle for").c_str(), player.m_name.c_str()));
		}
	}
}

void network_players_teleport_menu::load() {
	set_name("Teleport");
	set_parent<network_players_selected_menu>();

	add_string("Failed to get a vehicle handle for");
	add_string("No free seats, or they're too far away");

	add_option(submenu_option("Apartments")
		.add_translate()
		.add_submenu<network_players_teleport_apartments_menu>());

	add_option(button_option("Teleport to Player")
		.add_translate()
		.add_click([] { teleport_to_player(menu::player::get_selected_player()); })
		.add_requirement([] { return global::vars::g_network_menu_type == SELECTED_PLAYER; }));

	add_option(button_option("Teleport to Vehicle")
		.add_translate()
		.add_click([] { teleport_to_vehicle(menu::player::get_selected_player()); })
		.add_requirement([] { return global::vars::g_network_menu_type == SELECTED_PLAYER; }));

	add_option(button_option("Teleport Vehicle to Me")
		.add_translate()
		.add_click([] { teleport_to_me(menu::player::get_selected_player()); }));

	add_option(button_option("Teleport Into Vehicle")
		.add_translate()
		.add_click([] { teleport_into_vehicle(menu::player::get_selected_player()); })
		.add_requirement([] { return global::vars::g_network_menu_type == SELECTED_PLAYER; }));
}

void network_players_teleport_menu::update() {}

void network_players_teleport_menu::update_once() {
	if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
		set_parent<network_players_selected_menu>();
	} else {
		set_parent<network_session_menu>();
	}
}

void network_players_teleport_menu::feature_update() {}

network_players_teleport_menu* g_instance;
network_players_teleport_menu* network_players_teleport_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_teleport_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}