#include "network_players_friendly.h"
#include "menu/base/submenu_handler.h"
#include "network_players_selected.h"
#include "menu/base/util/timers.h"
#include "menu/base/util/helpers.h"
#include "rage/types/global_types.h"
#include "menu/base/util/global.h"
#include "rage/engine.h"
#include "menu/base/submenus/main/player/wardrobe_save_load.h"
#include "menu/base/submenus/main/player/wardrobe.h"
#include "global/lists.h"
#include "menu/base/submenus/main/weapon/give/give_weapon.h"
#include "util/fiber_pool.h"
#include "util/fiber.h"
#include "friendly/network_players_friendly_drops.h"
#include "menu/base/submenus/main/network/network_session.h"

using namespace network::players::friendly::vars;

namespace network::players::friendly::vars {
	variables m_vars;

	scroll_struct<uint32_t> commends[] = {
		{ localization("Friendly", true), 0xDAFB10F9 },
		{ localization("Helpful", true), 0x893E1390 }
	};

	scroll_struct<int> outfit[] = {
		{ localization("Copy Outfit", true), 0 },
		{ localization("Save Outfit", true), 0 }
	};

	void off_the_radar(menu::player::player_context& player) {
		std::vector<int> list = {
			rage::global::give_off_the_radar,
			player.m_id,
			native::get_network_time(),
			native::get_network_time() + 60000,
			1, // has start
			1, // has end
			menu::script_global(rage::global::_155_give_off_the_radar_global).at(player.m_id, rage::global::_155_give_off_the_radar_global_size).at(rage::global::_155_give_off_the_radar_global_index).as<int>()
		};

		menu::helpers::trigger_script_event(list, 7, player.m_id);
	}

	void disable_police(menu::player::player_context& player) {
		std::vector<int> list = {
			rage::global::remove_wanted_level,
			player.m_id, 
			menu::script_global(rage::global::_155_give_off_the_radar_global).at(player.m_id, rage::global::_155_give_off_the_radar_global_size).at(rage::global::_155_give_off_the_radar_global_index).as<int>()
		};

		menu::helpers::trigger_script_event(list, 3, player.m_id);
	}

	void spawn_bodyguards(menu::player::player_context& player, int count) {
		for (int i = 0; i < count; i++) {
			Ped ped = native::clone_ped(player.m_ped, player.m_heading, true, false);
			if (native::does_entity_exist(ped)) {
				native::give_weapon_to_ped(ped, 0x1b06d571, -1, false, true);
				native::set_ped_as_group_member(ped, native::get_player_group(player.m_id));
			}
		}
	}

	void commend(menu::player::player_context& player, int id) {
		if (!player.m_net_player) return;
		rage::engine::send_increment_stat_event(commends[id].m_result, 16, player.m_net_player);
	}

	void parachute(menu::player::player_context& player) {
		math::vector3<float> rotation = native::get_entity_rotation(player.m_ped, 0);
		math::vector3<float> coords = player.m_coords;

		native::set_entity_coords(menu::player::get_local_player().m_ped, coords.x + 10.0f, coords.y + 10.0f, coords.z + 24.0f, true, false, false, false);
		native::set_entity_rotation(menu::player::get_local_player().m_ped, rotation.x, rotation.y, rotation.z, 0, true);
		native::task_parachute_to_target(menu::player::get_local_player().m_ped, coords.x, coords.y, coords.z);
	}

	void give_all_weapons(menu::player::player_context& player) {
		util::fiber::pool::add([=] {
			for (scroll_struct<uint32_t> weapon : global::lists::g_weapons) {
				weapon::give::vars::give_weapon(player.m_ped, weapon.m_result, false, false);
				util::fiber::sleep(10);
			}
		});
	}

	void give_all_attachments(menu::player::player_context& player) {
		util::fiber::pool::add([=] {
			for (scroll_struct<uint32_t> weapon : global::lists::g_weapons) {
				weapon::give::vars::upgrade_weapon_components(player.m_ped, weapon.m_result);
				util::fiber::sleep(10);
			}
		});
	}
}

void network_players_friendly_menu::load() {
	set_name("Friendly");
	set_parent<network_players_selected_menu>();

	add_option(submenu_option("Drops")
		.add_translate()
		.add_submenu<network_players_friendly_drops_menu>());

	add_option(toggle_option("Demi Godmode")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_demi_godmode)
		.add_update([](toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_demi_godmode);
			} else {
				option->add_toggle(m_vars.m_demi_godmode);
			}
		}));

	add_option(toggle_option("Off the Radar")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_off_the_radar)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_off_the_radar);
			} else {
				option->add_toggle(m_vars.m_off_the_radar);
			}
		}));

	add_option(toggle_option("Disable Police")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_disable_police)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_disable_police);
			} else {
				option->add_toggle(m_vars.m_disable_police);
			}
		}));

	add_option(toggle_option("Kill Killers")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_kill_killers)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_kill_killers);
			} else {
				option->add_toggle(m_vars.m_kill_killers);
			}
		}));

	add_option(toggle_option("Force Visible")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_force_visible)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_force_visible);
			} else {
				option->add_toggle(m_vars.m_force_visible);
			}
		}));

	add_option(number_option<int>(SCROLLSELECT, "Spawn Bodyguard(s)")
		.add_translate()
		.add_number(menu::player::get_selected_player().m_bodyguard_count, "%i", 1).add_min(1).add_max(20)
		.add_update([] (number_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_number(menu::player::get_selected_player().m_bodyguard_count, "%i", 1);
			} else {
				option->add_number(m_vars.m_bodyguard_count, "%i", 1);
			}
		})
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				spawn_bodyguards(menu::player::get_selected_player(), menu::player::get_selected_player().m_bodyguard_count);
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					spawn_bodyguards(player, m_vars.m_bodyguard_count);
				});
			}
		}));

	add_option(scroll_option<uint32_t>(SCROLLSELECT, "Commend")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_commend, 0, NUMOF(commends), commends)
		.add_update([](scroll_option<uint32_t>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_commend, 0, NUMOF(commends), commends);
			} else {
				option->add_scroll(m_vars.m_commend, 0, NUMOF(commends), commends);
			}
		})
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				commend(menu::player::get_selected_player(), menu::player::get_selected_player().m_commend);
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					commend(player, m_vars.m_commend);
				});
			}
		}));

	add_option(scroll_option<int>(SCROLLSELECT, "Outfit")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_outfit, 0, NUMOF(outfit), outfit)
		.add_update([] (scroll_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_outfit, 0, NUMOF(outfit), outfit);
			} else {
				option->add_scroll(m_vars.m_outfit, 1, NUMOF(outfit), outfit);
			}
		})
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_outfit == 0) {
					native::clear_all_ped_props(menu::player::get_local_player().m_ped);

					for (scroll_struct<std::pair<int, math::vector3_<float>>>& component : player::wardrobe::vars::components) {
						native::set_ped_component_variation(menu::player::get_local_player().m_ped, component.m_result.first, native::get_ped_drawable_variation(menu::player::get_selected_player().m_ped, component.m_result.first), native::get_ped_texture_variation(menu::player::get_selected_player().m_ped, component.m_result.first), 0);
					}

					for (scroll_struct<std::pair<int, math::vector3_<float>>>& prop : player::wardrobe::vars::accessories) {
						native::set_ped_prop_index(menu::player::get_local_player().m_ped, prop.m_result.first, native::get_ped_prop_index(menu::player::get_selected_player().m_ped, prop.m_result.first), native::get_ped_prop_texture_index(menu::player::get_selected_player().m_ped, prop.m_result.first), true);
					}
				} else {
					player::wardrobe::saveload::vars::save_outfit(menu::player::get_selected_player().m_name.c_str(), menu::player::get_selected_player());
				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					player::wardrobe::saveload::vars::save_outfit(player.m_name.c_str(), player);
				});
			}
		}));

	add_option(button_option("Parachute to Player")
		.add_translate()
		.add_click([] { parachute(menu::player::get_selected_player()); })
		.add_requirement([] { return global::vars::g_network_menu_type == SELECTED_PLAYER; }));

	add_option(button_option("Give All Weapons")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				give_all_weapons(menu::player::get_selected_player());
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					give_all_weapons(player);
				});
			}
		}));
	
	add_option(button_option("Give All Attachments")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				give_all_attachments(menu::player::get_selected_player());
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					give_all_attachments(player);
				});
			}
		}));
}

void network_players_friendly_menu::update() {}

void network_players_friendly_menu::update_once() {
	if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
		set_parent<network_players_selected_menu>();
	} else {
		set_parent<network_session_menu>();
	}
}

void network_players_friendly_menu::feature_update() {
	menu::player::for_each([] (menu::player::player_context& player) {
		if (player.m_demi_godmode || m_vars.m_demi_godmode) {
			if (!player.m_in_vehicle && player.m_alive) {
				menu::timers::run_timed(&player.m_demi_godmode_timer, 250, [=] {
					int armor = native::get_ped_armour(player.m_ped);
					int armor_max = native::get_player_max_armour(player.m_id);
					int health = native::get_entity_health(player.m_ped);
					int health_max = native::get_entity_max_health(player.m_ped);

					if (armor < armor_max) {
						native::create_ambient_pickup(0x4bfb42d1, player.m_coords.x, player.m_coords.y, player.m_coords.z, 0, armor_max - armor, 0xe6cb661e, false, true);
					}

					if (health < health_max) {
						native::create_ambient_pickup(0x8f707c18, player.m_coords.x, player.m_coords.y, player.m_coords.z, 0, health_max - health, 0xe6cb661e, false, true);
					}
				});
			}
		}

		if (player.m_off_the_radar || m_vars.m_off_the_radar) {
			menu::timers::run_timed(&player.m_off_the_radar_timer, 1000, [&] {
				off_the_radar(player);
			});
		}

		if (player.m_disable_police || m_vars.m_disable_police) {
			menu::timers::run_timed(&player.m_disable_police_timer, 500, [&] {
				disable_police(player);
			});
		}

		if (player.m_kill_killers || m_vars.m_kill_killers) {
			if (!player.m_alive) {
				Entity killer = native::get_ped_source_of_death(player.m_ped);
				if (killer) {
					if (native::is_ped_a_player(killer)) {
						if (!native::is_entity_dead(killer, 1)) {
							math::vector3<float> coords = native::get_entity_coords(killer, true);
							native::add_explosion(coords.x, coords.y, coords.z, 1, 100.f, true, false, 0.f, false);
						}
					}
				}
			}
		}

		if (player.m_force_visible) {
			if (!native::is_entity_visible(player.m_entity)) {
				native::set_entity_locally_visible(player.m_entity);
				native::set_entity_visible(player.m_entity, true, true);
			}
		}
	});
}

network_players_friendly_menu* g_instance;
network_players_friendly_menu* network_players_friendly_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_friendly_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}