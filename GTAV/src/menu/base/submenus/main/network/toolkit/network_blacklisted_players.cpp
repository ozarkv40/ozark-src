#include "network_blacklisted_players.h"
#include "menu/base/submenu_handler.h"
#include "../network_host_toolkit.h"
#include "menu/base/util/timers.h"
#include "menu/base/util/panels.h"
#include "rage/api/api.h"

using namespace network::htoolkit::blacklist::vars;

namespace network::htoolkit::blacklist::vars {
	variables m_vars;

	void remove_player(uint64_t rockstar_id) {
		rage::network::network_base_config* real_config = global::vars::g_network_base_config;

		if (global::vars::g_steam) {
			real_config = (rage::network::network_base_config*)((uint64_t)global::vars::g_network_base_config + 0x70);
		}

		if (is_valid_ptr(real_config)) {
			if (real_config->m_last_blacklisted.m_rockstar_id == rockstar_id) {
				real_config->m_last_blacklisted.m_rockstar_id = 0;
				real_config->m_last_blacklisted_timestamp = 0;
			}

			// If they're the only one in the list
			if (real_config->m_first_blacklisted_player) {
				if (real_config->m_first_blacklisted_player->m_player.m_rockstar_id == rockstar_id) {
					if (real_config->m_first_blacklisted_player->m_next == nullptr) {
						real_config->m_first_blacklisted_player = nullptr;
						real_config->m_last_blacklisted_player = nullptr;
					} else {
						// Replace it with the next
						real_config->m_first_blacklisted_player = real_config->m_first_blacklisted_player->m_next;
						real_config->m_first_blacklisted_player->m_last = nullptr;
					}

					return;
				}
			}

			// If they're not the first
			rage::network::blacklisted_player* current_player = real_config->m_first_blacklisted_player;
			rage::network::blacklisted_player* last_player = nullptr;

			while (current_player) {
				if (current_player->m_player.m_rockstar_id == rockstar_id) {
					if (!is_valid_ptr(current_player->m_next)) {
						last_player->m_next = nullptr;
						return;
					}

					last_player->m_next = current_player->m_next;
					current_player->m_last = last_player;
					return;
				}

				last_player = current_player;
				current_player = current_player->m_next;
			}
		}
	}
}

void network_blacklisted_players_menu::load() {
	set_name("Blacklisted players");
	set_parent<network_host_toolkit_menu>();

	add_option(button_option("Clear All")
		.add_translate().add_hotkey()
		.add_click([] {
			rage::network::network_base_config* real_config = global::vars::g_network_base_config;

			if (global::vars::g_steam) {
				real_config = (rage::network::network_base_config*)((uint64_t)global::vars::g_network_base_config + 0x70);
			}

			if (is_valid_ptr(real_config)) {
				real_config->m_last_blacklisted.m_rockstar_id = 0;
				real_config->m_last_blacklisted_timestamp = 0;
				real_config->m_first_blacklisted_player = nullptr;
				real_config->m_last_blacklisted_player = nullptr;
			}

			m_vars.m_players.clear();
		}));

	add_option(break_option("Players")
		.add_translate());

	add_string("~m~None");
	add_string("Click on this player to remove them from the blacklist");
}

void network_blacklisted_players_menu::update() {
	static int timer = 0;

	menu::timers::run_timed(&timer, 1000, [this] {
		clear_options(2);

		std::vector<rage::network::blacklisted_player> players;

		rage::network::network_base_config* real_config = global::vars::g_network_base_config;

		if (global::vars::g_steam) {
			real_config = (rage::network::network_base_config*)((uint64_t)global::vars::g_network_base_config + 0x70);
		}

		rage::network::blacklisted_player* blacklisted_players = real_config->m_first_blacklisted_player;
		if (is_valid_ptr(blacklisted_players)) {
			for (; blacklisted_players; blacklisted_players = blacklisted_players->m_next) {
				players.push_back(*blacklisted_players);
			}
		}

		for (rage::network::blacklisted_player& player : players) {
			auto vit = std::find_if(m_vars.m_players.begin(), m_vars.m_players.end(), [=](blacklisted_player& element) { return element.m_player.m_player.m_rockstar_id == player.m_player.m_rockstar_id; });
			if (vit == m_vars.m_players.end()) {
				m_vars.m_players.push_back({ player, false, "" });
			}
		}

		std::vector<uint64_t> _delete;

		for (blacklisted_player& player : m_vars.m_players) {
			auto vit = std::find_if(players.begin(), players.end(), [=](rage::network::blacklisted_player& element) { return element.m_player.m_rockstar_id == player.m_player.m_player.m_rockstar_id; });
			if (vit == players.end()) {
				_delete.push_back(player.m_player.m_player.m_rockstar_id); // Deleted
				continue;
			}

			if (!player.m_api) {
				player.m_api = true;

				if (player.m_player.m_player.m_rockstar_id > 0x1000) {
					rage::api::get_profiles_from_rid(player.m_player.m_player.m_rockstar_id, [](bool successful, std::vector<rage::api::rockstar_account> accounts, void* data) {
						if (successful && !accounts.empty()) {
							auto vit = std::find_if(m_vars.m_players.begin(), m_vars.m_players.end(), [=](blacklisted_player& element) { return element.m_player.m_player.m_rockstar_id == accounts[0].m_rockstar_id; });
							if (vit != m_vars.m_players.end()) {
								vit->m_resolved_name = accounts[0].m_name;
							}
						}
					}, nullptr);
				}
			}

			std::string name = std::to_string(player.m_player.m_player.m_rockstar_id);
			if (!player.m_resolved_name.empty()) name = player.m_resolved_name;

			add_option(button_option(name)
				.add_click([=] { remove_player(player.m_player.m_player.m_rockstar_id); })
				.add_hover([=] {
					menu::panels::panel_custom_blacklisted_player p;
					p.m_rockstar_id = player.m_player.m_player.m_rockstar_id;
					p.m_blacklisted_time = player.m_player.m_timestamp;
					if (!player.m_resolved_name.empty()) strcpy_s(p.m_name, player.m_resolved_name.c_str());
					else strcpy_s(p.m_name, "Querying...");

					menu::panels::panel_parent* parent = menu::panels::get_parent("PANEL_BLACKLISTED_PLAYERS");
					if (parent) {
						menu::panels::set_structure(menu::panels::get_child(parent, "PANEL_BLACKLISTED_PLAYERS_INFO"), (void*)&p, sizeof(p));
						parent->m_render = true;
					}
				})
				.add_tooltip(get_string("Click on this player to remove them from the blacklist")));
		}

		for (uint64_t D : _delete) {
			m_vars.m_players.erase(std::remove_if(m_vars.m_players.begin(), m_vars.m_players.end(), [=](blacklisted_player& element) { return element.m_player.m_player.m_rockstar_id == D; }), m_vars.m_players.end());
		}

		if (m_vars.m_players.size() == 0) {
			menu::panels::panel_parent* parent = menu::panels::get_parent("PANEL_BLACKLISTED_PLAYERS");
			if (parent) {
				menu::panels::null_structure(menu::panels::get_child(parent, "PANEL_BLACKLISTED_PLAYERS_INFO"));
			}

			add_option(button_option(get_string("~m~None")).ref());
		}
	});

	if (menu::base::get_current_option() == 0) menu::panels::toggle_panel_render("PANEL_BLACKLISTED_PLAYERS", false);
}

void network_blacklisted_players_menu::update_once() {}

void network_blacklisted_players_menu::feature_update() {}

network_blacklisted_players_menu* g_instance;
network_blacklisted_players_menu* network_blacklisted_players_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_blacklisted_players_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}