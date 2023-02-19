#include "network_players_commands.h"
#include "menu/base/submenu_handler.h"
#include "network_players_selected.h"
#include "util/fiber_pool.h"
#include "network_players_text.h"
#include "network_players_friendly.h"
#include "menu/base/util/control.h"
#include "menu/base/submenus/main/vehicle.h"
#include "menu/base/submenus/main/network/network_session.h"
#include "menu/base/submenus/main/network/players/network_players_abusive.h"
#include "menu/base/submenus/main/network/players/network_players_trolling.h"
#include "menu/base/submenus/main/network/players/network_players_vehicle.h"
#include "menu/base/submenus/main/network/players/network_players_removals.h"
#include "rage/engine.h"
#include "global/lists.h"

using namespace network::players::commands::vars;

static localization t_processed_command("Processed command", true, true);
static localization t_from("from", true, true);

namespace network::players::commands::vars {
	variables m_vars;

	struct command_context {
		const char* m_command;
		const char* m_tooltip;
		std::function<void(menu::player::player_context&, std::vector<std::string>)> m_callback;
	};

	auto default_callback = [] (menu::player::player_context&, std::vector<std::string>) {};

	scroll_struct<command_context> commands[] = {
		{ localization("Give Weapons", true), { "weapons", "Gives them all weapons", default_callback } },
		{ localization("Vehicle Kick", true), { "vkick", "Kicks a player from their vehicle", default_callback } },
		{ localization("Fix Vehicle", true), { "vfix", "Fixes their vehicle", default_callback } },
		{ localization("Upgrade Vehicle", true), { "vupgrade", "Upgrades their vehicle", default_callback } },
		{ localization("Clone Vehicle", true), { "vclone", "Clones their vehicle", default_callback } },
		{ localization("Boost Vehicle", true), { "vboost", "Boosts their vehicle", default_callback } },
		{ localization("Spawn Entity", true), { "spawn", "Spawns an entity (check the sites list)", default_callback } },
		{ localization("Spawn Bodyguard", true), { "guard", "Spawns a bodyguard", default_callback } },
		{ localization("Off the Radar", true), { "otr", "Gives them off the radar", default_callback } },
		{ localization("Remove Wanted Level", true), { "nocops", "Removes their wanted level", default_callback } },
		{ localization("Kick Player", true), { "kick", "Kicks a player", default_callback } },
		{ localization("Explode Player", true), { "explode", "Explodes a player", default_callback } },
		{ localization("Ban Player from CEO", true), { "ceoban", "Bans a player from their CEO", default_callback } },
		{ localization("Kick Player from CEO", true), { "ceokick", "Kicks a player from their CEO", default_callback } },
		{ localization("Cage Player", true), { "cage", "Cages a player", default_callback } },
		{ localization("Taze Player", true), { "taze", "Tazes a player", default_callback } },
		{ localization("Ragdoll Player", true), { "ragdoll", "Ragdolls a player", default_callback } },
		{ localization("Glitch Player Physics", true), { "glitch", "Glitches a players physics", default_callback } },
		{ localization("Clone Player", true), { "clone", "Clones a player", default_callback } },
		{ localization("Blackscreen Player", true), { "blackscreen", "Blackscreens a player", default_callback } },
		{ localization("Crash Player", true), { "crash", "Crashes a player", default_callback } },
		{ localization("Teleport Vehicle", true), { "tp", "Teleports their vehicle somewhere", default_callback } },
		{ localization("Give Weapon Attachments", true), { "attachments", "Gives them all weapon attachments", default_callback } }
	};

	Player get_player(std::string name) {
		Player id = -1;

		if (!menu::player::get_local_player().m_name.compare(name)) {
			return id;
		}

		menu::player::for_each([&] (menu::player::player_context& player) {
			if (!player.m_name.compare(name)) {
				id = player.m_id;
			}
		}, true, true);

		return id;
	}

	void call_command(const char* command_name, rage::network::net_game_player* player, std::vector<std::string> tokens) {
		menu::player::player_context& player_var = menu::player::get_player(player->m_id);

		if (player_var.m_chat_commands || m_vars.m_chat_commands) {
			for (int i = 0; i < NUMOF(commands); i++) {
				scroll_struct<command_context> command = commands[i];

				if (!strcmp(command.m_result.m_command, command_name)) {
					if (player_var.m_chat_command[i] || (m_vars.m_chat_commands && m_vars.m_chat_command[i])) {
						util::fiber::pool::add([=] {
							command.m_result.m_callback(menu::player::get_player(player->m_id), tokens);
						});

						menu::notify::stacked(network_players_commands_menu::get()->get_name().get(), util::va::va("%s \"%s\" %s %s", TRANSLATE(t_processed_command), command_name, TRANSLATE(t_from), player_var.m_name.c_str()));
					}

					break;
				}
			}
		}
	}
}

void network_players_commands_menu::load() {
	set_name("Chat commands");
	set_parent<network_players_selected_menu>();

	for (scroll_struct<command_context>& command : commands) {
		add_string(command.m_result.m_tooltip);
	}

	// Give Weapons
	commands[0].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		network::players::friendly::vars::give_all_weapons(player);
	};

	// Vehicle Kick
	commands[1].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		if (tokens.size() == 2) {
			Player target = get_player(tokens[1]);
			if (target != -1) {
				menu::player::player_context& p = menu::player::get_player(target);
				if (p.m_in_vehicle) {
					network::players::abusive::vars::kick_from_vehicle(p);
				}
			}
		}
	};

	// Fix Vehicle
	commands[2].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		if (player.m_in_vehicle) {
			menu::control::request_control(player.m_vehicle, [] (Entity vehicle) {
				native::set_vehicle_fixed(vehicle);
			});
		}
	};

	// Upgrade Vehicle
	commands[3].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		if (player.m_in_vehicle) {
			menu::control::request_control(player.m_vehicle, [] (Entity vehicle) {
				vehicle::vars::max_upgrades(vehicle);
			});
		}
	};

	// Vehicle Clone
	commands[4].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		if (tokens.size() == 2) {
			Player target = get_player(tokens[1]);
			if (target != -1) {
				menu::player::player_context& p = menu::player::get_player(target);
				if (p.m_in_vehicle) {
					vehicle::vars::run_task(p.m_vehicle, [] (Vehicle veh) {
						vehicle::vars::clone_vehicle(veh);
					});
				}
			}
		}
	};

	// Vehicle Boost
	commands[5].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		if (tokens.size() == 2) {
			if (player.m_in_vehicle) {
				vehicle::vars::run_task(player.m_vehicle, [=] (Vehicle veh) {
					int speed = std::atoi(tokens[1].c_str());
					native::set_vehicle_forward_speed(veh, speed > 0 ? speed + native::get_entity_speed(veh) : speed);
				});
			}
		}
	};

	 // Spawn Entity
	commands[6].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		if (tokens.size() == 3) {
			auto spawn_vehicle = [=] (uint32_t hash) {
				menu::control::request_model(hash, [=] (uint32_t model) {
					Vehicle veh = native::create_vehicle(model, player.m_coords.x, player.m_coords.y, player.m_coords.z, player.m_heading, true, true, 0);
					if (native::does_entity_exist(veh)) {
						native::decor_set_int(veh, "MPBitset", (1 << 10));
						native::set_vehicle_is_stolen(veh, false);
					}
				});
			};

			auto spawn_object = [=] (uint32_t hash) {
				menu::control::request_model(hash, [=] (uint32_t model) {
					native::create_object(model, player.m_coords.x, player.m_coords.y, player.m_coords.z, true, true, false);
				});
			};

			auto spawn_ped = [=] (uint32_t hash) {
				switch (hash) {
					case 0x3F039CBA:
					case 0x856CFB02:
					case 0x2D7030F3:
					case 0x0703F106:
					case 0x431d501c:
					case 0x1CFC0E72:
					case 0x1E15B3EC:
					case 0x1CB5C0C3:
					return;
				}

				menu::control::request_model(hash, [=] (uint32_t model) {
					native::create_ped(13, model, player.m_coords.x, player.m_coords.y, player.m_coords.z, player.m_heading, true, false);
				});
			};

			std::string string_name = tokens.at(2);
			switch (native::get_hash_key(tokens.at(1).c_str())) {
				case 0xdd245b9c: // vehicle
					if (string_name[0] == '0' && (string_name[1] == 'x' || string_name[1] == 'X')) {
						// hash
						spawn_vehicle((uint32_t)_strtoui64(string_name.c_str(), 0, 0));
					} else {
						if (std::find_if(string_name.begin(), string_name.end(), [] (unsigned char c) { return !std::isdigit(c); }) == string_name.end()) {
							// numeric
							spawn_vehicle((uint32_t)atoi(string_name.c_str()));
						} else {
							// name
							spawn_vehicle(native::get_hash_key(string_name.c_str()));
						}
					}

				break;

				case 0x34d90761: // ped
					if (string_name[0] == '0' && (string_name[1] == 'x' || string_name[1] == 'X')) {
						// hash
						spawn_ped((uint32_t)_strtoui64(string_name.c_str(), 0, 0));
					} else {
						if (std::find_if(string_name.begin(), string_name.end(), [] (unsigned char c) { return !std::isdigit(c); }) == string_name.end()) {
							// numeric
							spawn_ped((uint32_t)atoi(string_name.c_str()));
						} else {
							// name
							spawn_ped(native::get_hash_key(string_name.c_str()));
						}
					}

				break;

				case 0x39958261: // object
					if (string_name[0] == '0' && (string_name[1] == 'x' || string_name[1] == 'X')) {
						// hash
						spawn_object((uint32_t)_strtoui64(string_name.c_str(), 0, 0));
					} else {
						if (std::find_if(string_name.begin(), string_name.end(), [] (unsigned char c) { return !std::isdigit(c); }) == string_name.end()) {
							// numeric
							spawn_object((uint32_t)atoi(string_name.c_str()));
						} else {
							// name
							spawn_object(native::get_hash_key(string_name.c_str()));
						}
					}

				break;
			}
		}
	};

	// Spawn Bodyguard
	commands[7].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		network::players::friendly::vars::spawn_bodyguards(player, 1);
	};

	// Off the Radar
	commands[8].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		network::players::friendly::vars::off_the_radar(player);
	};

	// Remove Wanted Level
	commands[9].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		network::players::friendly::vars::disable_police(player);
	};

	// Kick Player
	commands[10].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		if (tokens.size() == 2) {
			Player target = get_player(tokens[1]);
			if (target != -1) {
				menu::player::player_context& p = menu::player::get_player(target);
				if (p.m_in_vehicle) {
					if (menu::player::get_local_player().m_is_script_host) {
						network::players::removals::vars::script_host_kick(p);
					}

					if (rage::engine::get_host_net_game_player() == menu::player::get_local_player().m_net_player) {
						network::players::removals::vars::session_host_kick(p);
					} else {
						if (rage::engine::get_host_net_game_player() != p.m_net_player) {
							network::players::removals::vars::break_freemode_kick(p);
						}
					}
				}
			}
		}
	};

	// Explode Player
	commands[11].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		if (tokens.size() == 2) {
			Player target = get_player(tokens[1]);
			if (target != -1) {
				menu::player::player_context& p = menu::player::get_player(target);
				native::add_explosion(p.m_coords.x, p.m_coords.y, p.m_coords.z, 0, 100.f, false, true, 0.f, false);
			}
		}
	};
	
	// Ban Player from CEO
	commands[12].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		if (tokens.size() == 2) {
			Player target = get_player(tokens[1]);
			if (target != -1) {
				menu::player::player_context& p = menu::player::get_player(target);
				network::players::abusive::vars::ceo_ban(p);
			}
		}
	};

	// Kick Player from CEO
	commands[13].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		if (tokens.size() == 2) {
			Player target = get_player(tokens[1]);
			if (target != -1) {
				menu::player::player_context& p = menu::player::get_player(target);
				network::players::abusive::vars::ceo_kick(p);
			}
		}
	};

	// Cage Player
	commands[14].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		if (tokens.size() == 2) {
			Player target = get_player(tokens[1]);
			if (target != -1) {
				menu::player::player_context& p = menu::player::get_player(target);
				network::players::abusive::vars::cage_player(p, 0);
			}
		}
	};

	// Taze Player
	commands[15].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		if (tokens.size() == 2) {
			Player target = get_player(tokens[1]);
			if (target != -1) {
				menu::player::player_context& p = menu::player::get_player(target);
				network::players::abusive::vars::taze(p);
			}
		}
	};

	// Ragdoll Player
	commands[16].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		if (tokens.size() == 2) {
			Player target = get_player(tokens[1]);
			if (target != -1) {
				menu::player::player_context& p = menu::player::get_player(target);
				network::players::abusive::vars::ragdoll(p);
			}
		}
	};

	// Glitch Player Physics
	commands[17].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		if (tokens.size() == 2) {
			Player target = get_player(tokens[1]);
			if (target != -1) {
				menu::player::player_context& p = menu::player::get_player(target);
				network::players::abusive::vars::glitch_physics(p);
			}
		}
	};

	// Clone Player
	commands[18].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		if (tokens.size() == 2) {
			Player target = get_player(tokens[1]);
			if (target != -1) {
				menu::player::player_context& p = menu::player::get_player(target);
				network::players::abusive::vars::clone_player(p, 1);
			}
		}
	};

	// Blackscreen Player
	commands[19].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		if (tokens.size() == 2) {
			Player target = get_player(tokens[1]);
			if (target != -1) {
				menu::player::player_context& p = menu::player::get_player(target);
				network::players::trolling::vars::black_screen(p);
			}
		}
	};

	// Crash Player
	commands[20].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		if (tokens.size() == 2) {
			Player target = get_player(tokens[1]);
			if (target != -1) {
				menu::player::player_context& p = menu::player::get_player(target);
				network::players::removals::vars::crash(p);
			}
		}
	};

	// Teleport Vehicle
	commands[21].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		if (tokens.size() == 2) {
			int id = std::atoi(tokens[1].c_str());
			if (id < 0 || id >= NUMOF(global::lists::g_popular_locations)) return;

			if (player.m_in_vehicle) {
				math::vector3<float> coords = global::lists::g_popular_locations[id].m_result;
				vehicle::vars::run_task(player.m_vehicle, [=] (Vehicle veh) {
					native::set_entity_coords(veh, coords.x, coords.y, coords.z, false, false, false, false);
				});
			}
		}
	};

	// Give Weapon Attachments
	commands[22].m_result.m_callback = [] (menu::player::player_context& player, std::vector<std::string> tokens) {
		network::players::friendly::vars::give_all_attachments(player);
	};

	add_option(toggle_option("Toggle Chat Commands")
		.add_translate()
		.add_toggle(menu::player::get_selected_player().m_chat_commands)
		.add_update([] (toggle_option* option, int pos) {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				option->add_toggle(menu::player::get_selected_player().m_chat_commands);
			} else {
				option->add_toggle(m_vars.m_chat_commands);
			}
		}));

	add_option(button_option("Send Command List")
		.add_translate()
		.add_click([] {
			if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
				network::players::text::vars::send_text_message(menu::player::get_selected_player(), menu::player::random(menu::player::get_selected_player().m_id), "Go to ozark.gg/chat to view the commands given to you!");
			} else {
				menu::player::for_each([] (menu::player::player_context& player) {
					network::players::text::vars::send_text_message(player, menu::player::random(player.m_id), "Go to ozark.gg/chat to view the commands given to you!");
				});
			}
		}));

	add_option(break_option("Commands")
		.add_translate());
}

void network_players_commands_menu::update() {}

void network_players_commands_menu::update_once() {
	if (global::vars::g_network_menu_type == SELECTED_PLAYER) {
		set_parent<network_players_selected_menu>();
	} else {
		set_parent<network_session_menu>();
	}

	clear_options(3);

	for (int i = 0; i < NUMOF(commands); i++) {
		scroll_struct<command_context> command = commands[i];

		add_option(toggle_option(command.m_name.get())
			.add_toggle(global::vars::g_network_menu_type == SELECTED_PLAYER ? menu::player::get_selected_player().m_chat_command[i] : m_vars.m_chat_command[i])
			.add_tooltip(std::string("?") + command.m_result.m_command + std::string(" - ") + get_string(command.m_result.m_tooltip)));
	}
}

void network_players_commands_menu::feature_update() {}

network_players_commands_menu* g_instance;
network_players_commands_menu* network_players_commands_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_players_commands_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}