#include "network_session_finder.h"
#include "menu/base/submenu_handler.h"
#include "../network.h"
#include "menu/base/util/panels.h"
#include "menu/base/util/timers.h"
#include "finder/network_session_finder_edit.h"
#include "rage/api/api.h"
#include "rage/ros.h"
#include "menu/base/util/textures.h"
#include "util/threads.h"

using namespace network::sfinder::vars;

namespace network::sfinder::vars {
	variables m_vars;
}

void network_session_finder_menu::load() {
	set_name("Session Finder");
	set_parent<network_menu>();

	add_option(toggle_option("Toggle Population")
		.add_translate()
		.add_toggle(m_vars.m_populate)
		.add_tooltip("Does cause some stuttering so don't leave it enabled all the time"));

	add_option(number_option<int>(SCROLL, "Minimum Slots Available")
		.add_translate()
		.add_number(m_vars.m_minimum_slots, "%i", 1).add_min(1).add_max(32)
		.add_click([] { m_vars.m_sessions.clear(); }).add_savable(get_submenu_name_stack())
		.add_tooltip("NOTE: Changing this value will reset the cache!"));

	add_option(button_option("Clear Cache")
		.add_translate()
		.add_click([] { m_vars.m_sessions.clear(); }));

	add_option(break_option("Sessions")
		.add_translate());

	add_string("~m~None");
}

void network_session_finder_menu::update() {
	static int timer = 0;

	menu::timers::run_timed(&timer, 1000, [this] {
		clear_options(4);

		for (std::size_t i = 0; i < m_vars.m_sessions.size(); i++) {
			session_browser& session = m_vars.m_sessions[i];
			if (!session.m_requested && global::vars::g_player_image_queue.empty()) {
				session.m_requested = true;

				std::size_t* number = new std::size_t;
				*number = i;

				rage::api::get_profiles_from_rid(session.m_rockstar_id, [](bool successful, std::vector<rage::api::rockstar_account> accounts, void* data) {
					if (data) {
						std::size_t id = *(std::size_t*)data;
						if (successful && !accounts.empty()) {
							m_vars.m_sessions[id].m_name = accounts[0].m_name;
						}

						delete data;
					}
				}, number);
			}

			bool peer_modded = ((session.m_peer_token >> 32) & 0xFFFFFFFF) < 0x1000;
			bool modder = peer_modded || session.m_rockstar_id < 0x1000;

			std::string color_modifier = "";
			if (global::vars::g_read_stats_by_gamer_results.contains(session.m_rockstar_id)) {
				if (global::vars::g_read_stats_by_gamer_results[session.m_rockstar_id].m_wallet_balance > 1000000000
					|| global::vars::g_read_stats_by_gamer_results[session.m_rockstar_id].m_bank_balance > 1000000000
					|| global::vars::g_read_stats_by_gamer_results[session.m_rockstar_id].m_rank > 2500) {
					color_modifier = "~y~";
				}
			}

			char option[150];
			if (session.m_name.empty()) {
				sprintf_s(option, "%s%s%i%s", color_modifier.c_str(), modder ? "~r~" : "", (uint32_t)session.m_rockstar_id, modder ? " - Modder" : "");
			} else {
				sprintf_s(option, "%s%s%s%s", color_modifier.c_str(), modder ? "~r~" : "", session.m_name.c_str(), modder ? " - Modder" : "");
			}

			add_option(submenu_option(option)
				.add_submenu<network_session_finder_edit_menu>()
				.add_hover([=](submenu_option*) {
					menu::panels::panel_custom_session_browser browser;
					browser.m_local_ip = session.m_local_ip;
					browser.m_peer_token = session.m_peer_token;
					browser.m_rockstar_id = session.m_rockstar_id;
					browser.m_name[0] = 0;
					if (!session.m_name.empty()) strcpy_s(browser.m_name, session.m_name.c_str());

					if (global::vars::g_read_stats_by_gamer_results.contains(session.m_rockstar_id)) {
						browser.m_has_stats = true;
						memcpy(&browser.m_stats, &global::vars::g_read_stats_by_gamer_results[session.m_rockstar_id], sizeof(browser.m_stats));
					} else {
						browser.m_has_stats = false;
					}

					menu::panels::panel_parent* parent = menu::panels::get_parent("PANEL_SESSION_BROWSER");
					if (parent) {
						menu::panels::set_structure(menu::panels::get_child(parent, "PANEL_SESSION_BROWSER_INFO"), (void*)&browser, sizeof(browser));
						parent->m_render = true;
					}
				})
				.add_update([=](submenu_option* option, int pos) {
					menu::textures::texture_context context;
					if (menu::textures::get_texture(std::string("playerimg_" + std::to_string(session.m_rockstar_id)), &context)) {
						option->add_offset(0.016f);

						menu::renderer::draw_rect_unaligned({ global::ui::g_position.x + 0.004f + 0.007f, global::ui::g_position.y + (pos * global::ui::g_option_scale) + 0.005f + 0.011f }, { 0.0136f, 0.0216f }, { 200, 200, 200, 255 });
						menu::renderer::draw_sprite({ "ozarkplayerimg", context.m_name }, { global::ui::g_position.x + 0.004f + 0.007f, global::ui::g_position.y + (pos * global::ui::g_option_scale) + 0.005f + 0.011f }, { 0.0136f, 0.0216f }, 0.f, { 255, 255, 255, 255 });
					}
				})
				.add_click([=] { network::sfinder::edit::vars::m_vars.m_selected = i; }));
		}

		if (m_vars.m_sessions.size() == 0) {
			add_option(button_option(get_string("~m~None")).ref());
		}
	});

	if (menu::base::get_current_option() < 4) {
		menu::panels::toggle_panel_render("PANEL_SESSION_BROWSER", false);
	}
}

void network_session_finder_menu::update_once() {
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

void network_session_finder_menu::feature_update() {}

network_session_finder_menu* g_instance;
network_session_finder_menu* network_session_finder_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_session_finder_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}