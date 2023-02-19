#include "network_players_vehicle.h"
#include "menu/base/submenu_handler.h"
#include "network_players_selected.h"
#include "menu/base/submenus/main/vehicle.h"
#include "menu/base/submenus/main/vehicle/vehicle_movement.h"
#include "global/lists.h"
#include "menu/base/submenus/main/network/network_session.h"

using namespace network::players::vehicle::vars;

namespace network::players::vehicle::vars {
	variables m_vars;
}

void network_players_vehicle_menu::load() {
	set_name("Vehicle");
	set_parent<network_players_selected_menu>();

	add_option(toggle_option("Godmode")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_vehicle_godmode)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_vehicle_godmode);
			} else {
				option->add_toggle(m_vars.m_vehicle_godmode);
			}
		}));

	add_option(scroll_option<int>(SCROLLSELECT, "Upgrades")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_vehicle_upgrades, 0, NUMOF(vehicle::vars::upgrades), vehicle::vars::upgrades)
		.add_update([] (scroll_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_vehicle_upgrades, 0, NUMOF(vehicle::vars::upgrades), vehicle::vars::upgrades);
			} else {
				option->add_scroll(m_vars.m_vehicle_upgrades, 0, NUMOF(vehicle::vars::upgrades), vehicle::vars::upgrades);
			}
		})
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_in_vehicle) {
					vehicle::vars::max_upgrades(menu::player::get_selected_player().m_vehicle, menu::player::get_selected_player().m_vehicle_upgrades);
				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					if (player.m_in_vehicle) {
						vehicle::vars::max_upgrades(player.m_vehicle, player.m_vehicle_upgrades);
					}
				});
			}
		}));

	add_option(scroll_option<int>(SCROLLSELECT, "Downgrades")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_vehicle_downgrades, 0, NUMOF(vehicle::vars::upgrades), vehicle::vars::upgrades)
		.add_update([] (scroll_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_vehicle_downgrades, 0, NUMOF(vehicle::vars::upgrades), vehicle::vars::upgrades);
			} else {
				option->add_scroll(m_vars.m_vehicle_downgrades, 0, NUMOF(vehicle::vars::upgrades), vehicle::vars::upgrades);
			}
		})
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_in_vehicle) {
					vehicle::vars::low_upgrades(menu::player::get_selected_player().m_vehicle, menu::player::get_selected_player().m_vehicle_downgrades);
				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					if (player.m_in_vehicle) {
						vehicle::vars::low_upgrades(player.m_vehicle, player.m_vehicle_downgrades);
					}
				});
			}
		}));

	add_option(scroll_option<std::pair<math::vector3_<float>, math::vector3_<float>>>(SCROLLSELECT, "Acrobatics")
		.add_translate()
		.add_scroll(menu::player::get_selected_player().m_vehicle_acrobatics, 0, NUMOF(global::lists::g_acrobatics), global::lists::g_acrobatics)
		.add_update([] (scroll_option<std::pair<math::vector3_<float>, math::vector3_<float>>>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_scroll(menu::player::get_selected_player().m_vehicle_acrobatics, 0, NUMOF(global::lists::g_acrobatics), global::lists::g_acrobatics);
			} else {
				option->add_scroll(m_vars.m_vehicle_acrobatics, 0, NUMOF(global::lists::g_acrobatics), global::lists::g_acrobatics);
			}
		})
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_in_vehicle) {
					vehicle::movement::vars::run_acrobatic(menu::player::get_selected_player().m_vehicle, global::lists::g_acrobatics[menu::player::get_selected_player().m_vehicle_acrobatics].m_result);
				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					if (player.m_in_vehicle) {
						vehicle::movement::vars::run_acrobatic(player.m_vehicle, global::lists::g_acrobatics[m_vars.m_vehicle_acrobatics].m_result);
					}
				});
			}
		}));

	add_option(button_option("Repair Vehicle")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_in_vehicle) {
					vehicle::vars::run_task(menu::player::get_selected_player().m_vehicle, [] (Vehicle veh) { native::set_vehicle_fixed(veh); });
				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					if (player.m_in_vehicle) {
						vehicle::vars::run_task(player.m_vehicle, [] (Vehicle veh) { native::set_vehicle_fixed(veh); });
					}
				});
			}
		}));

	add_option(number_option<int>(SCROLLSELECT, "Boost Forwards")
		.add_translate()
		.add_number(menu::player::get_selected_player().m_vehicle_boost_forwards, "%i", 1).add_min(0).add_max(5000).set_scroll_speed(10).show_max()
		.add_update([] (number_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_number(menu::player::get_selected_player().m_vehicle_boost_forwards, "%i", 1);
			} else {
				option->add_number(m_vars.m_vehicle_boost_forwards, "%i", 1);
			}
		})
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_in_vehicle) {
					vehicle::vars::run_task(menu::player::get_selected_player().m_vehicle, [] (Vehicle veh) {
						native::set_vehicle_forward_speed(veh, menu::player::get_selected_player().m_vehicle_boost_forwards + native::get_entity_speed(veh));
					});
				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					if (player.m_in_vehicle) {
						vehicle::vars::run_task(player.m_vehicle, [] (Vehicle veh) {
							native::set_vehicle_forward_speed(veh, m_vars.m_vehicle_boost_forwards + native::get_entity_speed(veh));
						});
					}
				});
			}
		}));

	add_option(number_option<int>(SCROLLSELECT, "Boost Backwards")
		.add_translate()
		.add_number(menu::player::get_selected_player().m_vehicle_boost_backwards, "%i", 1).add_min(0).add_max(5000).set_scroll_speed(10).show_max()
		.add_update([] (number_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_number(menu::player::get_selected_player().m_vehicle_boost_backwards, "%i", 1);
			} else {
				option->add_number(m_vars.m_vehicle_boost_backwards, "%i", 1);
			}
		})
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_in_vehicle) {
					vehicle::vars::run_task(menu::player::get_selected_player().m_vehicle, [] (Vehicle veh) {
						native::set_vehicle_forward_speed(veh, (float)-menu::player::get_selected_player().m_vehicle_boost_backwards);
					});

				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					if (player.m_in_vehicle) {
						vehicle::vars::run_task(player.m_vehicle, [] (Vehicle veh) {
							native::set_vehicle_forward_speed(veh, (float)-m_vars.m_vehicle_boost_backwards);
						});
					}
				});
			}
		}));

	add_option(button_option("Kill Engine")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_in_vehicle) {
					vehicle::vars::run_task(menu::player::get_selected_player().m_vehicle, [] (Vehicle veh) {
						native::set_vehicle_engine_health(veh, -4000.f);
					});
				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					if (player.m_in_vehicle) {
						vehicle::vars::run_task(player.m_vehicle, [] (Vehicle veh) {
							native::set_vehicle_engine_health(veh, -4000.f);
						});
					}
				});
			}
		}));

	add_option(button_option("Burst Tires")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_in_vehicle) {
					vehicle::vars::run_task(menu::player::get_selected_player().m_vehicle, [] (Vehicle veh) {
						native::set_vehicle_tyres_can_burst(veh, true);
						for (int id = 0; id < 8; id++) {
							native::set_vehicle_tyre_burst(veh, id, true, 1000.f);
						}
					});
				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					if (player.m_in_vehicle) {
						vehicle::vars::run_task(player.m_vehicle, [] (Vehicle veh) {
							native::set_vehicle_tyres_can_burst(veh, true);
							for (int id = 0; id < 8; id++) {
								native::set_vehicle_tyre_burst(veh, id, true, 1000.f);
							}
						});
					}
				});
			}
		}));

	add_option(button_option("Break Windows")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_in_vehicle) {
					vehicle::vars::run_task(menu::player::get_selected_player().m_vehicle, [] (Vehicle veh) {
						for (int id = 0; id < 8; id++) {
							native::smash_vehicle_window(veh, id);
						}
					});
				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					if (player.m_in_vehicle) {
						vehicle::vars::run_task(player.m_vehicle, [] (Vehicle veh) {
							for (int id = 0; id < 8; id++) {
								native::smash_vehicle_window(veh, id);
							}
						});
					}
				});
			}
		}));

	add_option(toggle_option("Disable Full Collision")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_vehicle_disable_collision)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_vehicle_disable_collision);
			} else {
				option->add_toggle(m_vars.m_vehicle_disable_collision);
			}
		}));

	add_option(toggle_option("Slippy Wheels")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_vehicle_slippy_wheels)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_vehicle_slippy_wheels);
			} else {
				option->add_toggle(m_vars.m_vehicle_slippy_wheels);
			}
		}));

	add_option(button_option("Stop")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_in_vehicle) {
					vehicle::vars::run_task(menu::player::get_selected_player().m_vehicle, [] (Vehicle veh) {
						native::set_vehicle_forward_speed(veh, 0.f);
					});
				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					if (player.m_in_vehicle) {
						vehicle::vars::run_task(player.m_vehicle, [] (Vehicle veh) {
							native::set_vehicle_forward_speed(veh, 0.f);
						});
					}
				});
			}
		}));

	add_option(button_option("Place on Ground")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_in_vehicle) {
					vehicle::vars::run_task(menu::player::get_selected_player().m_vehicle, [] (Vehicle veh) {
						native::set_vehicle_on_ground_properly(veh, 0);
					});
				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					if (player.m_in_vehicle) {
						vehicle::vars::run_task(player.m_vehicle, [] (Vehicle veh) {
							native::set_vehicle_on_ground_properly(veh, 0);
						});
					}
				});
			}
		}));

	add_option(button_option("Kick All Seats")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_in_vehicle) {
					vehicle::vars::run_task(menu::player::get_selected_player().m_vehicle, [] (Vehicle veh) {
						for (int i = -1; i < native::get_vehicle_max_number_of_passengers(veh); i++) {
							if (!native::is_vehicle_seat_free(veh, i, 0)) {
								native::clear_ped_tasks_immediately(native::get_ped_in_vehicle_seat(veh, i, 0));
							}
						}
					});
				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					if (player.m_in_vehicle) {
						vehicle::vars::run_task(player.m_vehicle, [] (Vehicle veh) {
							for (int i = -1; i < native::get_vehicle_max_number_of_passengers(veh); i++) {
								if (!native::is_vehicle_seat_free(veh, i, 0)) {
									native::clear_ped_tasks_immediately(native::get_ped_in_vehicle_seat(veh, i, 0));
								}
							}
						});
					}
				});
			}
		}));

	add_option(button_option("Kick Driver")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_in_vehicle) {
					vehicle::vars::run_task(menu::player::get_selected_player().m_vehicle, [] (Vehicle veh) {
						if (!native::is_vehicle_seat_free(veh, -1, 0)) {
							native::clear_ped_tasks_immediately(native::get_ped_in_vehicle_seat(veh, -1, 0));
						}
					});
				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					if (player.m_in_vehicle) {
						vehicle::vars::run_task(player.m_vehicle, [] (Vehicle veh) {
							if (!native::is_vehicle_seat_free(veh, -1, 0)) {
								native::clear_ped_tasks_immediately(native::get_ped_in_vehicle_seat(veh, -1, 0));
							}
						});
					}
				});
			}
		}));

	add_option(button_option("Lock Doors")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_in_vehicle) {
					vehicle::vars::run_task(menu::player::get_selected_player().m_vehicle, [] (Vehicle veh) {
						native::set_vehicle_doors_locked(veh, 4);
					});
				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					if (player.m_in_vehicle) {
						vehicle::vars::run_task(player.m_vehicle, [] (Vehicle veh) {
							native::set_vehicle_doors_locked(veh, 4);
						});
					}
				});
			}
		}));

	add_option(button_option("Unlock Doors")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_in_vehicle) {
					vehicle::vars::run_task(menu::player::get_selected_player().m_vehicle, [] (Vehicle veh) {
						native::set_vehicle_doors_locked(veh, 0);
					});
				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					if (player.m_in_vehicle) {
						vehicle::vars::run_task(player.m_vehicle, [] (Vehicle veh) {
							native::set_vehicle_doors_locked(veh, 0);
						});
					}
				});
			}
		}));

	add_option(number_option<int>(SCROLLSELECT, "Rotate")
		.add_translate()
		.add_number(menu::player::get_selected_player().m_vehicle_rotate, "%i", 10).add_min(10).add_max(360)
		.add_update([] (number_option<int>* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_number(menu::player::get_selected_player().m_vehicle_rotate, "%i", 10);
			} else {
				option->add_number(m_vars.m_vehicle_rotate, "%i", 10);
			}
		})
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_in_vehicle) {
					vehicle::vars::run_task(menu::player::get_selected_player().m_vehicle, [] (Vehicle veh) {
						math::vector3<float> rotation = native::get_entity_rotation(veh, 2);
						native::set_entity_rotation(veh, rotation.x, rotation.y, rotation.z + (float)menu::player::get_selected_player().m_vehicle_rotate, 2, true);
					});
				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					if (player.m_in_vehicle) {
						vehicle::vars::run_task(player.m_vehicle, [] (Vehicle veh) {
							math::vector3<float> rotation = native::get_entity_rotation(veh, 2);
							native::set_entity_rotation(veh, rotation.x, rotation.y, rotation.z + (float)m_vars.m_vehicle_rotate, 2, true);
						});
					}
				});
			}
		}));

	add_option(button_option("Clone")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_in_vehicle) {
					vehicle::vars::run_task(menu::player::get_selected_player().m_vehicle, [] (Vehicle veh) {
						vehicle::vars::clone_vehicle(veh);
					});
				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					if (player.m_in_vehicle) {
						vehicle::vars::run_task(player.m_vehicle, [] (Vehicle veh) {
							vehicle::vars::clone_vehicle(veh);
						});
					}
				});
			}
		}));

	add_option(button_option("Delete")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				if (menu::player::get_selected_player().m_in_vehicle) {
					vehicle::vars::run_task(menu::player::get_selected_player().m_vehicle, [] (Vehicle veh) {
						native::set_entity_as_mission_entity(veh, true, true);
						native::delete_entity(&veh);
					});
				}
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					if (player.m_in_vehicle) {
						vehicle::vars::run_task(player.m_vehicle, [] (Vehicle veh) {
							native::set_entity_as_mission_entity(veh, true, true);
							native::delete_entity(&veh);
						});
					}
				});
			}
		}));
}

void network_players_vehicle_menu::update() {}

void network_players_vehicle_menu::update_once() {
	if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
		set_parent<network_players_selected_menu>();
	} else {
		set_parent<network_session_menu>();
	}
}

void network_players_vehicle_menu::feature_update() {
	menu::player::for_each([] (menu::player::player_context& player) {
		bool excluded = menu::player::is_excluded(player.m_id);

		if (player.m_vehicle_godmode || m_vars.m_vehicle_godmode) {
			if (!(excluded && !player.m_vehicle_godmode)) {
				if (player.m_in_vehicle) {
					vehicle::vars::run_task(player.m_vehicle, [] (Entity veh) {
						native::set_entity_invincible(veh, false);
					});
				}
			}
		}

		if (player.m_vehicle_disable_collision || m_vars.m_vehicle_disable_collision) {
			if (!(excluded && !player.m_vehicle_disable_collision)) {
				if (player.m_in_vehicle) {
					vehicle::vars::run_task(player.m_vehicle, [] (Entity veh) {
						native::set_entity_collision(veh, false, true);
					});
				}
			}
		}

		if (player.m_vehicle_slippy_wheels || m_vars.m_vehicle_slippy_wheels) {
			if (!(excluded && !player.m_vehicle_slippy_wheels)) {
				if (player.m_in_vehicle) {
					vehicle::vars::run_task(player.m_vehicle, [] (Entity veh) {
						native::set_vehicle_reduce_grip(veh, true);
					});
				}
			}
		}

		if (player.m_vehicle_freeze || m_vars.m_vehicle_freeze) {
			if (!(excluded && !player.m_vehicle_freeze)) {
				if (player.m_in_vehicle) {
					vehicle::vars::run_task(player.m_vehicle, [] (Entity veh) {
						native::freeze_entity_position(veh, true);
					});
				}
			}
		}
	}, true);
}

network_players_vehicle_menu* g_instance;
network_players_vehicle_menu* network_players_vehicle_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_vehicle_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}