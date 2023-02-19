#include "network_friends.h"
#include "menu/base/submenu_handler.h"
#include "../network.h"
#include "menu/base/util/panels.h"
#include "friends/network_friends_selected.h"
#include "rage/engine.h"
#include "rage/ros.h"
#include "menu/base/util/timers.h"
#include "util/threads.h"
#include "menu/base/util/textures.h"

using namespace network::friends::vars;

namespace network::friends::vars {
	variables m_vars;

	void invite_all() {
		for (int i = 0; i < native::network_get_friend_count(); i++) {
			rage::network::friends* _friend = (rage::network::friends*) & global::vars::g_friends[i];
			rage::engine::invite_player(_friend->m_rockstar_id);
		}
	}
}

void network_friends_menu::load() {
	set_name("Friends");
	set_parent<network_menu>();

	add_option(button_option("Invite All")
		.add_translate().add_hotkey()
		.add_click(invite_all));

	add_option(break_option("Friends")
		.add_translate());

	network_friends_selected_menu::get();

	add_string("~m~None");
}

void network_friends_menu::update() {
	static int timer = 0;
	static bool update_online = true;

	menu::timers::run_timed(&timer, 4000, [] { update_online = true; });

	if (update_online) {
		update_online = false;

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
			for (int i = 0; i < native::network_get_friend_count(); i++) {
				rage::network::friends* _friend = (rage::network::friends*) & global::vars::g_friends[i];
				m_vars.m_queue.push_back(_friend->m_rockstar_id);
			}
		}
	}

	if (menu::base::get_current_option() <= 1) {
		menu::panels::toggle_panel_render("PANEL_FRIEND", false);
	}
}

void network_friends_menu::update_once() {
	clear_options(2);

	if (native::network_get_friend_count() == 0) {
		add_option(button_option(get_string("~m~None")).ref());
	} else {
		for (int i = 0; i < native::network_get_friend_count(); i++) {
			rage::network::friends* _friend = (rage::network::friends*)&global::vars::g_friends[i];
			m_vars.m_queue.push_back(_friend->m_rockstar_id);
			m_vars.m_image_queue.push_back(_friend->m_rockstar_id);

			bool in_session = false;
			menu::player::for_each([&] (menu::player::player_context& pl) {
				if (pl.m_net_player) {
					if (pl.m_net_player->m_player_info) {
						if (pl.m_net_player->m_player_info->m_identifier.m_rockstar_id == _friend->m_rockstar_id) {
							in_session = true;
						}
					}
				}
			}, true);

			add_option(submenu_option(util::va::va("%s%s", (global::vars::g_online_rockstar_ids[_friend->m_rockstar_id].first || in_session) ? "" : "~m~", _friend->m_name))
				.add_submenu<network_friends_selected_menu>()
				.add_hover([=](submenu_option*) {
					menu::panels::panel_custom_friend tmp;
					tmp.m_rockstar_id = _friend->m_rockstar_id;
					tmp.m_in_session = in_session;
					tmp.m_online = global::vars::g_online_rockstar_ids[_friend->m_rockstar_id].first || in_session;
					tmp.m_session_type = tmp.m_online ? global::vars::g_online_rockstar_ids[_friend->m_rockstar_id].second : -1;
					strcpy(tmp.m_name, _friend->m_name);

					if (global::vars::g_read_stats_by_gamer_results.contains(_friend->m_rockstar_id)) {
						tmp.m_has_stats = true;
						memcpy(&tmp.m_stats, &global::vars::g_read_stats_by_gamer_results[_friend->m_rockstar_id], sizeof(tmp.m_stats));
					} else {
						tmp.m_has_stats = false;
					}

					menu::panels::set_structure(menu::panels::get_child(menu::panels::get_parent("PANEL_FRIEND"), "PANEL_FRIEND_INFO"), &tmp, sizeof(tmp));
					menu::panels::toggle_panel_render("PANEL_FRIEND", true);
				})
				.add_click([=] {
					network::friends::selected::vars::m_vars.m_selected = _friend;
				})
				.add_update([=] (submenu_option* option, int pos) {
					menu::textures::texture_context context;
					if (menu::textures::get_texture(std::string("playerimg_" + std::to_string(_friend->m_rockstar_id)), &context)) {
						option->add_offset(0.016f);

						menu::renderer::draw_rect_unaligned({ global::ui::g_position.x + 0.004f + 0.007f, global::ui::g_position.y + (pos * global::ui::g_option_scale) + 0.005f + 0.011f }, { 0.0136f, 0.0216f }, { 200, 200, 200, 255 });
						menu::renderer::draw_sprite({ "ozarkplayerimg", context.m_name }, { global::ui::g_position.x + 0.004f + 0.007f, global::ui::g_position.y + (pos * global::ui::g_option_scale) + 0.005f + 0.011f }, { 0.0136f, 0.0216f }, 0.f, { 255, 255, 255, 255 });
					}
				}));
		}
	}

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
			rage::ros::send_stat_requests(ridss, (int)count);

			for (uint64_t i = 0; i < count; i++) {
				if (global::vars::g_unloading) return;
				rage::ros::download_player_image(ridss[i]);
			}

			delete[] ridss;
			delete[] lp;
		}, info);
	}
}

void network_friends_menu::feature_update() {}

network_friends_menu* g_instance;
network_friends_menu* network_friends_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_friends_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}