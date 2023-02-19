#include "protection_reactions.h"
#include "menu/base/submenu_handler.h"
#include "../protections.h"
#include "reactions/protection_reactions_selected.h"
#include "util/fiber.h"
#include "util/fiber_pool.h"
#include "rage/engine.h"
#include "menu/base/submenus/main/network/players/network_players_abusive.h"
#include "menu/base/submenus/main/network/players/network_players_trolling.h"
#include "menu/base/submenus/main/network/players/network_players_removals.h"
#include "menu/base/submenus/main/network/session/network_session_overseer.h"

using namespace protection::reactions::vars;

namespace protection::reactions::vars {
	variables m_vars;

	std::string reasons[] = {
		"Death",						//
		"Aim",							//
		"Report",						//
		"Spoofed Host Token",			//
		"Spoofed Rockstar ID",			//
		"Spoofed Name",					//
		"Spoofed IP",					//
		"Spoofed Chat",					//
		"Spoofed Text",					//
		"Arxan",						//
		"Crash Attempt",				//
		"Spectating You",				//
		"Money Drop",					//
		"Quantum Kick",					//
		"Script Migration",				//
		"Super Jump",					//
		"Join Timeout",					//
		"Invalid Model",				//
		"Info Change"					//
	};

	void process_event(eEventReactions _event, Player id) {
		util::fiber::pool::add([=] {
			menu::player::player_context& player = menu::player::get_player(id);
			if (!player.m_connected) return;

			if (m_vars.m_reactions[_event].m_explode) {
				native::add_explosion(player.m_coords.x, player.m_coords.y, player.m_coords.z, 0, 10.f, true, false, 0.f, false);
				util::fiber::sleep(250);
			}

			if (m_vars.m_reactions[_event].m_crash) {
				network::players::removals::vars::crash(player);
				util::fiber::sleep(250);
			}

			if (m_vars.m_reactions[_event].m_kick) {
				if (menu::player::get_local_player().m_is_script_host) {
					network::players::removals::vars::script_host_kick(player);
					util::fiber::sleep(250);
				}

				if (rage::engine::get_host_net_game_player() == menu::player::get_local_player().m_net_player) {
					network::players::removals::vars::session_host_kick(player);
					util::fiber::sleep(250);
				} else {
					if (rage::engine::get_host_net_game_player() != player.m_net_player) {
						network::players::removals::vars::break_freemode_kick(player);
						util::fiber::sleep(250);
					}
				}
			}

			if (m_vars.m_reactions[_event].m_add_to_overseer) {
				if (is_valid_ptr(player.m_net_player)) {
					if (is_valid_ptr(player.m_net_player->m_player_info)) {
						network::session::overseer::vars::save(player.m_name, player.m_net_player->m_player_info->m_identifier.m_rockstar_id, "Event Reaction for " + reasons[_event]);
					}
				}

				util::fiber::sleep(250);
			}

			if (m_vars.m_reactions[_event].m_cage) {
				network::players::abusive::vars::cage_player(player, 2);
				util::fiber::sleep(250);
			}

			if (m_vars.m_reactions[_event].m_kick_from_vehicle) {
				network::players::abusive::vars::kick_from_vehicle(player);
				util::fiber::sleep(250);
			}

			if (m_vars.m_reactions[_event].m_set_on_fire) {
				network::players::abusive::vars::set_on_fire(player);
				util::fiber::sleep(250);
			}

			if (m_vars.m_reactions[_event].m_ragdoll) {
				network::players::abusive::vars::ragdoll(player);
				util::fiber::sleep(250);
			}

			if (m_vars.m_reactions[_event].m_glitch_physics) {
				network::players::abusive::vars::glitch_physics(player);
				util::fiber::sleep(250);
			}

			if (m_vars.m_reactions[_event].m_black_screen) {
				network::players::trolling::vars::black_screen(player);
				util::fiber::sleep(250);
			}

			if (m_vars.m_reactions[_event].m_blame) {
				network::players::abusive::vars::blame(player);
				util::fiber::sleep(250);
			}

			if (m_vars.m_reactions[_event].m_give_wanted_level) {
				network::players::abusive::vars::give_wanted_level(player, 1);
				util::fiber::sleep(250);
			}

			if (m_vars.m_reactions[_event].m_send_to_island) {
				network::players::abusive::vars::send_to_island(player);
				util::fiber::sleep(250);
			}

			if (m_vars.m_reactions[_event].m_remove_weapons) {
				native::remove_all_ped_weapons(player.m_ped, true);
				util::fiber::sleep(250);
			}

			if (m_vars.m_reactions[_event].m_hostile_clone) {
				player.m_clone_type = 1;
				network::players::abusive::vars::clone_player(player, player.m_clone_type);
				util::fiber::sleep(250);
			}

			if (m_vars.m_reactions[_event].m_bail) {
				if (is_valid_ptr(*(uint64_t*)(global::vars::g_network_player_manager))) {
					native::network_bail(0, 0, 0);
				}
			}
		});
	}
}

void protection_reactions_menu::load() {
	set_name("Reactions");
	set_parent<protection_menu>();

	int index = 0;
	for (std::string s : reasons) {
		add_string(s);

		m_vars.m_reactions[index].m_explode = util::config::read_bool(get_submenu_name_stack(), "Explode", false, { s });
		m_vars.m_reactions[index].m_crash = util::config::read_bool(get_submenu_name_stack(), "Crash", false, { s });
		m_vars.m_reactions[index].m_kick = util::config::read_bool(get_submenu_name_stack(), "Kick", false, { s });
		m_vars.m_reactions[index].m_add_to_overseer = util::config::read_bool(get_submenu_name_stack(), "Add to Overseer", false, { s });
		m_vars.m_reactions[index].m_cage = util::config::read_bool(get_submenu_name_stack(), "Cage", false, { s });
		m_vars.m_reactions[index].m_kick_from_vehicle = util::config::read_bool(get_submenu_name_stack(), "Kick from Vehicle", false, { s });
		m_vars.m_reactions[index].m_set_on_fire = util::config::read_bool(get_submenu_name_stack(), "Set on Fire", false, { s });
		m_vars.m_reactions[index].m_ragdoll = util::config::read_bool(get_submenu_name_stack(), "Ragdoll", false, { s });
		m_vars.m_reactions[index].m_glitch_physics = util::config::read_bool(get_submenu_name_stack(), "Glitch Physics", false, { s });
		m_vars.m_reactions[index].m_black_screen = util::config::read_bool(get_submenu_name_stack(), "Black Screen", false, { s });
		m_vars.m_reactions[index].m_blame = util::config::read_bool(get_submenu_name_stack(), "Blame", false, { s });
		m_vars.m_reactions[index].m_give_wanted_level = util::config::read_bool(get_submenu_name_stack(), "Give Wanted Level", false, { s });
		m_vars.m_reactions[index].m_send_to_island = util::config::read_bool(get_submenu_name_stack(), "Send to Island", false, { s });
		m_vars.m_reactions[index].m_remove_weapons = util::config::read_bool(get_submenu_name_stack(), "Remove Weapons", false, { s });
		m_vars.m_reactions[index].m_hostile_clone = util::config::read_bool(get_submenu_name_stack(), "Hostile Clone", false, { s });
		m_vars.m_reactions[index].m_bail = util::config::read_bool(get_submenu_name_stack(), "Bail", false, { s });
		index++;
	}
}

void protection_reactions_menu::update() {}

void protection_reactions_menu::update_once() {	// save config
	clear_options(0);

	int index = 0;
	for (std::string s : reasons) {
		add_option(submenu_option(get_string(s))
			.add_submenu<protection_reactions_selected_menu>()
			.add_click([=] {
				protection_reactions_selected_menu::get()->set_name(s, false, false);
				protection::reactions::selected::vars::m_vars.m_selected = index;
			}));

		index++;
	}

	if (menu::submenu::handler::get_previous() == protection_reactions_selected_menu::get()) {
		util::config::write_bool(get_submenu_name_stack(), "Explode", m_vars.m_reactions[protection::reactions::selected::vars::m_vars.m_selected].m_explode, { reasons[protection::reactions::selected::vars::m_vars.m_selected] });
		util::config::write_bool(get_submenu_name_stack(), "Crash", m_vars.m_reactions[protection::reactions::selected::vars::m_vars.m_selected].m_crash, { reasons[protection::reactions::selected::vars::m_vars.m_selected] });
		util::config::write_bool(get_submenu_name_stack(), "Kick", m_vars.m_reactions[protection::reactions::selected::vars::m_vars.m_selected].m_kick, { reasons[protection::reactions::selected::vars::m_vars.m_selected] });
		util::config::write_bool(get_submenu_name_stack(), "Add to Overseer", m_vars.m_reactions[protection::reactions::selected::vars::m_vars.m_selected].m_add_to_overseer, { reasons[protection::reactions::selected::vars::m_vars.m_selected] });
		util::config::write_bool(get_submenu_name_stack(), "Cage", m_vars.m_reactions[protection::reactions::selected::vars::m_vars.m_selected].m_cage, { reasons[protection::reactions::selected::vars::m_vars.m_selected] });
		util::config::write_bool(get_submenu_name_stack(), "Kick from Vehicle", m_vars.m_reactions[protection::reactions::selected::vars::m_vars.m_selected].m_kick_from_vehicle, { reasons[protection::reactions::selected::vars::m_vars.m_selected] });
		util::config::write_bool(get_submenu_name_stack(), "Set on Fire", m_vars.m_reactions[protection::reactions::selected::vars::m_vars.m_selected].m_set_on_fire, { reasons[protection::reactions::selected::vars::m_vars.m_selected] });
		util::config::write_bool(get_submenu_name_stack(), "Ragdoll", m_vars.m_reactions[protection::reactions::selected::vars::m_vars.m_selected].m_ragdoll, { reasons[protection::reactions::selected::vars::m_vars.m_selected] });
		util::config::write_bool(get_submenu_name_stack(), "Glitch Physics", m_vars.m_reactions[protection::reactions::selected::vars::m_vars.m_selected].m_glitch_physics, { reasons[protection::reactions::selected::vars::m_vars.m_selected] });
		util::config::write_bool(get_submenu_name_stack(), "Black Screen", m_vars.m_reactions[protection::reactions::selected::vars::m_vars.m_selected].m_black_screen, { reasons[protection::reactions::selected::vars::m_vars.m_selected] });
		util::config::write_bool(get_submenu_name_stack(), "Blame", m_vars.m_reactions[protection::reactions::selected::vars::m_vars.m_selected].m_blame, { reasons[protection::reactions::selected::vars::m_vars.m_selected] });
		util::config::write_bool(get_submenu_name_stack(), "Give Wanted Level", m_vars.m_reactions[protection::reactions::selected::vars::m_vars.m_selected].m_give_wanted_level, { reasons[protection::reactions::selected::vars::m_vars.m_selected] });
		util::config::write_bool(get_submenu_name_stack(), "Send to Island", m_vars.m_reactions[protection::reactions::selected::vars::m_vars.m_selected].m_send_to_island, { reasons[protection::reactions::selected::vars::m_vars.m_selected] });
		util::config::write_bool(get_submenu_name_stack(), "Remove Weapons", m_vars.m_reactions[protection::reactions::selected::vars::m_vars.m_selected].m_remove_weapons, { reasons[protection::reactions::selected::vars::m_vars.m_selected] });
		util::config::write_bool(get_submenu_name_stack(), "Hostile Clone", m_vars.m_reactions[protection::reactions::selected::vars::m_vars.m_selected].m_hostile_clone, { reasons[protection::reactions::selected::vars::m_vars.m_selected] });
	}
}

void protection_reactions_menu::feature_update() {
	static uint32_t last_death = 0;
	static uint32_t last_aim[32];

	if (m_vars.m_reactions[EVENT_DEATH].is_active()) {
		if (!menu::player::get_local_player().m_alive) {
			if (GetTickCount() - last_death > 2000) {
				Ped killer = native::get_ped_source_of_death(menu::player::get_local_player().m_ped);
				if (killer && killer != menu::player::get_local_player().m_ped && native::is_ped_a_player(killer)) {
					Player player_killer = native::network_get_player_index_from_ped(killer);
					if (player_killer != menu::player::get_local_player().m_id && menu::player::get_player(player_killer).m_connected) {
						last_death = GetTickCount();
						process_event(EVENT_DEATH, player_killer);
					}
				}
			}
		}
	}

	if (m_vars.m_reactions[EVENT_AIM].is_active()) {
		menu::player::for_each([] (menu::player::player_context& player) {
			if (GetTickCount() - last_aim[player.m_id] > 2000) {
				if (native::is_player_targetting_entity(player.m_id, menu::player::get_local_player().m_entity)) {
					last_aim[player.m_id] = GetTickCount();
					process_event(EVENT_AIM, player.m_id);
				}
			}
		});
	}
}

protection_reactions_menu* g_instance;
protection_reactions_menu* protection_reactions_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new protection_reactions_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}