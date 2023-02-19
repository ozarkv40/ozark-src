#include "network_friends_selected.h"
#include "menu/base/submenu_handler.h"
#include "../network_friends.h"
#include "menu/base/submenus/main/network/search/network_player_search_selected.h"
#include "menu/base/submenus/main/network/session/network_session_overseer.h"
#include "rage/engine.h"

using namespace network::friends::selected::vars;

namespace network::friends::selected::vars {
	variables m_vars;

	void add_to_overseer() {
		network::session::overseer::vars::save(m_vars.m_selected->m_name, m_vars.m_selected->m_rockstar_id, "Friend");
	}
}

void network_friends_selected_menu::load() {
	set_name("Friend");
	set_parent<network_friends_menu>();

	add_option(button_option("Add to Overseer")
		.add_translate()
		.add_click(add_to_overseer));

	add_option(button_option("Show Profile")
		.add_translate()
		.add_click([] {
			rage::network::network_handle handle;
			native::network_handle_from_user_id(std::to_string(m_vars.m_selected->m_rockstar_id).c_str(), &handle.m_handle, sizeof(handle) / 4);
			native::network_show_profile_ui(&handle.m_handle);
		}));

	add_option(button_option("Invite to Session")
		.add_translate()
		.add_click([] { rage::engine::invite_player(m_vars.m_selected->m_rockstar_id); }));

	add_option(button_option("Join Player")
		.add_translate()
		.add_click([] { network::player::search::selected::vars::join_player(m_vars.m_selected->m_rockstar_id); }));
}

void network_friends_selected_menu::update() {}

void network_friends_selected_menu::update_once() {}

void network_friends_selected_menu::feature_update() {}

network_friends_selected_menu* g_instance;
network_friends_selected_menu* network_friends_selected_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_friends_selected_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}