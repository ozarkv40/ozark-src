#include "network.h"
#include "menu/base/submenu_handler.h"
#include "../main.h"
#include "util/fiber_pool.h"
#include "util/fiber.h"
#include "menu/base/util/global.h"
#include "rage/types/global_types.h"
#include "menu/base/util/panels.h"
#include "network/network_session_finder.h"
#include "network/network_host_toolkit.h"
#include "network/network_global_chat.h"
#include "network/network_recent_players.h"
#include "network/network_friends.h"
#include "network/network_player_search_join.h"
#include "network/network_spoofing.h"
#include "network/network_account.h"
#include "network/network_join_bypass.h"
#include "network/network_players.h"
#include "network/network_session.h"

using namespace network::vars;

namespace network::vars {
	variables m_vars;

	scroll_struct<int> transitions[] = {
		{ localization("Public", true), 0 },
		{ localization("Crew", true), 12 },
		{ localization("Friend", true), 9 },
		{ localization("Leave Online", true), -1 }
	};

	void find_new_session(int id) {
		util::fiber::pool::add([=] {
			if (id == -1) {
				menu::script_global(rage::global::transition_session_flag + 2).as<int>() = id;
			} else {
				menu::script_global(rage::global::transition_session).as<int>() = id;
			}

			menu::script_global(rage::global::transition_session_flag).as<int>() = 1;
			util::fiber::sleep(200);
			menu::script_global(rage::global::transition_session_flag).as<int>() = 0;
		});
	}
}

void network_menu::load() {
	set_name("Network");
	set_parent<main_menu>();

	add_option(submenu_option("Players")
		.add_translate()
		.add_submenu<network_players_menu>()
		.add_click([] { global::vars::g_network_menu_type = SELECTED_PLAYER; }));

	add_option(submenu_option("Session")
		.add_translate()
		.add_submenu<network_session_menu>()
		.add_click([] { global::vars::g_network_menu_type = ALL_PLAYERS; }));

	add_option(submenu_option("Spoofing")
		.add_translate()
		.add_submenu<network_spoofing_menu>());

	add_option(submenu_option("Account")
		.add_translate()
		.add_submenu<network_account_menu>());

	add_option(submenu_option("Friends")
		.add_translate()
		.add_submenu<network_friends_menu>());

	add_option(submenu_option("Player Search")
		.add_translate()
		.add_submenu<network_player_search_menu>());

	add_option(submenu_option("Recent Players")
		.add_translate()
		.add_submenu<network_recent_players_menu>());

	add_option(submenu_option("Global Chat")
		.add_translate()
		.add_submenu<network_global_chat_menu>());

	add_option(submenu_option(XOR("Host Toolkit"))
		.add_translate()
		.add_submenu<network_host_toolkit_menu>());

	add_option(submenu_option("Session Finder")
		.add_translate()
		.add_submenu<network_session_finder_menu>());

	/*add_option(submenu_option("Join Bypass")
		.add_translate()
		.add_submenu<network_join_bypass_menu>());*/

	add_option(toggle_option("Join Notifications")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_join_notifications).add_savable(get_submenu_name_stack())
		.add_tooltip("Show when players are leaving and joining"));

	add_option(scroll_option<int>(SCROLLSELECT, "Find New Session")
		.add_translate().add_hotkey()
		.add_scroll(m_vars.m_transition, 0, NUMOF(transitions), transitions)
		.add_click([] { find_new_session(transitions[m_vars.m_transition].m_result); }));
}

void network_menu::update() {}

void network_menu::update_once() {
	rage::api::get_social_club()->m_clear_queue = true;
	menu::panels::toggle_panel_render("PANEL_PLAYER_INFO", false);
	menu::panels::toggle_panel_render("PANEL_RECENT_PLAYER", false);
	menu::panels::toggle_panel_render("PANEL_FRIEND", false);
	menu::panels::toggle_panel_render("PANEL_OVERSEER", false);
	menu::panels::toggle_panel_render("PANEL_SESSION", false);
	menu::panels::toggle_panel_render("PANEL_SESSION_BROWSER", false);
	menu::panels::toggle_panel_render("PANEL_PLAYER_SEARCH", false);
}

void network_menu::feature_update() {}

network_menu* g_instance;
network_menu* network_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}