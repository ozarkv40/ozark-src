#include "network_recent_players_permanent.h"
#include "menu/base/submenu_handler.h"
#include "../network_recent_players.h"
#include "network_recent_players_selected.h"
#include "rage/engine.h"
#include "menu/base/util/timers.h"
#include "menu/base/util/panels.h"
#include "util/dirs.h"
#include "util/log.h"
#include "util/threads.h"
#include "rage/ros.h"
#include "menu/base/util/textures.h"
#include <fstream>

using namespace network::recents::permanent::vars;

namespace network::recents::permanent::vars {
	variables m_vars;

	void load_players() {
		try {
			nlohmann::json json;

			std::ifstream file(util::dirs::get_path(recent_players));
			if (file.good()) {
				json = nlohmann::json::parse(file);
				file.close();
			}

			json = json["perm"];

			network::recents::vars::m_vars.m_permanent_players.clear();
			for (nlohmann::json::iterator it = json.begin(); it != json.end(); ++it) {
				network::recents::vars::recent_player o;
				strcpy_s(o.m_name, it.value()["name"].get<std::string>().c_str());
				if (strlen(o.m_name) == 0) strcpy_s(o.m_name, "Invalid Name");

				strcpy_s(o.m_ip, it.value()["ip"].get<std::string>().c_str());
				strcpy_s(o.m_first_encountered, it.value()["first encountered"].get<std::string>().c_str());
				strcpy_s(o.m_last_encountered, it.value()["last encountered"].get<std::string>().c_str());

				o.m_internal_encountered = it.value()["internal"].get<int>();
				o.m_rockstar_id = std::stoull(it.key());

				if (network::recents::vars::m_vars.m_permanent_players.size() == 100) break;
				if (o.m_rockstar_id > 0x1000) m_vars.m_queue.push_back(o.m_rockstar_id);
				network::recents::vars::m_vars.m_permanent_players.push_back({ it.key(), o });
			}

			if (!network::recents::vars::m_vars.m_permanent_players.empty()) {
				uint32_t* rids = new uint32_t[network::recents::vars::m_vars.m_permanent_players.size()];

				for (std::size_t i = 0; i < network::recents::vars::m_vars.m_permanent_players.size(); i++) {
					rids[i] = (uint32_t)network::recents::vars::m_vars.m_permanent_players[i].second.m_rockstar_id;
				}

				uint64_t* info = new uint64_t[2];
				*(uint64_t*)((uint64_t)info) = (uint64_t)network::recents::vars::m_vars.m_permanent_players.size();
				*(uint64_t*)((uint64_t)info + 8) = (uint64_t)rids;

				util::threads::add_job([](void* lp) {
					uint64_t count = *(uint64_t*)((uint64_t)lp);
					uint32_t* ridss = (uint32_t*)*(uint64_t*)((uint64_t)lp + 8);

					rage::ros::send_stat_requests(ridss, (int)count);

					for (uint64_t i = 0; i < count; i++) {
						if (global::vars::g_unloading) return;

						if (menu::submenu::handler::get_current() != network_recent_players_permanent_menu::get()) {
							if (std::find_if(begin(m_vars.m_image_queue), end(m_vars.m_image_queue), [=](uint64_t rid) { return (uint32_t)rid == ridss[i]; }) == end(m_vars.m_image_queue)) m_vars.m_image_queue.push_back(ridss[i]);
							return;
						}

						rage::ros::download_player_image(ridss[i]);
					}

					delete[] ridss;
					delete[] lp;
				}, info);
			}

			std::sort(begin(network::recents::vars::m_vars.m_permanent_players), end(network::recents::vars::m_vars.m_permanent_players), [](std::pair<std::string, network::recents::vars::recent_player>& first, std::pair<std::string, network::recents::vars::recent_player>& second) { return first.second.m_internal_encountered > second.second.m_internal_encountered; });
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}
}

void network_recent_players_permanent_menu::load() {
	set_name("Permanent");
	set_parent<network_recent_players_menu>();

	add_string("~m~None");
}

void network_recent_players_permanent_menu::update() {
	static int timers[2] = { 0, 0 };
	static bool update_players = true;
	static bool update_online = true;

	menu::timers::run_timed(&timers[0], 1000, [] { update_players = true; });
	menu::timers::run_timed(&timers[1], 4000, [] { update_online = true; });

	if (update_players) {
		update_players = false;

		clear_options(0);

		if (network::recents::vars::m_vars.m_permanent_players.size()) {
			for (std::size_t i = 0; i < network::recents::vars::m_vars.m_permanent_players.size(); i++) {
				std::pair<std::string, network::recents::vars::recent_player>& player = network::recents::vars::m_vars.m_permanent_players[i];

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
						network::recents::selected::vars::m_vars.m_type = 2;
						network::recents::selected::vars::m_vars.m_selected_player = i;
						network::recents::vars::m_vars.m_selected_list = &network::recents::vars::m_vars.m_permanent_players;
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

	if (update_online) {
		update_online = false;

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
			for (std::size_t i = 0; i < network::recents::vars::m_vars.m_permanent_players.size(); i++) {
				m_vars.m_queue.push_back(network::recents::vars::m_vars.m_permanent_players[i].second.m_rockstar_id);
			}
		}
	}
}

void network_recent_players_permanent_menu::update_once() {
	load_players();

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

void network_recent_players_permanent_menu::feature_update() {}

network_recent_players_permanent_menu* g_instance;
network_recent_players_permanent_menu* network_recent_players_permanent_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_recent_players_permanent_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}