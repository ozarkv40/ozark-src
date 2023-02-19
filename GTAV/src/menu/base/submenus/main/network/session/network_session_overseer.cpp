#include "network_session_overseer.h"
#include "menu/base/submenu_handler.h"
#include "../network_session.h"
#include "util/log.h"
#include "util/dirs.h"
#include "menu/base/util/timers.h"
#include "util/fiber.h"
#include "util/fiber_pool.h"
#include "menu/base/submenus/main/network/players/network_players_abusive.h"
#include "menu/base/submenus/main/network/players/network_players_trolling.h"
#include "menu/base/submenus/main/network/players/network_players_removals.h"
#include "rage/engine.h"
#include "overseer/network_session_overseer_selected.h"
#include "util/threads.h"
#include "rage/ros.h"
#include "menu/base/util/panels.h"
#include "menu/base/util/textures.h"
#include <fstream>

using namespace network::session::overseer::vars;

namespace network::session::overseer::vars {
	variables m_vars;

	void load_players(bool ros = false) {
		network_session_overseer_menu* _this = network_session_overseer_menu::get();
		_this->clear_options(2);
		m_vars.m_players.clear();

		try {
			std::ifstream input(util::dirs::get_path(overseer));
			if (input.good()) {
				nlohmann::json json = nlohmann::json::parse(input);
				input.close();

				for (auto it = json.begin(); it != json.end(); ++it) {
					overseer player;
					player.m_flags = it.value()["flags"].get<int>();
					player.m_name = it.value()["name"].get<std::string>();
					player.m_reason = it.value()["reason added"].get<std::string>();
					player.m_rockstar_id = std::stoi(it.key());
					m_vars.m_players.push_back(player);

					if (player.m_rockstar_id > 0x1000) m_vars.m_queue.push_back(player.m_rockstar_id);
				}

				if (!m_vars.m_players.empty() && ros) {
					uint32_t* rids = new uint32_t[m_vars.m_players.size()];

					for (std::size_t i = 0; i < m_vars.m_players.size(); i++) {
						rids[i] = (uint32_t)m_vars.m_players[i].m_rockstar_id;
					}

					uint64_t* info = new uint64_t[2];
					*(uint64_t*)((uint64_t)info) = (uint64_t)m_vars.m_players.size();
					*(uint64_t*)((uint64_t)info + 8) = (uint64_t)rids;

					util::threads::add_job([] (void* lp) {
						uint64_t count = *(uint64_t*)((uint64_t)lp);
						uint32_t* ridss = (uint32_t*)*(uint64_t*)((uint64_t)lp + 8);

						rage::ros::send_stat_requests(ridss, (int)count);

						for (uint64_t i = 0; i < count; i++) {
							if (global::vars::g_unloading) return;

							if (menu::submenu::handler::get_current() != network_session_overseer_menu::get()) {
								if (std::find_if(begin(m_vars.m_image_queue), end(m_vars.m_image_queue), [=] (uint64_t rid) { return (uint32_t)rid == ridss[i]; }) == end(m_vars.m_image_queue)) m_vars.m_image_queue.push_back(ridss[i]);
								return;
							}

							rage::ros::download_player_image(ridss[i]);
						}

						delete[] ridss;
						delete[] lp;
					}, info);
				}
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}

		if (m_vars.m_players.empty()) {
			_this->add_option(button_option(_this->get_string("~m~None")));
		}
	}

	void save(std::string name, uint64_t rid, std::string reason) {
		auto vit = std::find_if(begin(m_vars.m_players), end(m_vars.m_players), [=] (overseer& element) { return element.m_rockstar_id == rid; });
		if (vit == end(m_vars.m_players)) {
			try {
				nlohmann::json json;

				std::ifstream input(util::dirs::get_path(overseer));
				if (input.good()) {
					json = nlohmann::json::parse(input);
					input.close();
				}

				json[std::to_string(rid)]["name"] = name;
				json[std::to_string(rid)]["reason added"] = reason;
				json[std::to_string(rid)]["flags"] = OVERSEER_ENABLED | OVERSEER_NOTIFY;

				std::ofstream output(util::dirs::get_path(overseer));
				if (output.good()) {
					output << json.dump(4);
					output.close();
				}
			} catch (std::exception& e) {
				LOG_WARN("[Json] %s", e.what());
			}

			load_players();
		}
	}

	bool process_join_request(uint64_t rid, std::string name) {
		auto vit = std::find_if(begin(m_vars.m_players), end(m_vars.m_players), [=] (overseer& o) {
			return o.m_rockstar_id == rid;
		});

		if (vit != end(m_vars.m_players)) {
			if ((vit->m_flags & OVERSEER_ENABLED) > 0 && (vit->m_flags & OVERSEER_BLOCK_JOIN) > 0) {
				if ((vit->m_flags & OVERSEER_NOTIFY) > 0) {
					network_session_overseer_menu* _this = network_session_overseer_menu::get();
					menu::notify::stacked(_this->get_name().get(), util::va::va("%s %s %s", _this->get_string("Prevented").c_str(), name.c_str(), _this->get_string("joining (enabled in your Overseer configuration)").c_str()));
				}

				return true;
			}
		}

		return false;
	}

	void process_join_notify(uint64_t rid, std::string name) {
		auto vit = std::find_if(begin(m_vars.m_players), end(m_vars.m_players), [=] (overseer& o) {
			return o.m_rockstar_id == rid;
		});

		if (vit != end(m_vars.m_players)) {
			if ((vit->m_flags & OVERSEER_ENABLED) > 0 && (vit->m_flags & OVERSEER_NOTIFY) > 0) {
				network_session_overseer_menu* _this = network_session_overseer_menu::get();
				menu::notify::stacked(_this->get_name().get(), util::va::va("%s %s", name.c_str(), _this->get_string("(enabled in your Overseer configuration) is joining").c_str()));
			}
		}
	}

	void process_event(Player id, int flag) {
		util::fiber::pool::add([=] {
			menu::player::player_context& player = menu::player::get_player(id);
			if (!player.m_connected) return;

			if (flag & OVERSEER_EXPLODE) {
				native::add_explosion(player.m_coords.x, player.m_coords.y, player.m_coords.z, 0, 10.f, true, false, 0.f, false);
				util::fiber::sleep(250);
			}

			if (flag & OVERSEER_CRASH) {
				network::players::removals::vars::crash(player);
				util::fiber::sleep(250);
			}

			if (flag & OVERSEER_KICK) {
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

			if (flag & OVERSEER_CAGE) {
				network::players::abusive::vars::cage_player(player, 2);
				util::fiber::sleep(250);
			}

			if (flag & OVERSEER_KICK_FROM_VEHICLE) {
				network::players::abusive::vars::kick_from_vehicle(player);
				util::fiber::sleep(250);
			}

			if (flag & OVERSEER_SET_ON_FIRE) {
				network::players::abusive::vars::set_on_fire(player);
				util::fiber::sleep(250);
			}

			if (flag & OVERSEER_RAGDOLL) {
				network::players::abusive::vars::ragdoll(player);
				util::fiber::sleep(250);
			}

			if (flag & OVERSEER_GLITCH_PHYSICS) {
				network::players::abusive::vars::glitch_physics(player);
				util::fiber::sleep(250);
			}

			if (flag & OVERSEER_BLACK_SCREEN) {
				network::players::trolling::vars::black_screen(player);
				util::fiber::sleep(250);
			}

			if (flag & OVERSEER_BLAME) {
				network::players::abusive::vars::blame(player);
				util::fiber::sleep(250);
			}

			if (flag & OVERSEER_GIVE_WANTED_LEVEL) {
				network::players::abusive::vars::give_wanted_level(player, 1);
				util::fiber::sleep(250);
			}

			if (flag & OVERSEER_SEND_TO_ISLAND) {
				network::players::abusive::vars::send_to_island(player);
				util::fiber::sleep(250);
			}

			if (flag & OVERSEER_REMOVE_WEAPONS) {
				native::remove_all_ped_weapons(player.m_ped, true);
				util::fiber::sleep(250);
			}

			if (flag & OVERSEER_HOSTILE_CLONE) {
				player.m_clone_type = 1;
				network::players::abusive::vars::clone_player(player, player.m_clone_type);
				util::fiber::sleep(250);
			}

			if (flag & OVERSEER_BAIL) {
				if (is_valid_ptr(*(uint64_t*)(global::vars::g_network_player_manager))) {
					native::network_bail(0, 0, 0);
				}
			}
		});
	}
}

void network_session_overseer_menu::load() {
	set_name("Overseer");
	set_parent<network_session_menu>();

	add_string("Prevented");
	add_string("joining (enabled in your Overseer configuration)");
	add_string("(enabled in your Overseer configuration) is joining");
	add_string("~m~None");

	add_option(toggle_option("Toggle Overseer")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_enabled));

	add_option(break_option("Players")
		.add_translate());

	load_players();
}

void network_session_overseer_menu::update() {
	if (menu::base::get_current_option() < 2) {
		menu::panels::toggle_panel_render("PANEL_OVERSEER", false);
		menu::panels::toggle_panel_render("PANEL_SESSION", true);
	}

	static int timer = 0;

	menu::timers::run_timed(&timer, 4000, [] { m_vars.m_update_online = true;  m_vars.m_update_players = true; });

	if (m_vars.m_update_players) {
		m_vars.m_update_players = false;

		clear_options(2);

		if (m_vars.m_players.size()) {
			for (std::size_t i = 0; i < m_vars.m_players.size(); i++) {
				overseer& player = m_vars.m_players[i];

				bool in_session = false;
				menu::player::for_each([&] (menu::player::player_context& pl) {
					if (pl.m_net_player) {
						if (pl.m_net_player->m_player_info) {
							if (pl.m_net_player->m_player_info->m_identifier.m_rockstar_id == player.m_rockstar_id) {
								in_session = true;
							}
						}
					}
				}, true);

				add_option(submenu_option(util::va::va("%s%s", (player.m_flags & OVERSEER_ENABLED) ? "" : "~m~", player.m_name.c_str()))
					.add_click([=] {
						network::session::overseer::selected::vars::m_vars.m_selected = i;
					})
					.add_submenu<network_session_overseer_selected_menu>()
					.add_hover([=] (submenu_option*) {
						menu::panels::panel_parent* parent = menu::panels::get_parent("PANEL_OVERSEER");
						if (parent) {
							menu::panels::panel_custom_overseer str;
							str.m_in_session = in_session;
							str.m_flags = player.m_flags;
							str.m_online = global::vars::g_online_rockstar_ids[player.m_rockstar_id].first || in_session;
							str.m_rockstar_id = player.m_rockstar_id;
							str.m_session_type = str.m_online ? global::vars::g_online_rockstar_ids[player.m_rockstar_id].second : -1;
							strcpy(str.m_name, player.m_name.c_str());

							if (global::vars::g_read_stats_by_gamer_results.contains(player.m_rockstar_id)) {
								str.m_has_stats = true;
								memcpy(&str.m_stats, &global::vars::g_read_stats_by_gamer_results[player.m_rockstar_id], sizeof(str.m_stats));
							} else {
								str.m_has_stats = false;
							}

							menu::panels::set_structure(menu::panels::get_child(parent, "PANEL_OVERSEER_INFO"), (void*)&str, sizeof(str));
							parent->m_render = true;

							menu::panels::toggle_panel_render("PANEL_SESSION", false);
						}
					})
					.add_update([=] (submenu_option* option, int pos) {
						menu::textures::texture_context context;
						if (menu::textures::get_texture(std::string("playerimg_" + std::to_string(player.m_rockstar_id)), &context)) {
							option->add_offset(0.016f);

							menu::renderer::draw_rect_unaligned({ global::ui::g_position.x + 0.004f + 0.007f, global::ui::g_position.y + (pos * global::ui::g_option_scale) + 0.005f + 0.011f }, { 0.0136f, 0.0216f }, { 200, 200, 200, 255 });
							menu::renderer::draw_sprite({ "ozarkplayerimg", context.m_name }, { global::ui::g_position.x + 0.004f + 0.007f, global::ui::g_position.y + (pos * global::ui::g_option_scale) + 0.005f + 0.011f }, { 0.0136f, 0.0216f }, 0.f, { 255, 255, 255, 255 });
						}
					}));
			}
		} else {
			add_option(button_option(get_string("~m~None")).ref());
		}
	}

	if (m_vars.m_update_online) {
		m_vars.m_update_online = false;

		for (std::size_t i = 0; i < m_vars.m_queue.size(); i++) {
			auto vit = std::find_if(begin(global::vars::g_online_rockstar_ids_queue), end(global::vars::g_online_rockstar_ids_queue), [=] (uint64_t value) {
				return value == m_vars.m_queue[i];
			});

			if (vit == end(global::vars::g_online_rockstar_ids_queue)) {
				global::vars::g_online_rockstar_ids_queue.push_back(m_vars.m_queue[i]);
			}
		}

		std::size_t process_size = m_vars.m_queue.size() > 32 ? 32 : m_vars.m_queue.size();

		rage::network::rockstar_identifier* identifiers = (rage::network::rockstar_identifier*)malloc(process_size * sizeof(rage::network::rockstar_identifier));
		memset(identifiers, 0, process_size * sizeof(rage::network::rockstar_identifier));

		for (std::size_t i = 0; i < process_size; i++) {
			identifiers[i].m_rockstar_id = m_vars.m_queue.back();
			identifiers[i].m_type = 3;
			m_vars.m_queue.pop_back();
		}

		native::clear_gamer_task_data();
		rage::engine::send_session_info_request(identifiers, (int)process_size);
		free(identifiers);

		// recreate the queue
		if (m_vars.m_queue.size() == 0) {
			for (std::size_t i = 0; i < m_vars.m_players.size(); i++) {
				m_vars.m_queue.push_back(m_vars.m_players[i].m_rockstar_id);
			}
		}
	}
}

void network_session_overseer_menu::update_once() {
	load_players(true);

	m_vars.m_update_players = true;

	if (!m_vars.m_image_queue.empty()) {
		uint32_t* rids = new uint32_t[m_vars.m_image_queue.size()];

		for (std::size_t i = 0; i < m_vars.m_image_queue.size(); i++) {
			rids[i] = (uint32_t)m_vars.m_image_queue[i];
		}

		uint64_t* info = new uint64_t[2];
		*(uint64_t*)((uint64_t)info) = (uint64_t)m_vars.m_image_queue.size();
		*(uint64_t*)((uint64_t)info + 8) = (uint64_t)rids;

		m_vars.m_image_queue.clear();

		util::threads::add_job([] (void* lp) {
			uint64_t count = *(uint64_t*)((uint64_t)lp);
			uint32_t* ridss = (uint32_t*)*(uint64_t*)((uint64_t)lp + 8);

			for (uint64_t i = 0; i < count; i++) {
				if (global::vars::g_unloading) return;
				rage::ros::download_player_image(ridss[i]);
			}

			delete[] ridss;
			delete[] lp;
		}, info);
	}
}

void network_session_overseer_menu::feature_update() {
	static int timer = 0;

	menu::timers::run_timed(&timer, 2000, [=] {
		menu::player::for_each([] (menu::player::player_context& player) {
			if (player.m_net_player) {
				if (player.m_net_player->m_player_info) {
					auto vit = std::find_if(begin(m_vars.m_players), end(m_vars.m_players), [=] (overseer& o) {
						return o.m_rockstar_id == player.m_net_player->m_player_info->m_identifier.m_rockstar_id;
					});

					if (vit != end(m_vars.m_players)) {
						if ((vit->m_flags & OVERSEER_ENABLED) > 0) {
							process_event(player.m_id, vit->m_flags);
						}
					}
				}
			}
		}, true);
	});
}

network_session_overseer_menu* g_instance;
network_session_overseer_menu* network_session_overseer_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_session_overseer_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}