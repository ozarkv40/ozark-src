#include "network_recent_players_selected.h"
#include "menu/base/submenu_handler.h"
#include "../network_recent_players.h"
#include "network_recent_players_permanent.h"
#include "util/log.h"
#include "util/dirs.h"
#include "rage/engine.h"
#include "menu/base/util/panels.h"
#include "menu/base/submenus/main/network/search/network_player_search_selected.h"
#include "menu/base/submenus/main/network/session/network_session_overseer.h"
#include <fstream>

using namespace network::recents::selected::vars;

namespace network::recents::selected::vars {
	variables m_vars;

	void add_to_permanent() {
		try {
			nlohmann::json json;

			std::ifstream file(util::dirs::get_path(recent_players));
			if (file.good()) {
				json = nlohmann::json::parse(file);
				file.close();

				std::ofstream output(util::dirs::get_path(recent_players));
				if (output.good()) {
					network::recents::vars::recent_player p = network::recents::vars::m_vars.m_selected_list->at(m_vars.m_selected_player).second;
					json["perm"][std::to_string(p.m_rockstar_id)]["name"] = p.m_name;
					json["perm"][std::to_string(p.m_rockstar_id)]["ip"] = p.m_ip;
					json["perm"][std::to_string(p.m_rockstar_id)]["first encountered"] = p.m_first_encountered;
					json["perm"][std::to_string(p.m_rockstar_id)]["last encountered"] = p.m_last_encountered;
					json["perm"][std::to_string(p.m_rockstar_id)]["internal"] = p.m_internal_encountered;
					output << json.dump(4);
					output.close();
				}
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}

	void remove_from_permanent() {
		try {
			nlohmann::json json;

			std::ifstream file(util::dirs::get_path(recent_players));
			if (file.good()) {
				json = nlohmann::json::parse(file);
				file.close();

				std::ofstream output(util::dirs::get_path(recent_players));
				if (output.good()) {
					network::recents::vars::recent_player p = network::recents::vars::m_vars.m_selected_list->at(m_vars.m_selected_player).second;
					json["perm"][std::to_string(p.m_rockstar_id)].clear();
					output << json.dump(4);
					output.close();
				}
			}
		} catch (std::exception& e) {
			LOG_WARN("[Json] %s", e.what());
		}
	}

	void add_to_overseer() {
		network::recents::vars::recent_player p = network::recents::vars::m_vars.m_selected_list->at(m_vars.m_selected_player).second;
		network::session::overseer::vars::save(p.m_name, p.m_rockstar_id, "Recent Player");
	}
}

void network_recent_players_selected_menu::load() {
	set_name("Recent Player");
	set_parent<network_recent_players_menu>();

	add_option(button_option("Add to Permanent List")
		.add_translate()
		.add_click(add_to_permanent)
		.add_requirement([] { return m_vars.m_type == 1; }));

	add_option(button_option("Add to Overseer")
		.add_translate()
		.add_click(add_to_overseer));

	add_option(button_option("Show Profile")
		.add_translate()
		.add_click([] {
			rage::network::network_handle handle;
			native::network_handle_from_user_id(std::to_string(network::recents::vars::m_vars.m_selected_list->at(m_vars.m_selected_player).second.m_rockstar_id).c_str(), &handle.m_handle, sizeof(handle) / 4);
			native::network_show_profile_ui(&handle.m_handle);
		}));

	add_option(button_option("Send Friend Request")
		.add_translate()
		.add_click([] { rage::engine::send_friend_request(network::recents::vars::m_vars.m_selected_list->at(m_vars.m_selected_player).second.m_rockstar_id); }));

	add_option(button_option("Invite to Session")
		.add_translate()
		.add_click([] { rage::engine::invite_player(network::recents::vars::m_vars.m_selected_list->at(m_vars.m_selected_player).second.m_rockstar_id); }));

	add_option(button_option("Join Player")
		.add_translate()
		.add_click([] { network::player::search::selected::vars::join_player(network::recents::vars::m_vars.m_selected_list->at(m_vars.m_selected_player).second.m_rockstar_id); }));

	add_option(button_option("Remove from Permanent")
		.add_translate()
		.add_click(remove_from_permanent)
		.add_requirement([] { return m_vars.m_type != 1; }));
}

void network_recent_players_selected_menu::update() {}

void network_recent_players_selected_menu::update_once() {
	if (m_vars.m_type == 1) {
		set_parent<network_recent_players_menu>();
	} else {
		set_parent<network_recent_players_permanent_menu>();
	}

	auto& [strr, rec] = network::recents::vars::m_vars.m_selected_list->at(m_vars.m_selected_player);

	bool in_session = false;
	menu::player::for_each([&](menu::player::player_context& pl) {
		if (pl.m_net_player) {
			if (pl.m_net_player->m_player_info) {
				if (pl.m_net_player->m_player_info->m_identifier.m_rockstar_id == rec.m_rockstar_id) {
					in_session = true;
				}
			}
		}
	}, true);

	menu::panels::panel_custom_recent_player str;
	str.m_in_session = in_session;
	str.m_online = global::vars::g_online_rockstar_ids[rec.m_rockstar_id].first || in_session;
	str.m_rockstar_id = rec.m_rockstar_id;
	str.m_session_type = str.m_online ? global::vars::g_online_rockstar_ids[rec.m_rockstar_id].second : -1;
	strcpy(str.m_first_encountered, rec.m_first_encountered);
	strcpy(str.m_last_encountered, rec.m_last_encountered);
	strcpy(str.m_name, rec.m_name);
	strcpy(str.m_ip, rec.m_ip);

	if (global::vars::g_read_stats_by_gamer_results.contains(rec.m_rockstar_id)) {
		str.m_has_stats = true;
		memcpy(&str.m_stats, &global::vars::g_read_stats_by_gamer_results[rec.m_rockstar_id], sizeof(str.m_stats));
	} else {
		str.m_has_stats = false;
	}

	menu::panels::set_structure(menu::panels::get_child(menu::panels::get_parent("PANEL_RECENT_PLAYER"), "PANEL_RECENT_PLAYER_INFO"), (void*)&str, sizeof(str));
}

void network_recent_players_selected_menu::feature_update() {}

network_recent_players_selected_menu* g_instance;
network_recent_players_selected_menu* network_recent_players_selected_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_recent_players_selected_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}