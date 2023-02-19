#include "network_players_abusive_attackers.h"
#include "menu/base/submenu_handler.h"
#include "../network_players_abusive.h"
#include "menu/base/util/control.h"

using namespace network::players::abusive::attackers::vars;

namespace network::players::abusive::attackers::vars {
	variables m_vars;

	scroll_struct<int> type[] = {
		{ localization("Military Jets", true), 0 },
		{ localization("Military Buzzards", true), 1 },
	};

	void spawn_attackers(menu::player::player_context& player, bool session = false) {
		std::vector<Entity> entities;

		int type = session ?  m_vars.m_attacker_type : player.m_attacker_type;
		int count = session ? m_vars.m_attacker_count : player.m_attacker_count;
		bool invincibility = session ? m_vars.m_attacker_invincibility : player.m_attacker_invincibility;
		bool invisibility = session ? m_vars.m_attacker_invisibility : player.m_attacker_invisibility;

		if (type == 0) { // Military Jets
			menu::control::simple_request_model(0xB39B0AE6); // lazer

			for (int i = 0; i < count; i++) {
				math::vector3_<float> spawn_coords = { player.m_coords.x + native::get_random_float_in_range(0.f, 100.f), player.m_coords.y + native::get_random_float_in_range(0.f, 100.f), player.m_coords.z + 100.f + (i * 10.f) };

				Vehicle vehicle = native::create_vehicle(0xB39B0AE6, spawn_coords.x, spawn_coords.y, spawn_coords.z, player.m_heading, true, true, 0);
				if (native::does_entity_exist(vehicle)) {
					native::apply_force_to_entity(vehicle, 1, 0.f, 0.f, 50.f, 0.f, 0.f, 0.f, 0, true, true, true, false, true);

					entities.push_back(vehicle);

					Ped ped = native::create_random_ped_as_driver(vehicle, true);
					if (native::does_entity_exist(ped)) {
						native::task_plane_chase(ped, player.m_ped, 0.f, 0.f, 50.f);
						native::task_combat_ped(ped, player.m_ped, 0, 16);
						native::set_ped_keep_task(ped, true);
						entities.push_back(ped);
					}
				}
			}
		}

		if (type == 1) { // Military Buzzards
			menu::control::simple_request_model(0x2f03547b); // buzzard
			menu::control::simple_request_model(0x613E626C); // mw

			for (int i = 0; i < count; i++) {
				math::vector3_<float> spawn_coords = { player.m_coords.x + native::get_random_float_in_range(0.f, 100.f), player.m_coords.y + native::get_random_float_in_range(0.f, 100.f), player.m_coords.z + 100.f + (i * 10.f) };

				Vehicle vehicle = native::create_vehicle(0x2f03547b, spawn_coords.x, spawn_coords.y, spawn_coords.z, player.m_heading, true, true, 0);
				if (native::does_entity_exist(vehicle)) {
					native::apply_force_to_entity(vehicle, 1, 0.f, 0.f, 50.f, 0.f, 0.f, 0.f, 0, true, true, true, false, true);

					entities.push_back(vehicle);

					Ped ped = native::create_random_ped_as_driver(vehicle, true);
					if (native::does_entity_exist(ped)) {
						entities.push_back(ped);

						native::task_heli_chase(ped, player.m_ped, 0.f, 0.f, 50.f);
						native::task_combat_ped(ped, player.m_ped, 0, 16);
						native::set_ped_keep_task(ped, true);

						for (int j = 0; j < native::get_vehicle_max_number_of_passengers(vehicle); j++) {
							ped = native::create_ped_inside_vehicle(vehicle, 29, 0x613E626C, i, true, false);
							if (native::does_entity_exist(ped)) {
								entities.push_back(ped);

								native::set_ped_combat_ability(ped, 100);
								native::give_delayed_weapon_to_ped(ped, 0x394f415c, 9999, true);
								native::task_combat_ped(ped, player.m_ped, 0, 16);
								native::set_ped_keep_task(ped, true);
							}
						}
					}
				}
			}
		}

		for (Entity& e : entities) {
			native::set_entity_invincible(e, invincibility);
			native::set_entity_visible(e, !invisibility, true);
		}
	}
}

void network_players_abusive_attackers_menu::load() {
	set_name("Attackers");
	set_parent<network_players_abusive_menu>();

	add_option(scroll_option<int>(SCROLL, "Type")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_attacker_type, 0, NUMOF(type), type)
		.add_update([] (scroll_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_attacker_type, 0, NUMOF(type), type);
			} else {
				option->add_scroll(m_vars.m_attacker_type, 0, NUMOF(type), type);
			}
		}));

	add_option(toggle_option("Invincibility")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_attacker_invincibility)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_attacker_invincibility);
			} else {
				option->add_toggle(m_vars.m_attacker_invincibility);
			}
		}));

	add_option(toggle_option("Invisibility")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_attacker_invisibility)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_attacker_invisibility);
			} else {
				option->add_toggle(m_vars.m_attacker_invisibility);
			}
		}));

	add_option(number_option<int>(SCROLL, "Count")
		.add_translate()
		.add_number(menu::player::get_selected_player().m_attacker_count, "%i", 1).add_min(1).add_max(100)
		.add_update([] (number_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_number(menu::player::get_selected_player().m_attacker_count, "%i", 1);
			} else {
				option->add_number(m_vars.m_attacker_count, "%i", 1);
			}
		}));

	add_option(button_option("Spawn Attackers")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				spawn_attackers(menu::player::get_selected_player());
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					spawn_attackers(player, true);
				});
			}
		}));
}

void network_players_abusive_attackers_menu::update() {}

void network_players_abusive_attackers_menu::update_once() {}

void network_players_abusive_attackers_menu::feature_update() {}

network_players_abusive_attackers_menu* g_instance;
network_players_abusive_attackers_menu* network_players_abusive_attackers_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_abusive_attackers_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}