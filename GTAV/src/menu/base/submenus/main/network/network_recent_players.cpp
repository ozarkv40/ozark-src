#include "network_recent_players.h"
#include "menu/base/submenu_handler.h"
#include "../network.h"
#include "recent/network_recent_players_selected.h"
#include "recent/network_recent_players_permanent.h"
#include "util/dirs.h"
#include "util/log.h"
#include "menu/base/util/timers.h"
#include "menu/base/util/panels.h"
#include "rage/engine.h"
#include "util/threads.h"
#include "rage/ros.h"
#include "menu/base/util/textures.h"
#include <ctime>
#include <fstream>

using namespace network::recents::vars;

namespace network::recents::vars {
	variables m_vars;

	std::string get_current_time() {
		time_t raw_time;
		time(&raw_time);

		tm time;
		localtime_s(&time, &raw_time);

		char time_string[128];
		strftime(time_string, 128, "%a %d %b %Y %H:%M:%S", &time);
		return std::string(time_string);
	}

	void save(std::string name, std::string ip, uint64_t rockstar_id) {
		nlohmann::json json;
		std::vector<recent_player> players;
		std::vector<recent_player> perm_players;

		try {
			std::ifstream file(util::dirs::get_path(recent_players));
			if (file.good()) {
				json = nlohmann::json::parse(file);
				file.close();
			}

			if (!json["recent"].is_null()) {
				for (nlohmann::json::iterator it = json["recent"].begin(); it != json["recent"].end(); ++it) {
					recent_player o;
					strcpy_s(o.m_name, it.value()["name"].get<std::string>().c_str());
					strcpy_s(o.m_ip, it.value()["ip"].get<std::string>().c_str());
					strcpy_s(o.m_first_encountered, it.value()["first encountered"].get<std::string>().c_str());
					strcpy_s(o.m_last_encountered, it.value()["last encountered"].get<std::string>().c_str());
					o.m_rockstar_id = std::stoull(it.key());
					o.m_internal_encountered = it.value()["internal"].get<int>();

					players.push_back(o);
				}
			}

			if (!json["perm"].is_null()) {
				for (nlohmann::json::iterator it = json["perm"].begin(); it != json["perm"].end(); ++it) {
					recent_player o;
					strcpy_s(o.m_name, it.value()["name"].get<std::string>().c_str());
					strcpy_s(o.m_ip, it.value()["ip"].get<std::string>().c_str());
					strcpy_s(o.m_first_encountered, it.value()["first encountered"].get<std::string>().c_str());
					strcpy_s(o.m_last_encountered, it.value()["last encountered"].get<std::string>().c_str());

					o.m_rockstar_id = std::stoull(it.key());
					o.m_internal_encountered = it.value()["internal"].get<int>();

					perm_players.push_back(o);
				}
			}

			bool exists = false;
			for (recent_player& p : players) {
				if (p.m_rockstar_id == rockstar_id && !strcmp(p.m_name, name.c_str())) {
					exists = true;
					strcpy_s(p.m_last_encountered, get_current_time().c_str());
					strcpy_s(p.m_ip, ip.c_str());
					p.m_internal_encountered = (int)time(0);
					break;
				}
			}

			if (!exists) {
				recent_player new_player;
				strcpy_s(new_player.m_name, name.c_str());
				strcpy_s(new_player.m_ip, ip.c_str());
				strcpy_s(new_player.m_first_encountered, get_current_time().c_str());
				strcpy_s(new_player.m_last_encountered, get_current_time().c_str());
				new_player.m_internal_encountered = (int)time(0);
				new_player.m_rockstar_id = rockstar_id;
				players.push_back(new_player);
			}

			std::sort(begin(players), end(players), [](recent_player& first, recent_player& second) { return first.m_internal_encountered > second.m_internal_encountered; });

			std::ofstream output(util::dirs::get_path(recent_players));
			if (output.good()) {
				nlohmann::json resp;

				for (recent_player& p : perm_players) {
					resp["perm"][std::to_string(p.m_rockstar_id)]["name"] = p.m_name;
					resp["perm"][std::to_string(p.m_rockstar_id)]["ip"] = p.m_ip;
					resp["perm"][std::to_string(p.m_rockstar_id)]["first encountered"] = p.m_first_encountered;
					resp["perm"][std::to_string(p.m_rockstar_id)]["last encountered"] = p.m_last_encountered;
					resp["perm"][std::to_string(p.m_rockstar_id)]["internal"] = p.m_internal_encountered;
				}

				int count = 0;
				for (recent_player& p : players) {
					if (count > 100) break;
					resp["recent"][std::to_string(p.m_rockstar_id)]["name"] = p.m_name;
					resp["recent"][std::to_string(p.m_rockstar_id)]["ip"] = p.m_ip;
					resp["recent"][std::to_string(p.m_rockstar_id)]["first encountered"] = p.m_first_encountered;
					resp["recent"][std::to_string(p.m_rockstar_id)]["last encountered"] = p.m_last_encountered;
					resp["recent"][std::to_string(p.m_rockstar_id)]["internal"] = p.m_internal_encountered;
					count++;
				}

				output << resp.dump(4);
				output.close();
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}

	void load_players() {
		try {
			nlohmann::json json;

			std::ifstream file(util::dirs::get_path(recent_players));
			if (file.good()) {
				json = nlohmann::json::parse(file);
				file.close();
			}

			json = json["recent"];

			m_vars.m_players.clear();
			for (nlohmann::json::iterator it = json.begin(); it != json.end(); ++it) {
				recent_player o;
				strcpy_s(o.m_name, it.value()["name"].get<std::string>().c_str());
				if (strlen(o.m_name) == 0) strcpy_s(o.m_name, "Invalid Name");

				strcpy_s(o.m_ip, it.value()["ip"].get<std::string>().c_str());
				strcpy_s(o.m_first_encountered, it.value()["first encountered"].get<std::string>().c_str());
				strcpy_s(o.m_last_encountered, it.value()["last encountered"].get<std::string>().c_str());

				o.m_internal_encountered = it.value()["internal"].get<int>();
				o.m_rockstar_id = std::stoull(it.key());

				if (m_vars.m_players.size() == 1000) break;
				if (o.m_rockstar_id > 0x1000) m_vars.m_queue.push_back(o.m_rockstar_id);
				m_vars.m_players.push_back({ it.key(), o });
			}

			if (!m_vars.m_players.empty()) {
				uint32_t* rids = new uint32_t[m_vars.m_players.size()];

				for (std::size_t i = 0; i < m_vars.m_players.size(); i++) {
					rids[i] = (uint32_t)m_vars.m_players[i].second.m_rockstar_id;
				}

				uint64_t* info = new uint64_t[2];
				*(uint64_t*)((uint64_t)info) = (uint64_t)m_vars.m_players.size();
				*(uint64_t*)((uint64_t)info + 8) = (uint64_t)rids;

				util::threads::add_job([](void* lp) {
					uint64_t count = *(uint64_t*)((uint64_t)lp);
					uint32_t* ridss = (uint32_t*)*(uint64_t*)((uint64_t)lp + 8);

					rage::ros::send_stat_requests(ridss, (int)count);

					for (uint64_t i = 0; i < count; i++) {
						if (global::vars::g_unloading) return;

						if (menu::submenu::handler::get_current() != network_recent_players_menu::get()) {
							if (std::find_if(begin(m_vars.m_image_queue), end(m_vars.m_image_queue), [=](uint64_t rid) { return (uint32_t)rid == ridss[i]; }) == end(m_vars.m_image_queue)) m_vars.m_image_queue.push_back(ridss[i]);
							return;
						}

						rage::ros::download_player_image(ridss[i]);
					}

					delete[] ridss;
					delete[] lp;
				}, info);
			}

			std::sort(begin(m_vars.m_players), end(m_vars.m_players), [](std::pair<std::string, recent_player>& first, std::pair<std::string, recent_player>& second) { return first.second.m_internal_encountered > second.second.m_internal_encountered; });
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}
}

void network_recent_players_menu::load() {
	set_name("Recent Players");
	set_parent<network_menu>();

	add_option(submenu_option("Permanent")
		.add_translate().add_hotkey()
		.add_submenu<network_recent_players_permanent_menu>()
		.add_hover([](submenu_option*) { menu::panels::toggle_panel_render("PANEL_RECENT_PLAYER", false); }));

	add_option(break_option("Players")
		.add_translate());

	add_string("~m~None");

	network_recent_players_selected_menu::get();
}

void network_recent_players_menu::update() {
	static int timers[2] = { 0, 0 };

	menu::timers::run_timed(&timers[1], 4000, [] { m_vars.m_update_online = true;  m_vars.m_update_players = true; });

	if (m_vars.m_update_players) {
		m_vars.m_update_players = false;

		clear_options(2);

		if (m_vars.m_players.size()) {
			for (std::size_t i = 0; i < m_vars.m_players.size(); i++) {
				std::pair<std::string, recent_player>& player = m_vars.m_players[i];

				bool in_session = false;
				menu::player::for_each([&](menu::player::player_context& pl) {
					if (pl.m_net_player) {
						if (pl.m_net_player->m_player_info) {
							if (pl.m_net_player->m_player_info->m_identifier.m_rockstar_id == player.second.m_rockstar_id) {
								in_session = true;
							}
						}
					}
				}, true);

				add_option(submenu_option(util::va::va("%s%s", (global::vars::g_online_rockstar_ids[player.second.m_rockstar_id].first || in_session) ? "" : "~m~", player.second.m_name))
					.add_click([=] {
						network::recents::selected::vars::m_vars.m_type = 1;
						network::recents::selected::vars::m_vars.m_selected_player = i;
						m_vars.m_selected_list = &m_vars.m_players;
					})
					.add_submenu<network_recent_players_selected_menu>()
					.add_hover([=](submenu_option*) {
						menu::panels::panel_parent* parent = menu::panels::get_parent("PANEL_RECENT_PLAYER");
						if (parent) {
							menu::panels::panel_custom_recent_player str;
							str.m_in_session = in_session;
							str.m_online = global::vars::g_online_rockstar_ids[player.second.m_rockstar_id].first || in_session;
							str.m_rockstar_id = player.second.m_rockstar_id;
							str.m_session_type = str.m_online ? global::vars::g_online_rockstar_ids[player.second.m_rockstar_id].second : -1;
							strcpy(str.m_first_encountered, player.second.m_first_encountered);
							strcpy(str.m_last_encountered, player.second.m_last_encountered);
							strcpy(str.m_name, player.second.m_name);
							strcpy(str.m_ip, player.second.m_ip);

							if (global::vars::g_read_stats_by_gamer_results.contains(player.second.m_rockstar_id)) {
								str.m_has_stats = true;
								memcpy(&str.m_stats, &global::vars::g_read_stats_by_gamer_results[player.second.m_rockstar_id], sizeof(str.m_stats));
							} else {
								str.m_has_stats = false;
							}

							menu::panels::set_structure(menu::panels::get_child(parent, "PANEL_RECENT_PLAYER_INFO"), (void*)&str, sizeof(str));
							parent->m_render = true;
						}
					})
					.add_update([=](submenu_option* option, int pos) {
						menu::textures::texture_context context;
						if (menu::textures::get_texture(std::string("playerimg_" + std::to_string(player.second.m_rockstar_id)), &context)) {
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
			auto vit = std::find_if(begin(global::vars::g_online_rockstar_ids_queue), end(global::vars::g_online_rockstar_ids_queue), [=](uint64_t value) {
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
				m_vars.m_queue.push_back(m_vars.m_players[i].second.m_rockstar_id);
			}
		}
	}
}

void network_recent_players_menu::update_once() {
	load_players();
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

		util::threads::add_job([](void* lp) {
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

void network_recent_players_menu::feature_update() {}

network_recent_players_menu* g_instance;
network_recent_players_menu* network_recent_players_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_recent_players_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}