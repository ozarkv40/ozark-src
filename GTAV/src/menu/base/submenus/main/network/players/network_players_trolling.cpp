#include "network_players_trolling.h"
#include "menu/base/submenu_handler.h"
#include "network_players_selected.h"
#include "network_players_abusive.h"
#include "menu/base/util/helpers.h"
#include "rage/types/global_types.h"
#include "trolling/network_players_trolling_sounds.h"
#include "trolling/network_players_trolling_attachments.h"
#include "menu/base/submenus/main/network/network_session.h"

using namespace network::players::trolling::vars;

namespace network::players::trolling::vars {
	variables m_vars;

	scroll_struct<uint32_t> weapon_groups[] = {
		{ localization("Melee", true), 0xD49321D4 },
		{ localization("Pistol", true), 0x18D5FA97 },
		{ localization("SMG", true), 0xC6E9A5C5 },
		{ localization("Assault Rifle", true), 0x39D5C192 },
		{ localization("MG", true), 0x451B04BC },
		{ localization("Shotgun", true), 0x33431399 },
		{ localization("Sniper", true), 0xB7BBD827 },
		{ localization("Heavy", true), 0xA27A4F9F },
		{ localization("Throwables", true), 0x5C4C5883 },
		{ localization("Spillable", true), 0x5F1BE07C },
		{ localization("Stun", true), 0x29268262 },
		{ localization("Extinguisher", true), 0xFDBF656C }
	};

	void black_screen(menu::player::player_context& player) {
		menu::helpers::trigger_script_event({ rage::global::apartment_teleport, player.m_id, 0, 0 }, 4, player.m_id);
	}

	void remove_weapon_group(menu::player::player_context& player, uint32_t group) {
		std::vector<uint32_t> hashes;

		uint64_t table = *(uint64_t*)global::vars::g_weapon_info.m_list;
		if (table) {
			for (int16_t i = 0; i < (*(int16_t*)global::vars::g_weapon_info.m_count) - 1; i++) {
				rage::types::weapon_info* ptr = (rage::types::weapon_info*) * (uint64_t*)(table + (i * 8));
				if (ptr) {
					if (ptr->m_group_hash == group) {
						hashes.push_back(ptr->m_name_hash);
					}
				}
			}
		}

		for (uint32_t& hash : hashes) {
			native::remove_weapon_from_ped(player.m_ped, hash);
		}

		network_players_trolling_menu* _this = network_players_trolling_menu::get();
		menu::notify::stacked(_this->get_name().get(), util::va::va("%s %i %s %s", _this->get_string("Removed").c_str(), hashes.size(), _this->get_string("weapons from").c_str(), player.m_name.c_str()));
	}
}

void network_players_trolling_menu::load() {
	set_name("Trolling");
	set_parent<network_players_selected_menu>();

	add_string("Removed");
	add_string("weapons from");

	add_option(submenu_option("Sounds")
		.add_translate()
		.add_submenu<network_players_trolling_sounds_menu>());

	add_option(submenu_option("Attachments")
		.add_translate()
		.add_submenu<network_players_trolling_attachments_menu>());

	add_option(button_option("Explode")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				native::add_explosion(menu::player::get_selected_player().m_coords.x, menu::player::get_selected_player().m_coords.y, menu::player::get_selected_player().m_coords.z, 0, 10.f, true, false, 0.f, false);
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					native::add_explosion(player.m_coords.x, player.m_coords.y, player.m_coords.z, 0, 10.f, true, false, 0.f, false);
				});
			}
		}));

	add_option(button_option("Kick From Vehicle")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				network::players::abusive::vars::kick_from_vehicle(menu::player::get_selected_player());
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					network::players::abusive::vars::kick_from_vehicle(player);
				});
			}
		}));

	add_option(scroll_option<int>(SCROLLSELECT, "Cage")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_cage_type, 0, NUMOF(network::players::abusive::vars::cages), network::players::abusive::vars::cages)
		.add_update([] (scroll_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_cage_type, 0, NUMOF(network::players::abusive::vars::cages), network::players::abusive::vars::cages);
			} else {
				option->add_scroll(network::players::abusive::vars::m_vars.m_cage_type, 0, NUMOF(network::players::abusive::vars::cages), network::players::abusive::vars::cages);
			}
		})
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				network::players::abusive::vars::cage_player(menu::player::get_selected_player(), menu::player::get_selected_player().m_cage_type);
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					network::players::abusive::vars::cage_player(player, network::players::abusive::vars::m_vars.m_cage_type);
				});
			}
		}));

	add_option(scroll_option<int>(SCROLLSELECT, "CEO")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_ceo_type, 0, NUMOF(network::players::abusive::vars::ceos), network::players::abusive::vars::ceos)
		.add_update([] (scroll_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_ceo_type, 0, NUMOF(network::players::abusive::vars::ceos), network::players::abusive::vars::ceos);
			} else {
				option->add_scroll(network::players::abusive::vars::m_vars.m_ceo_type, 0, NUMOF(network::players::abusive::vars::ceos), network::players::abusive::vars::ceos);
			}
		})
		.add_click([] {
			int type = global::vars::g_network_menu_type == SELECTED_PLAYER ? menu::player::get_selected_player().m_ceo_type : network::players::abusive::vars::m_vars.m_ceo_type;

			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (type == 0) {
					network::players::abusive::vars::ceo_kick(menu::player::get_selected_player());
				} else network::players::abusive::vars::ceo_ban(menu::player::get_selected_player());
			} else {
				menu::player::for_each([=] (menu::player::player_context& player) {
					if (type == 0) {
						network::players::abusive::vars::ceo_kick(player);
					} else network::players::abusive::vars::ceo_ban(player);
				});
			}
		}));

	add_option(scroll_option<uint32_t>(SCROLLSELECT, "Remove Weapon Group")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_remove_weapon_group_type, 0, NUMOF(weapon_groups), weapon_groups)
		.add_update([] (scroll_option<uint32_t>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_remove_weapon_group_type, 0, NUMOF(weapon_groups), weapon_groups);
			} else {
				option->add_scroll(m_vars.m_remove_weapon_group_type, 0, NUMOF(weapon_groups), weapon_groups);
			}
		})
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				remove_weapon_group(menu::player::get_selected_player(), weapon_groups[menu::player::get_selected_player().m_remove_weapon_group_type].m_result);
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					remove_weapon_group(player, weapon_groups[m_vars.m_remove_weapon_group_type].m_result);
				});
			}
		}));

	add_option(button_option("Set On Fire")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				network::players::abusive::vars::set_on_fire(menu::player::get_selected_player());
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					network::players::abusive::vars::set_on_fire(player);
				});
			}
		}));

	add_option(button_option("Taze")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				network::players::abusive::vars::taze(menu::player::get_selected_player());
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					network::players::abusive::vars::taze(player);
				});
			}
		}));

	add_option(button_option("Ragdoll")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				network::players::abusive::vars::ragdoll(menu::player::get_selected_player());
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					network::players::abusive::vars::ragdoll(player);
				});
			}
		}));

	add_option(button_option("Glitch Physics")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				network::players::abusive::vars::glitch_physics(menu::player::get_selected_player());
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					network::players::abusive::vars::glitch_physics(player);
				});
			}
		}));

	add_option(button_option("Forcefield")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				native::add_explosion(menu::player::get_selected_player().m_coords.x, menu::player::get_selected_player().m_coords.y, menu::player::get_selected_player().m_coords.z, 29, 100.f, false, true, 0.f, true);
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					native::add_explosion(player.m_coords.x, player.m_coords.y, player.m_coords.z, 29, 100.f, false, true, 0.f, true);
				});
			}
		}));

	add_option(button_option("Blame")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				network::players::abusive::vars::blame(menu::player::get_selected_player());
			}
		})
		.add_requirement([] { return global::vars::g_network_menu_type == SELECTED_PLAYER; }));

	add_option(button_option("Rain Rockets")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				network::players::abusive::vars::rain_rockets(menu::player::get_selected_player());
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					network::players::abusive::vars::rain_rockets(player);
				});
			}
		}));

	add_option(button_option("Send to Island")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				network::players::abusive::vars::send_to_island(menu::player::get_selected_player());
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					network::players::abusive::vars::send_to_island(player);
				});
			}
		}));

	add_option(button_option("Black Screen")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				black_screen(menu::player::get_selected_player());
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					black_screen(player);
				});
			}
		}));

	add_option(button_option("Give Wanted Level")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				network::players::abusive::vars::give_wanted_level(menu::player::get_selected_player(), 5);
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					network::players::abusive::vars::give_wanted_level(player, 5);
				});
			}
		}));

	add_option(button_option("Block Passive")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				menu::helpers::trigger_script_event({ rage::global::block_passive, 1, 1 }, 3, menu::player::get_selected_player().m_id);
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					menu::helpers::trigger_script_event({ rage::global::block_passive, 1, 1 }, 3, player.m_id);
				});
			}
		}));

	add_option(scroll_option<uint32_t>(SCROLLSELECT, "Vehicle Ram")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_vehicle_ram_type, 0, NUMOF(network::players::abusive::vars::ram_vehicles), network::players::abusive::vars::ram_vehicles)
		.add_update([] (scroll_option<uint32_t>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_vehicle_ram_type, 0, NUMOF(network::players::abusive::vars::ram_vehicles), network::players::abusive::vars::ram_vehicles);
			} else {
				option->add_scroll(network::players::abusive::vars::m_vars.m_vehicle_ram_type, 0, NUMOF(network::players::abusive::vars::ram_vehicles), network::players::abusive::vars::ram_vehicles);
			}
		})
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				network::players::abusive::vars::ram(menu::player::get_selected_player(), menu::player::get_selected_player().m_vehicle_ram_type);
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					network::players::abusive::vars::ram(player, network::players::abusive::vars::m_vars.m_vehicle_ram_type);
				});
			}
		}));

	add_option(scroll_option<int>(SCROLLSELECT, "Clone")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_clone_type, 0, NUMOF(network::players::abusive::vars::clone), network::players::abusive::vars::clone)
		.add_update([] (scroll_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_clone_type, 0, NUMOF(network::players::abusive::vars::clone), network::players::abusive::vars::clone);
			} else {
				option->add_scroll(network::players::abusive::vars::m_vars.m_clone_type, 0, NUMOF(network::players::abusive::vars::clone), network::players::abusive::vars::clone);
			}
		})
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				network::players::abusive::vars::clone_player(menu::player::get_selected_player(), menu::player::get_selected_player().m_clone_type);
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					network::players::abusive::vars::clone_player(player, network::players::abusive::vars::m_vars.m_clone_type);
				});
			}
		}));

	add_option(scroll_option<int>(SCROLLSELECT, "Show Message")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_show_message_type, 0, NUMOF(network::players::abusive::vars::messages), network::players::abusive::vars::messages)
		.add_update([] (scroll_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_show_message_type, 0, NUMOF(network::players::abusive::vars::messages), network::players::abusive::vars::messages);
			} else {
				option->add_scroll(network::players::abusive::vars::m_vars.m_show_message_type, 0, NUMOF(network::players::abusive::vars::messages), network::players::abusive::vars::messages);
			}
		})
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				network::players::abusive::vars::send_message(menu::player::get_selected_player(), menu::player::get_selected_player().m_show_message_type);
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					network::players::abusive::vars::send_message(player, network::players::abusive::vars::m_vars.m_show_message_type);
				});
			}
		}));
}

void network_players_trolling_menu::update() {}

void network_players_trolling_menu::update_once() {
	if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
		set_parent<network_players_selected_menu>();
	} else {
		set_parent<network_session_menu>();
	}
}

void network_players_trolling_menu::feature_update() {}

network_players_trolling_menu* g_instance;
network_players_trolling_menu* network_players_trolling_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_trolling_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}