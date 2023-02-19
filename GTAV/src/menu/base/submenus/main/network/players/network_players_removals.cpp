#include "network_players_removals.h"
#include "menu/base/submenu_handler.h"
#include "network_players_selected.h"
#include "util/fiber_pool.h"
#include "util/fiber.h"
#include "util/log.h"
#include "menu/base/submenus/main/network/network_host_toolkit.h"
#include "menu/base/util/global.h"
#include "menu/base/util/control.h"
#include "menu/base/util/helpers.h"
#include "rage/types/global_types.h"
#include "rage/engine.h"
#include "menu/base/submenus/main/network/network_session.h"
#include "global/lists.h"

using namespace network::players::removals::vars;

namespace network::players::removals::vars {
	variables m_vars;

	void script_host_kick(menu::player::player_context& player, bool everyone) {
		if (network::htoolkit::vars::force_host_of_script("freemode")) {
			if (everyone) {
				menu::player::for_each([] (menu::player::player_context& p) {
					menu::script_global(rage::global::host_drop_kick + p.m_id + 1).as<int>() = 1;
				});
			} else {
				menu::script_global(rage::global::host_drop_kick + player.m_id + 1).as<int>() = 1;
			}
		}
	}

	void session_host_kick(menu::player::player_context& player, bool everyone) {
		if (rage::engine::get_host_net_game_player() == menu::player::get_local_player().m_net_player) {
			if (everyone) {
				menu::player::for_each([] (menu::player::player_context& p) {
					native::network_session_kick_player(p.m_id);
				});
			} else {
				if (player.m_net_player != menu::player::get_local_player().m_net_player) {
					native::network_session_kick_player(player.m_id);
				}
			}
		} else {
			menu::notify::stacked(network_players_removals_menu::get()->get_name().get(), network_players_removals_menu::get()->get_string("You need to be host to use this kick"));
		}
	}

	void break_freemode_kick(menu::player::player_context& player, bool everyone) {
		if (everyone) {
			menu::player::for_each([] (menu::player::player_context& p) {
				if (rage::engine::get_host_net_game_player() != p.m_net_player) {
					menu::helpers::trigger_script_event({ -966559987, 18707275, 55963135, 20806885, 56512451, -21520996 }, 6, p.m_id);
					menu::helpers::trigger_script_event({ -1054826273, -33111572, -28521729, -7891846 }, 4, p.m_id);
					menu::helpers::trigger_script_event({ -1729804184, 31689453, 91436768, 9588623, -50805664, -10510254 }, 6, p.m_id);
				}
			});
		} else {
			if (rage::engine::get_host_net_game_player() == player.m_net_player) {
				menu::notify::stacked(network_players_removals_menu::get()->get_name().get(), network_players_removals_menu::get()->get_string("You can't use this kick on the host"));
			} else {
				menu::helpers::trigger_script_event({ -966559987, 18707275, 55963135, 20806885, 56512451, -21520996 }, 6, player.m_id);
				menu::helpers::trigger_script_event({ -1054826273, -33111572, -28521729, -7891846 }, 4, player.m_id);
				menu::helpers::trigger_script_event({ -1729804184, 31689453, 91436768, 9588623, -50805664, -10510254 }, 6, player.m_id);
			}
		}
	}

	void spawn_entities(menu::player::player_context& player, bool everyone) {
		menu::control::request_model(global::lists::g_ped_model_popular[native::network_get_random_int_in_range(0, NUMOF(global::lists::g_ped_model_popular) - 1)].m_result, [=] (uint32_t model) {
			if (everyone) {
				menu::player::for_each([=] (menu::player::player_context& every) {
					native::create_ped(21, model, every.m_coords.x, every.m_coords.y, every.m_coords.z, 0.f, true, false);
				});

				return;
			}

			native::create_ped(21, model, player.m_coords.x, player.m_coords.y, player.m_coords.z, 0.f, true, false);
		});

		menu::control::request_model(global::lists::g_ped_model_story[native::network_get_random_int_in_range(0, NUMOF(global::lists::g_ped_model_story) - 1)].m_result, [=] (uint32_t model) {
			if (everyone) {
				menu::player::for_each([=] (menu::player::player_context& every) {
					native::create_ped(21, model, every.m_coords.x, every.m_coords.y, every.m_coords.z, 0.f, true, false);
				});

				return;
			}

			native::create_ped(21, model, player.m_coords.x, player.m_coords.y, player.m_coords.z, 0.f, true, false);
		});

		menu::control::request_model(global::lists::g_ped_model_animal[native::network_get_random_int_in_range(0, NUMOF(global::lists::g_ped_model_animal) - 1)].m_result, [=] (uint32_t model) {
			if (everyone) {
				menu::player::for_each([=] (menu::player::player_context& every) {
					native::create_ped(21, model, every.m_coords.x, every.m_coords.y, every.m_coords.z, 0.f, true, false);
				});

				return;
			}

			native::create_ped(21, model, player.m_coords.x, player.m_coords.y, player.m_coords.z, 0.f, true, false);
		});

		menu::control::request_model(global::lists::g_ped_model_emergency[native::network_get_random_int_in_range(0, NUMOF(global::lists::g_ped_model_emergency) - 1)].m_result, [=] (uint32_t model) {
			if (everyone) {
				menu::player::for_each([=] (menu::player::player_context& every) {
					native::create_ped(21, model, every.m_coords.x, every.m_coords.y, every.m_coords.z, 0.f, true, false);
				});

				return;
			}

			native::create_ped(21, model, player.m_coords.x, player.m_coords.y, player.m_coords.z, 0.f, true, false);
		});

		menu::control::request_model(global::lists::g_ped_model_role[native::network_get_random_int_in_range(0, NUMOF(global::lists::g_ped_model_role) - 1)].m_result, [=] (uint32_t model) {
			if (everyone) {
				menu::player::for_each([=] (menu::player::player_context& every) {
					native::create_ped(21, model, every.m_coords.x, every.m_coords.y, every.m_coords.z, 0.f, true, false);
				});

				return;
			}

			native::create_ped(21, model, player.m_coords.x, player.m_coords.y, player.m_coords.z, 0.f, true, false);
		});

		menu::control::request_model(global::lists::g_ped_model_ambient[native::network_get_random_int_in_range(0, NUMOF(global::lists::g_ped_model_ambient) - 1)].m_result, [=] (uint32_t model) {
			if (everyone) {
				menu::player::for_each([=] (menu::player::player_context& every) {
					native::create_ped(21, model, every.m_coords.x, every.m_coords.y, every.m_coords.z, 0.f, true, false);
				});

				return;
			}

			native::create_ped(21, model, player.m_coords.x, player.m_coords.y, player.m_coords.z, 0.f, true, false);
		});

		menu::control::request_model(global::lists::g_ped_model_misc[native::network_get_random_int_in_range(0, NUMOF(global::lists::g_ped_model_misc) - 1)].m_result, [=] (uint32_t model) {
			if (everyone) {
				menu::player::for_each([=] (menu::player::player_context& every) {
					native::create_ped(21, model, every.m_coords.x, every.m_coords.y, every.m_coords.z, 0.f, true, false);
				});

				return;
			}

			native::create_ped(21, model, player.m_coords.x, player.m_coords.y, player.m_coords.z, 0.f, true, false);
		});
	
		menu::control::request_model(global::lists::g_object_model_small[native::network_get_random_int_in_range(0, NUMOF(global::lists::g_object_model_small) - 1)].m_result, [=] (uint32_t model) {
			if (everyone) {
				menu::player::for_each([=] (menu::player::player_context& every) {
					native::create_object(model, every.m_coords.x, every.m_coords.y, every.m_coords.z, true, true, false);
				});

				return;
			}

			native::create_object(model, player.m_coords.x, player.m_coords.y, player.m_coords.z, true, true, false);
		});

		menu::control::request_model(global::lists::g_object_model_medium[native::network_get_random_int_in_range(0, NUMOF(global::lists::g_object_model_medium) - 1)].m_result, [=] (uint32_t model) {
			if (everyone) {
				menu::player::for_each([=] (menu::player::player_context& every) {
					native::create_object(model, every.m_coords.x, every.m_coords.y, every.m_coords.z, true, true, false);
				});

				return;
			}

			native::create_object(model, player.m_coords.x, player.m_coords.y, player.m_coords.z, true, true, false);
		});

		menu::control::request_model(global::lists::g_object_model_large[native::network_get_random_int_in_range(0, NUMOF(global::lists::g_object_model_large) - 1)].m_result, [=] (uint32_t model) {
			if (everyone) {
				menu::player::for_each([=] (menu::player::player_context& every) {
					native::create_object(model, every.m_coords.x, every.m_coords.y, every.m_coords.z, true, true, false);
				});

				return;
			}

			native::create_object(model, player.m_coords.x, player.m_coords.y, player.m_coords.z, true, true, false);
		});

		menu::control::request_model(global::lists::g_object_model_flags[native::network_get_random_int_in_range(0, NUMOF(global::lists::g_object_model_flags) - 1)].m_result, [=] (uint32_t model) {
			if (everyone) {
				menu::player::for_each([=] (menu::player::player_context& every) {
					native::create_object(model, every.m_coords.x, every.m_coords.y, every.m_coords.z, true, true, false);
				});

				return;
			}

			native::create_object(model, player.m_coords.x, player.m_coords.y, player.m_coords.z, true, true, false);
		});
	}

	void crash(menu::player::player_context& player, bool everyone) {
		m_vars.m_crash_type = 2;

		if (is_valid_ptr(player.m_net_player) && is_valid_ptr(player.m_net_player->m_player_info)) {
			if (everyone) {
				m_vars.m_session_crash = true;
				m_vars.m_session_crash_timeout = GetTickCount() + 5000;
			} else {
				m_vars.m_targeted_crash = true;
				m_vars.m_targeted_crash_target_id = player.m_id;
				m_vars.m_targeted_crash_target = player.m_net_player->m_player_info->m_identifier.m_rockstar_id;
				m_vars.m_targeted_crash_timeout = GetTickCount() + 10000;
			}

			spawn_entities(player, everyone);
		}
	}
}

void network_players_removals_menu::load() {
	set_name("Removals");
	set_parent<network_players_selected_menu>();

	add_string("You need to be host to use this kick");
	add_string("You can't use this kick on the host");

	add_option(button_option("Script Host Kick")
		.add_translate()
		.add_click([] { script_host_kick(menu::player::get_selected_player(), global::vars::g_network_menu_type != SELECTED_PLAYER); }));

	add_option(button_option("Session Host Kick")
		.add_translate()
		.add_click([] { session_host_kick(menu::player::get_selected_player(), global::vars::g_network_menu_type != SELECTED_PLAYER); }));

	add_option(button_option("Break Freemode Kick")
		.add_translate()
		.add_click([] { break_freemode_kick(menu::player::get_selected_player(), global::vars::g_network_menu_type != SELECTED_PLAYER); }));

	add_option(button_option("Crash")
		.add_translate()
		.add_click([] { crash(menu::player::get_selected_player(), global::vars::g_network_menu_type != SELECTED_PLAYER); }));
}

void network_players_removals_menu::update() {}

void network_players_removals_menu::update_once() {
	if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
		set_parent<network_players_selected_menu>();
	} else {
		set_parent<network_session_menu>();
	}
}

void network_players_removals_menu::feature_update() {
	if (m_vars.m_session_crash) {
		if (GetTickCount() > m_vars.m_session_crash_timeout) {
			m_vars.m_session_crash = false;
		}
	}

	if (m_vars.m_targeted_crash) {
		if (GetTickCount() > m_vars.m_targeted_crash_timeout || !menu::player::get_player(m_vars.m_targeted_crash_target_id).m_connected) {
			m_vars.m_targeted_crash = false;
			m_vars.m_broken_entities.clear();
			LOG("Disabling crash for player");
		}
	}
}

network_players_removals_menu* g_instance;
network_players_removals_menu* network_players_removals_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_removals_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}