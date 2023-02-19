#include "network_session_finder_edit.h"
#include "menu/base/submenu_handler.h"
#include "../network_session_finder.h"
#include "rage/engine.h"
#include "menu/base/submenus/main/network/search/network_player_search_selected.h"

using namespace network::sfinder::edit::vars;

namespace network::sfinder::edit::vars {
	variables m_vars;
}

void network_session_finder_edit_menu::load() {
	set_name("Session Finder");
	set_parent<network_session_finder_menu>();

	add_option(button_option("Show Profile")
		.add_translate()
		.add_click([] {
			rage::network::network_handle handle;
			native::network_handle_from_user_id(std::to_string(network::sfinder::vars::m_vars.m_sessions[m_vars.m_selected].m_rockstar_id).c_str(), &handle.m_handle, sizeof(handle) / 4);
			native::network_show_profile_ui(&handle.m_handle);
		}));

	add_option(button_option("Send Friend Request")
		.add_translate()
		.add_click([] { rage::engine::send_friend_request(network::sfinder::vars::m_vars.m_sessions[m_vars.m_selected].m_rockstar_id); }));

	add_option(button_option("Invite to Session")
		.add_translate()
		.add_click([] { rage::engine::invite_player(network::sfinder::vars::m_vars.m_sessions[m_vars.m_selected].m_rockstar_id); }));

	add_option(button_option("Join Player")
		.add_translate()
		.add_click([] { network::player::search::selected::vars::join_player(network::sfinder::vars::m_vars.m_sessions[m_vars.m_selected].m_rockstar_id); }));
}

void network_session_finder_edit_menu::update() {}

void network_session_finder_edit_menu::update_once() {}

void network_session_finder_edit_menu::feature_update() {}

network_session_finder_edit_menu* g_instance;
network_session_finder_edit_menu* network_session_finder_edit_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_session_finder_edit_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}