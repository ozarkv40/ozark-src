#include "network_player_search_join.h"
#include "menu/base/submenu_handler.h"
#include "../network.h"
#include "rage/engine.h"
#include "search/network_player_search_selected.h"
#include "menu/base/util/timers.h"
#include "menu/base/util/panels.h"
#include "menu/base/util/textures.h"
#include "util/threads.h"
#include "rage/ros.h"

using namespace network::player::search::vars;

namespace network::player::search::vars {
	variables m_vars;

	void input_player_rid_callback(button_option* option, const char* result) {
		m_vars.m_current_offset = 0;
		m_vars.m_current_page = 0;
		m_vars.m_total_pages_requested = 0;
		m_vars.m_accounts.clear();
		m_vars.m_name.clear();
		network_player_search_menu::get()->clear_options(5);

		std::string string_name(result);
		if (std::find_if(string_name.begin(), string_name.end(), [](unsigned char c) { return !std::isdigit(c); }) == string_name.end()) {
			if (atoll(string_name.c_str()) > 0x1000) {
				m_vars.m_rockstar_id = atoll(string_name.c_str());

				rage::api::get_profiles_from_rid(atoll(string_name.c_str()), [](bool success, std::vector<rage::api::rockstar_account> accounts, void* data) {
					if (success && !accounts.empty()) {
						m_vars.m_accounts.clear();
						m_vars.m_accounts.push_back(accounts[0]);
						m_vars.m_total = 1;
						network_player_search_menu::get()->update_once();
					} else {
						menu::notify::stacked(network_player_search_menu::get()->get_name().get(), network_player_search_menu::get()->get_string("Failed resolving profile"), global::ui::g_error);
					}
				}, nullptr);
			}
		}
	}

	void input_player_name_callback(button_option* option, const char* result) {
		m_vars.m_name = result;
		m_vars.m_rockstar_id = 0;
		m_vars.m_current_offset = 0;
		m_vars.m_current_page = 0;
		m_vars.m_total_pages_requested = 0;
		m_vars.m_accounts.clear();
		network_player_search_menu::get()->clear_options(5);

		rage::api::get_profiles_from_name(result, [=](bool success, std::vector<rage::api::rockstar_account> accounts, rage::api::result_info* out_info) {
			if (success && !accounts.empty()) {
				for (rage::api::rockstar_account& account : accounts) {
					if (std::find_if(begin(m_vars.m_accounts), end(m_vars.m_accounts), [=](rage::api::rockstar_account& elem) { return elem.m_rockstar_id == account.m_rockstar_id; }) == end(m_vars.m_accounts)) {
						m_vars.m_accounts.push_back(account);
					}
				}

				m_vars.m_total_pages_requested = 1;
				m_vars.m_current_offset += (int)accounts.size() + 1;
				m_vars.m_total = out_info->m_total;
				network_player_search_menu::get()->update_once();
			} else {
				menu::notify::stacked(network_player_search_menu::get()->get_name().get(), network_player_search_menu::get()->get_string("Failed resolving profiles"), global::ui::g_error);
			}

			if (out_info) {
				delete out_info;
			}
		}, nullptr);
	}

	void add_player(network_player_search_menu* _this, rage::api::rockstar_account* account) {
		uint8_t custom[0x10];
		*(uint64_t*)&custom[0] = account->m_rockstar_id;
		*(uint64_t*)&custom[8] = (uint64_t)&account->m_name;

		_this->add_option(submenu_option(account->m_name)
			.add_custom_data(custom)
			.add_submenu<network_player_search_selected_menu>()
			.add_click([=] { network::player::search::selected::vars::m_vars.m_selected = account; })
			.add_update([](submenu_option* option, int pos) {
				uint8_t* data = option->get_custom_data();
				uint64_t rid = *(uint64_t*)&data[0];
				std::string* name = (std::string*)*(uint64_t*)&data[8];

				option->set_name(((global::vars::g_online_rockstar_ids[rid].first) ? "" : "~m~") + *name);
				option->set_tooltip(util::va::va("Page %i of %i", m_vars.m_current_page + 1, (m_vars.m_total / 10) + 1));

				menu::textures::texture_context context;
				if (menu::textures::get_texture(std::string("playerimg_" + std::to_string(rid)), &context)) {
					option->add_offset(0.016f);

					menu::renderer::draw_rect_unaligned({ global::ui::g_position.x + 0.004f + 0.007f, global::ui::g_position.y + (pos * global::ui::g_option_scale) + 0.005f + 0.011f }, { 0.0136f, 0.0216f }, { 200, 200, 200, 255 });
					menu::renderer::draw_sprite({ "ozarkplayerimg", context.m_name }, { global::ui::g_position.x + 0.004f + 0.007f, global::ui::g_position.y + (pos * global::ui::g_option_scale) + 0.005f + 0.011f }, { 0.0136f, 0.0216f }, 0.f, { 255, 255, 255, 255 });
				}
			})
			.add_hover([] (submenu_option* option) {
				uint8_t* data = option->get_custom_data();
				uint64_t rid = *(uint64_t*)&data[0];
				std::string* name = (std::string*)*(uint64_t*)&data[8];

				menu::panels::panel_custom_player_search search;
				search.m_rockstar_id = rid;
				search.m_online = global::vars::g_online_rockstar_ids[rid].first;
				strcpy_s(search.m_name, name->c_str());

				if (global::vars::g_read_stats_by_gamer_results.contains(rid)) {
					search.m_has_stats = true;
					memcpy(&search.m_stats, &global::vars::g_read_stats_by_gamer_results[rid], sizeof(search.m_stats));
				} else {
					search.m_has_stats = false;
				}

				menu::panels::panel_parent* parent = menu::panels::get_parent("PANEL_PLAYER_SEARCH");
				if (parent) {
					menu::panels::set_structure(menu::panels::get_child(parent, "PANEL_PLAYER_SEARCH_INFO"), (void*)&search, sizeof(search));
					parent->m_render = true;
				}
			}));


		m_vars.m_queue.push_back(account->m_rockstar_id);
	}

	void get_next_page() {
		if ((m_vars.m_current_page + 1) < m_vars.m_total_pages_requested) {
			m_vars.m_current_page++;
			network_player_search_menu::get()->update_once();
			return;
		}

		if (!m_vars.m_processing_next_page) {
			m_vars.m_processing_next_page = true;

			rage::api::get_profiles_from_name(m_vars.m_name, [=](bool success, std::vector<rage::api::rockstar_account> accounts, rage::api::result_info* out_info) {
				m_vars.m_processing_next_page = false;

				if (success && !accounts.empty()) {
					for (rage::api::rockstar_account& account : accounts) {
						if (std::find_if(begin(m_vars.m_accounts), end(m_vars.m_accounts), [=](rage::api::rockstar_account& elem) { return elem.m_rockstar_id == account.m_rockstar_id; }) == end(m_vars.m_accounts)) {
							m_vars.m_accounts.push_back(account);
						}
					}

					m_vars.m_total_pages_requested++;
					m_vars.m_current_offset += (int)accounts.size() + 1;
					m_vars.m_current_page++;
					network_player_search_menu::get()->update_once();
				} else {
					menu::notify::stacked(network_player_search_menu::get()->get_name().get(), network_player_search_menu::get()->get_string("Failed resolving profiles"), global::ui::g_error);
				}

				if (out_info) {
					delete out_info;
				}
			}, nullptr, m_vars.m_current_offset);
		}
	}
}

void network_player_search_menu::load() {
	set_name("Player Search");
	set_parent<network_menu>();

	add_option(button_option("Input Target Rockstar ID")
		.add_translate()
		.add_keyboard("Enter target players Rockstar ID", 30, input_player_rid_callback));

	add_option(button_option("Input Target Name")
		.add_translate()
		.add_keyboard("Enter target players name", 30, input_player_name_callback));

	add_option(button_option("Next Page")
		.add_translate()
		.add_click([this] { get_next_page(); })
		.add_update([](button_option* option) { option->set_tooltip(util::va::va("Page %i of %i", m_vars.m_current_page + 1, (m_vars.m_total / 10) + 1)); })
		.add_requirement([] { return (((m_vars.m_current_page + 1) * 10) < m_vars.m_total) && m_vars.m_rockstar_id == 0; }));

	add_option(button_option("Previous Page")
		.add_translate()
		.add_click([this] { m_vars.m_current_page--; update_once(); })
		.add_update([](button_option* option) { option->set_tooltip(util::va::va("Page %i of %i", m_vars.m_current_page + 1, (m_vars.m_total / 10) + 1)); })
		.add_requirement([] { return (m_vars.m_current_page > 0) && m_vars.m_rockstar_id == 0; }));

	add_option(break_option("Results")
		.add_translate());

	add_string("~m~None");
	add_string("Failed resolving profile");
	add_string("Failed resolving profiles");
}

void network_player_search_menu::update() {
	if (menu::base::get_current_option() <= 6) {
		menu::panels::toggle_panel_render("PANEL_PLAYER_SEARCH", false);
	}

	static int timers[2] = { 0, 0 };
	static bool update_online = true;

	menu::timers::run_timed(&timers[1], 4000, [] { update_online = true; });

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
		if (process_size) {
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
		}

		// recreate the queue
		if (m_vars.m_queue.size() == 0) {
			for (std::size_t i = 0; i < m_vars.m_accounts.size(); i++) {
				m_vars.m_queue.push_back(m_vars.m_accounts[i].m_rockstar_id);
			}
		}
	}
}

void add_request(std::vector<uint64_t> players) {
	if (players.empty()) return;

	uint32_t* rids = new uint32_t[players.size()];

	for (std::size_t i = 0; i < players.size(); i++) {
		rids[i] = (uint32_t)players[i];
	}

	uint64_t* info = new uint64_t[2];
	*(uint64_t*)((uint64_t)info) = (uint64_t)players.size();
	*(uint64_t*)((uint64_t)info + 8) = (uint64_t)rids;

	util::threads::add_job([](void* lp) {
		uint64_t count = *(uint64_t*)((uint64_t)lp);
		uint32_t* ridss = (uint32_t*)*(uint64_t*)((uint64_t)lp + 8);

		rage::ros::send_stat_requests(ridss, (int)count);

		for (uint64_t i = 0; i < count; i++) {
			if (global::vars::g_unloading) return;

			if (menu::submenu::handler::get_current() != network_player_search_menu::get()) {
				if (std::find_if(begin(m_vars.m_image_queue), end(m_vars.m_image_queue), [=](uint64_t rid) { return (uint32_t)rid == ridss[i]; }) == end(m_vars.m_image_queue)) m_vars.m_image_queue.push_back(ridss[i]);
				return;
			}

			rage::ros::download_player_image(ridss[i]);
		}

		delete[] ridss;
		delete[] lp;
	}, info);
}

void network_player_search_menu::update_once() {
	clear_options(5);

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

	std::vector<uint64_t> players;

	if (m_vars.m_current_page == 0) {
		if (m_vars.m_accounts.size() <= 10) {
			for (rage::api::rockstar_account& account : m_vars.m_accounts) {
				add_player(this, &account);
				players.push_back(account.m_rockstar_id);
			}

			add_request(players);

			if (m_vars.m_accounts.empty()) {
				add_option(button_option(get_string("~m~None")).ref());
			}
		} else {
			for (std::size_t i = 0; i < 10; i++) {
				add_player(this, &m_vars.m_accounts[i]);
				players.push_back(m_vars.m_accounts[i].m_rockstar_id);
			}

			add_request(players);
		}
	} else {
		std::size_t max_size = m_vars.m_accounts.size() > (m_vars.m_current_page * 10) + 10 ? 10 : m_vars.m_accounts.size() - (m_vars.m_current_page * 10);
		for (std::size_t i = 0; i < max_size; i++) {
			add_player(this, &m_vars.m_accounts[i + (m_vars.m_current_page * 10)]);
			players.push_back(m_vars.m_accounts[i + (m_vars.m_current_page * 10)].m_rockstar_id);
		}

		add_request(players);

		if (max_size == 0) {
			add_option(button_option(get_string("~m~None")).ref());
		}
	}
}

void network_player_search_menu::feature_update() {}

network_player_search_menu* g_instance;
network_player_search_menu* network_player_search_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_player_search_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}