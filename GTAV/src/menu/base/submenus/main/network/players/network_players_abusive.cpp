#include "network_players_abusive.h"
#include "menu/base/submenu_handler.h"
#include "network_players_selected.h"
#include "menu/base/util/timers.h"
#include "menu/base/util/control.h"
#include "menu/base/util/helpers.h"
#include "rage/engine.h"
#include "rage/types/global_types.h"
#include "abusive/network_players_abusive_attackers.h"
#include "abusive/network_players_abusive_explosions.h"
#include "menu/base/submenus/main/network/network_session.h"

using namespace network::players::abusive::vars;

namespace network::players::abusive::vars {
	variables m_vars;

	scroll_struct<int> cages[] = {
		{ localization("Trolly", true), 0 },
		{ localization("Fence", true), 1 }
	};

	scroll_struct<int> ceos[] = {
		{ localization("Kick", true), 0 },
		{ localization("Ban", true), 1 }
	};

	scroll_struct<int> clone[] = {
		{ localization("Ambient", true), 0 },
		{ localization("Hostile", true), 1 }
	};

	scroll_struct<int> messages[] = {
		{ localization("Spectating You", true), -649239378 }, //
		{ localization("Stopped Spectating You", true), -90374608 },//
		{ localization("Now Spectating", true), -148441291 },//
		{ localization("$ Banked", true), -989654618 },//
		{ localization("$ Stolen", true), 220852783 },//
		{ localization("$ Removed", true), -1857757712 },//
		{ localization("ATM Stolen", true), -859229584 },//
		{ localization("Equipped Minigun", true), 88766328 },//
		{ localization("Killed Gang Member", true), -1049002738 },//
		{ localization("Registered as President", true), 1149761915 },//
		{ localization("Registered as CEO", true), 1149761915 },//
		{ localization("Registered as VIP", true), 1149761915 },//
		{ localization("Going Psycho", true), 1163167720 },//
		{ localization("VIP Dismissed", true), -1578431846 }//
	};

	scroll_struct<uint32_t> ram_vehicles[] = {
		{ localization("", false), 0x5A82F9AE },
		{ localization("", false), 0x5BA0FF1E },
		{ localization("", false), 0x18619B7E },
		{ localization("", false), 0x322CF98F },
		{ localization("", false), 0xB2E046FB },
		{ localization("", false), 0xE83C17 },
		{ localization("", false), 0xA29F78B0 },
		{ localization("", false), 0x42BC5E19 },
		{ localization("", false), 0x1FD824AF },
		{ localization("", false), 0x8B213907 },
		{ localization("", false), 0x2C1FEA99 },
		{ localization("", false), 0xEA6A047F },
		{ localization("", false), 0x432AA566 },
		{ localization("", false), 0xEB298297 },
		{ localization("", false), 0xB44F0582 },
		{ localization("", false), 0x9472CD24 },
		{ localization("", false), 0x23CA25F2 },
		{ localization("", false), 0x619C1B82 },
		{ localization("", false), 0xB472D2B5 },
		{ localization("", false), 0xC2974024 },
		{ localization("", false), 0xd577c962 },
		{ localization("", false), 0x2ea68690 },
		{ localization("", false), 0xb779a091 },
	};

	void kick_from_vehicle(menu::player::player_context& player) {
		if (player.m_in_vehicle) {
			menu::control::request_control(player.m_vehicle, [] (Entity) {}, true);
		}
	}

	void taze(menu::player::player_context& player) {
		menu::control::request_weapon(0x3656c8c1, [=] (uint32_t hash) {
			native::shoot_single_bullet_between_coords_ignore_entity(player.m_coords.x, player.m_coords.y, player.m_coords.z + 1.f, player.m_coords.x, player.m_coords.y, player.m_coords.z, 10, 0, hash, menu::player::get_local_player().m_ped, true, false, 100.f, menu::player::get_local_player().m_ped, 0);
		});
	}

	void ragdoll(menu::player::player_context& player) {
		rage::engine::send_ragdoll_event(player.m_id);
	}

	void glitch_physics(menu::player::player_context& player) {
		menu::control::request_model(0xd5c0bc07, [=] (uint32_t model) {
			Object guitar = native::create_object(model, player.m_coords.x, player.m_coords.y, player.m_coords.z, true, true, false);
			if (native::does_entity_exist(guitar)) {
				native::set_entity_visible(guitar, false, false);
				native::attach_entity_to_entity(guitar, player.m_ped, native::get_ped_bone_index(player.m_ped, 23553), 0.5f, -0.2f, 0.f, 0.f, 75.0f, 0.f, true, true, false, true, 1, true);
				native::set_entity_collision(guitar, true, true);
			}
		});
	}

	void rain_rockets(menu::player::player_context& player) {
		menu::control::request_weapon(0x13579279, [=] (uint32_t model) {
			math::vector3<float> start_position = player.m_coords;
			start_position.x += native::get_random_float_in_range(-20.f, 20.f);
			start_position.y += native::get_random_float_in_range(-20.f, 20.f);
			native::shoot_single_bullet_between_coords_ignore_entity(start_position.x, start_position.y, start_position.z + native::get_random_float_in_range(50.f, 150.f), start_position.x, start_position.y, start_position.z, 250, 0, model, menu::player::get_local_player().m_ped, true, false, 1000.f, menu::player::get_local_player().m_entity, 0);
		});
	}

	void give_wanted_level(menu::player::player_context& player, int level) {
		native::report_crime(player.m_id, 8, native::get_wanted_level_threshold(level));
	}

	void cage_player(menu::player::player_context& player, int type) {
		if (type == 1) {
			menu::control::request_model(0x466EB7B8, [=] (uint32_t model) {
				math::vector3<float> min_dimensions;
				math::vector3<float> max_dimensions;

				native::get_model_dimensions(model, &min_dimensions, &max_dimensions);
				math::vector3<float> diameter = max_dimensions - min_dimensions;

				math::vector3<float> spawn_coords = native::get_offset_from_entity_in_world_coords(player.m_ped, -1.5f, -1.5f, 0.f);
				native::get_ground_z_for_3d_coord(spawn_coords.x, spawn_coords.y, spawn_coords.z, &spawn_coords.z, false);

				Object first_object = native::create_object(model, spawn_coords.x, spawn_coords.y, spawn_coords.z, true, true, false);
				if (native::does_entity_exist(first_object)) {
					float rotation = player.m_heading;
					native::set_entity_rotation(first_object, 0.f, 0.f, rotation, 2, false);
					native::freeze_entity_position(first_object, true);

					Object next_object = first_object;
					for (int i = 0; i < 3; i++) {
						rotation += 90.f;

						math::vector3<float> next = native::get_offset_from_entity_in_world_coords(next_object, diameter.x, 0.f, 0.f);
						next_object = native::create_object(model, next.x, next.y, next.z, true, true, false);
						if (native::does_entity_exist(next_object)) {
							native::set_entity_rotation(next_object, 0.f, 0.f, rotation, 2, false);
							native::freeze_entity_position(next_object, true);
						}
					}
				}
			});
		} else {
			menu::control::request_model(0x7B059043, [=] (uint32_t model) {
				Object cage = native::create_object(model, player.m_coords.x, player.m_coords.y, player.m_coords.z - 1.f, true, true, false);
				native::freeze_entity_position(cage, true);

				cage = native::create_object(model, player.m_coords.x, player.m_coords.y, player.m_coords.z + 1.f, true, true, false);
				native::freeze_entity_position(cage, true);
				native::set_entity_rotation(cage, 0.f, 180.f, 90.f, 0, false);
			});
		}
	}

	void ceo_ban(menu::player::player_context& player) {
		menu::helpers::trigger_script_event({ rage::global::ban_from_ceo, player.m_id, 1 }, 3, player.m_id);
	}

	void ceo_kick(menu::player::player_context& player) {
		menu::helpers::trigger_script_event({ rage::global::kick_from_ceo, player.m_id, 1, 5 }, 4, player.m_id);
	}

	void set_on_fire(menu::player::player_context& player) {
		if (!player.m_in_vehicle) {
			if (native::get_entity_speed(player.m_ped) > 1.5f) {
				math::vector3<float> fvector = native::get_entity_forward_vector(player.m_ped);

				for (int i = 1; i <= 3; i++) {
					math::vector3<float> coords = player.m_coords + (fvector * (float)i);
					native::start_script_fire(coords.x, coords.y, coords.z, 5, true);
				}
			} else {
				native::start_script_fire(player.m_coords.x, player.m_coords.y, player.m_coords.z, 5, true);
			}
		}
	}

	void blame(menu::player::player_context& player) {
		menu::player::for_each([=] (menu::player::player_context& p) {
			native::add_owned_explosion(player.m_ped, p.m_coords.x, p.m_coords.y, p.m_coords.z, 1, 10.f, true, false, 0.f);
		});
	}

	void send_to_island(menu::player::player_context& player) {
		menu::helpers::trigger_script_event({ rage::global::island_teleport, player.m_id, 0, 1, 1, }, 5, player.m_id);
	}

	void ram(menu::player::player_context& player, int type) {
		menu::control::request_model(ram_vehicles[type].m_result, [=] (uint32_t model) {
			Vehicle vehicle = native::create_vehicle(model, player.m_coords.x, player.m_coords.y, player.m_coords.z, 0.f, true, false, 1);
			if (native::does_entity_exist(vehicle)) {
				native::set_vehicle_out_of_control(vehicle, true, true);
				native::set_entity_heading(vehicle, player.m_heading - 90.f);
				native::set_vehicle_forward_speed(vehicle, 100.f);
				native::set_model_as_no_longer_needed(model);
			}
		});
	}

	void clone_player(menu::player::player_context& player, int type) {
		Ped cloned = native::clone_ped(player.m_ped, player.m_heading, true, true);
		if (type == 1 && native::does_entity_exist(cloned)) {
			native::give_weapon_to_ped(cloned, 0x7fd62962, 9999, true, true);
			native::task_combat_ped(cloned, player.m_ped, 0, 16);
			native::set_ped_keep_task(cloned, true);
		}
	}

	void send_message(menu::player::player_context& player, int type) {
		std::vector<int> args = {
			rage::global::message_handler,
			player.m_id,
			messages[type].m_result,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			player.m_id
		};

		switch (type) {
			case 9:
				args[3] = 1;
				break;

			case 10:
				args[3] = 100;
				break;

			case 11:
				args[3] = std::numeric_limits<int>::max();
				break;
		}

		menu::helpers::trigger_script_event(args, 14, player.m_id);
	}
}

void network_players_abusive_menu::load() {
	set_name("Abusive");
	set_parent<network_players_selected_menu>();

	for (scroll_struct<uint32_t>& veh : ram_vehicles) {
		veh.m_name.set(native::get_label_text(native::get_display_name_from_vehicle_model(veh.m_result)));
	}

	add_option(submenu_option("Attackers")
		.add_translate()
		.add_submenu<network_players_abusive_attackers_menu>());

	add_option(submenu_option("Custom Explosions")
		.add_translate()
		.add_submenu<network_players_abusive_explosions_menu>());

	add_option(toggle_option("Freeze")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_freeze)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_freeze);
			} else {
				option->add_toggle(m_vars.m_freeze);
			}
		}));

	add_option(toggle_option("Explode")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_simple_explode)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_simple_explode);
			} else {
				option->add_toggle(m_vars.m_simple_explode);
			}
		}));

	add_option(toggle_option("Kick From Vehicle")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_kick_from_vehicle)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_kick_from_vehicle);
			} else {
				option->add_toggle(m_vars.m_kick_from_vehicle);
			}
		})
		.add_tooltip("Interval: 1s"));

	add_option(scroll_option<int>(TOGGLE, "Cage")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_cage_type, 0, NUMOF(cages), cages)
		.add_toggle(menu::player::get_selected_player().m_cage)
		.add_update([] (scroll_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_cage_type, 0, NUMOF(cages), cages);
				option->add_toggle(menu::player::get_selected_player().m_cage);
			} else {
				option->add_scroll(m_vars.m_cage_type, 0, NUMOF(cages), cages);
				option->add_toggle(m_vars.m_cage);
			}
		})
		.add_tooltip("Interval: 1s. Selected player has priority over session"));

	add_option(scroll_option<int>(TOGGLE, "CEO")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_ceo_type, 0, NUMOF(ceos), ceos)
		.add_toggle(menu::player::get_selected_player().m_ceo)
		.add_update([] (scroll_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_ceo_type, 0, NUMOF(ceos), ceos);
				option->add_toggle(menu::player::get_selected_player().m_ceo);
			} else {
				option->add_scroll(m_vars.m_ceo_type, 0, NUMOF(ceos), ceos);
				option->add_toggle(m_vars.m_ceo);
			}
		})
		.add_tooltip("Interval: 1s. Selected player has priority over session"));

	add_option(toggle_option("Set On Fire")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_set_on_fire)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_set_on_fire);
			} else {
				option->add_toggle(m_vars.m_set_on_fire);
			}
		})
		.add_tooltip("Interval: 5s"));

	add_option(toggle_option("Taze")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_taze)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_taze);
			} else {
				option->add_toggle(m_vars.m_taze);
			}
		})
		.add_tooltip("Interval: 5s"));

	add_option(toggle_option("Ragdoll")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_ragdoll)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_ragdoll);
			} else {
				option->add_toggle(m_vars.m_ragdoll);
			}
		})
		.add_tooltip("Interval: 1s"));

	add_option(toggle_option("Glitch Physics")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_glitch_physics)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_glitch_physics);
			} else {
				option->add_toggle(m_vars.m_glitch_physics);
			}
		})
		.add_tooltip("Interval: 1s"));

	add_option(toggle_option("Forcefield")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_forcefield)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_forcefield);
			} else {
				option->add_toggle(m_vars.m_forcefield);
			}
		}));

	add_option(toggle_option("Blame")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_blame)
		.add_update([] (toggle_option* option, int pos) {
			option->add_toggle(menu::player::get_selected_player().m_blame);
		})
		.add_requirement([] { return global::vars::g_network_menu_type == SELECTED_PLAYER; })
		.add_tooltip("Interval: 5s"));

	add_option(toggle_option("Rain Rockets")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_rain_rockets)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_rain_rockets);
			} else {
				option->add_toggle(m_vars.m_rain_rockets);
			}
		})
		.add_tooltip("Interval: 750ms"));

	add_option(toggle_option("Send to Island")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_send_to_island)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_send_to_island);
			} else {
				option->add_toggle(m_vars.m_send_to_island);
			}
		})
		.add_tooltip("Interval: 5s"));

	add_option(toggle_option("Always Wanted")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_always_wanted)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_always_wanted);
			} else {
				option->add_toggle(m_vars.m_always_wanted);
			}
		}));

	add_option(scroll_option<uint32_t>(TOGGLE, "Vehicle Ram")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_vehicle_ram_type, 0, NUMOF(ram_vehicles), ram_vehicles)
		.add_toggle(menu::player::get_selected_player().m_vehicle_ram)
		.add_update([] (scroll_option<uint32_t>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_vehicle_ram_type, 0, NUMOF(ram_vehicles), ram_vehicles);
				option->add_toggle(menu::player::get_selected_player().m_vehicle_ram);
			} else {
				option->add_scroll(m_vars.m_vehicle_ram_type, 0, NUMOF(ram_vehicles), ram_vehicles);
				option->add_toggle(m_vars.m_vehicle_ram);
			}
		})
		.add_tooltip("Interval: 2.5s. Selected player has priority over session"));

	add_option(scroll_option<int>(TOGGLE, "Clone")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_clone_type, 0, NUMOF(clone), clone)
		.add_toggle(menu::player::get_selected_player().m_clone)
		.add_update([] (scroll_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_clone_type, 0, NUMOF(clone), clone);
				option->add_toggle(menu::player::get_selected_player().m_clone);
			} else {
				option->add_scroll(m_vars.m_clone_type, 0, NUMOF(clone), clone);
				option->add_toggle(m_vars.m_clone);
			}
		})
		.add_tooltip("Interval: 1s. Selected player has priority over session"));

	add_option(toggle_option("Hostile Peds")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_hostile_peds)
		.add_update([] (toggle_option* option, int pos) {
			option->add_toggle(menu::player::get_selected_player().m_hostile_peds);
		})
		.add_requirement([] { return global::vars::g_network_menu_type == SELECTED_PLAYER; })
		.add_tooltip("You have to be near them for it to take affect"));

	add_option(toggle_option("Hostile Traffic")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_hostile_vehicles)
		.add_update([] (toggle_option* option, int pos) {
			option->add_toggle(menu::player::get_selected_player().m_hostile_vehicles);
		})
		.add_requirement([] { return global::vars::g_network_menu_type == SELECTED_PLAYER; })
		.add_tooltip("You have to be near them for it to take affect"));

	add_option(scroll_option<int>(TOGGLE, "Show Message")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_show_message_type, 0, NUMOF(messages), messages)
		.add_toggle(menu::player::get_selected_player().m_show_message)
		.add_update([] (scroll_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_show_message_type, 0, NUMOF(messages), messages);
				option->add_toggle(menu::player::get_selected_player().m_show_message);
			} else {
				option->add_scroll(m_vars.m_show_message_type, 0, NUMOF(messages), messages);
				option->add_toggle(m_vars.m_show_message);
			}
		})
		.add_tooltip("Interval: 500ms. Selected player has priority over session"));

	/*add_option(toggle_option("Fake Money Drop")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_fake_money_drop)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_fake_money_drop);
			} else {
				option->add_toggle(m_vars.m_fake_money_drop);
			}
		}));*/
}

void network_players_abusive_menu::update() {}

void network_players_abusive_menu::update_once() {
	if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
		set_parent<network_players_selected_menu>();
	} else {
		set_parent<network_session_menu>();
	}
}

void network_players_abusive_menu::feature_update() {
	menu::player::for_each([] (menu::player::player_context& player) {
		bool excluded = menu::player::is_excluded(player.m_id);

		if (player.m_freeze || m_vars.m_freeze) {
			if (!(excluded && !player.m_freeze)) {
				native::clear_ped_tasks_immediately(player.m_ped);
			}
		}

		if (player.m_simple_explode || m_vars.m_simple_explode) {
			if (!(excluded && !player.m_freeze)) {
				native::add_explosion(player.m_coords.x, player.m_coords.y, player.m_coords.z, 0, 10.f, true, false, 0.f, false);
			}
		}

		if (player.m_kick_from_vehicle || m_vars.m_kick_from_vehicle) {
			if (!(excluded && !player.m_kick_from_vehicle)) {
				menu::timers::run_timed(&player.m_kick_from_vehicle_timer, 1000, [&] {
					kick_from_vehicle(player);
				});
			}
		}

		if (player.m_taze || m_vars.m_taze) {
			if (!(excluded && !player.m_taze)) {
				menu::timers::run_timed(&player.m_taze_timer, 5000, [&] {
					taze(player);
				});
			}
		}

		if (player.m_ragdoll || m_vars.m_ragdoll) {
			if (!(excluded && !player.m_ragdoll)) {
				menu::timers::run_timed(&player.m_ragdoll_timer, 1000, [&] {
					ragdoll(player);
				});
			}
		}

		if (player.m_glitch_physics || m_vars.m_glitch_physics) {
			if (!(excluded && !player.m_glitch_physics)) {
				menu::timers::run_timed(&player.m_glitch_physics_timer, 1000, [&] {
					Object guitar = native::get_closest_object_of_type(player.m_coords.x, player.m_coords.y, player.m_coords.z, 5.f, 0xd5c0bc07, false, false, false);
					if (!guitar || !native::does_entity_exist(guitar) || !native::is_entity_attached_to_entity(guitar, player.m_ped)) {
						glitch_physics(player);
					}
				});
			}
		}

		if (player.m_forcefield || m_vars.m_forcefield) {
			if (!(excluded && !player.m_forcefield)) {
				native::add_explosion(player.m_coords.x, player.m_coords.y, player.m_coords.z, 29, 100.f, false, true, 0.f, true);
			}
		}

		if (player.m_rain_rockets || m_vars.m_rain_rockets) {
			if (!(excluded && !player.m_rain_rockets)) {
				menu::timers::run_timed(&player.m_rain_rockets_timer, 750, [&] {
					rain_rockets(player);
				});
			}
		}

		if (player.m_always_wanted || m_vars.m_always_wanted) {
			if (!(excluded && !player.m_always_wanted)) {
				give_wanted_level(player, 5);
			}
		}

		if (player.m_cage || m_vars.m_cage) {
			if (!(excluded && !player.m_cage)) {
				menu::timers::run_timed(&player.m_glitch_physics_timer, 1000, [&] {
					int type = player.m_cage ? player.m_cage_type : m_vars.m_cage_type;
					if (type == 1) {
						Object fence = native::get_closest_object_of_type(player.m_coords.x, player.m_coords.y, player.m_coords.z, 5.f, 0x466EB7B8, false, false, false);
						if (!fence || !native::does_entity_exist(fence)) {
							cage_player(player, type);
						}
					} else {
						Object fence = native::get_closest_object_of_type(player.m_coords.x, player.m_coords.y, player.m_coords.z, 5.f, 0x7B059043, false, false, false);
						if (!fence || !native::does_entity_exist(fence)) {
							cage_player(player, type);
						}
					}
				});
			}
		}

		if (player.m_ceo || m_vars.m_ceo) {
			if (!(excluded && !player.m_ceo)) {
				menu::timers::run_timed(&player.m_ceo_timer, 1000, [&] {
					int type = player.m_ceo ? player.m_ceo_type : m_vars.m_ceo_type;

					if (type == 0) {
						ceo_kick(player);
					} else ceo_ban(player);
				});
			}
		}

		if (player.m_set_on_fire || m_vars.m_set_on_fire) {
			if (!(excluded && !player.m_set_on_fire)) {
				menu::timers::run_timed(&player.m_set_on_fire_timer, 5000, [&] {
					set_on_fire(player);
				});
			}
		}

		if (player.m_send_to_island || m_vars.m_send_to_island) {
			if (!(excluded && !player.m_send_to_island)) {
				menu::timers::run_timed(&player.m_send_to_island_timer, 5000, [&] {
					send_to_island(player);
				});
			}
		}

		if (player.m_vehicle_ram || m_vars.m_vehicle_ram) {
			if (!(excluded && !player.m_vehicle_ram)) {
				menu::timers::run_timed(&player.m_vehicle_ram_timer, 2500, [&] {
					int type = player.m_vehicle_ram ? player.m_vehicle_ram_type : m_vars.m_vehicle_ram_type;
					ram(player, type);
				});
			}
		}

		if (player.m_clone || m_vars.m_clone) {
			if (!(excluded && !player.m_clone)) {
				menu::timers::run_timed(&player.m_clone_timer, 2500, [&] {
					int type = player.m_clone ? player.m_clone_type : m_vars.m_clone_type;
					clone_player(player, type);
				});
			}
		}

		if (player.m_show_message || m_vars.m_show_message) {
			if (!(excluded && !player.m_show_message)) {
				menu::timers::run_timed(&player.m_show_message_timer, 500, [&] {
					int type = player.m_show_message ? player.m_show_message_type : m_vars.m_show_message_type;
					send_message(player, type);
				});
			}
		}

		if (player.m_fake_money_drop || m_vars.m_fake_money_drop) {
			if (!(excluded && !player.m_fake_money_drop)) {
				menu::timers::run_timed(&player.m_fake_money_drop_timer, 500, [&] {
					native::create_ambient_pickup(0x1e9a99f8, player.m_coords.x, player.m_coords.y, player.m_coords.z, 0, 0, 0x113fd533, 0, 1);
				});
			}
		}

		if (player.m_blame) {
			if (!(excluded && !player.m_blame)) {
				menu::timers::run_timed(&player.m_blame_timer, 5000, [&] {
					blame(player);
				});
			}
		}

		if (player.m_hostile_peds) {
			menu::timers::run_timed(&player.m_hostile_peds_timer, 1000, [=] {
				global::vars::g_ped_pool->for_each([=] (Entity ped, void* p) {
					if (!native::is_ped_a_player(ped)) {
						if (native::get_entity_coords(ped, true).get_distance(player.m_coords) < 100.f) {
							native::give_weapon_to_ped(ped, 0x7FD62962, 9999, true, true);
							native::task_combat_ped(ped, player.m_ped, 0, 16);
							native::set_ped_keep_task(ped, true);
						}
					}
				});
			});
		}

		if (player.m_hostile_vehicles) {
			menu::timers::run_timed(&player.m_hostile_vehicles_timer, 1000, [=] {
				global::vars::g_vehicle_pool->for_each([=] (Entity veh, void* v) {
					if (native::get_entity_coords(veh, true).get_distance(player.m_coords) < 200.f) {
						if (!native::is_this_model_a_train(native::get_entity_model(veh))) {
							Ped ped = native::get_ped_in_vehicle_seat(veh, -1, 1);
							if (native::does_entity_exist(ped)) {
								native::task_vehicle_drive_to_coord(ped, veh, player.m_coords.x, player.m_coords.y, player.m_coords.z, 100, 1, native::get_entity_model(veh), 16777216, 4, -1);
							}
						}
					}
				});
			});
		}
	}, true);
}

network_players_abusive_menu* g_instance;
network_players_abusive_menu* network_players_abusive_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_abusive_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}