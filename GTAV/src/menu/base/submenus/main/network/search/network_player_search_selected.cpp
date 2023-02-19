#include "network_player_search_selected.h"
#include "menu/base/submenu_handler.h"
#include "../network_player_search_join.h"
#include "rage/engine.h"
#include "util/memory/memory.h"
#include "util/caller.h"
#include "util/util.h"
#include "util/log.h"
#include "menu/base/submenus/main/network/spoofing/network_spoofing_rid.h"

using namespace network::player::search::selected::vars;

namespace network::player::search::selected::vars {
	variables m_vars;

	void join_player(uint64_t rockstar_id) {
		rage::network::rockstar_identifier* identifier = new rage::network::rockstar_identifier();
		identifier->m_rockstar_id = rockstar_id;
		identifier->m_type = 3;

		global::vars::g_gs_info_requests.push_back({ false, 2, rockstar_id, GetTickCount() + 10000, [=](std::string gs, uint64_t rid) {
			rage::network::gs_session session;
			if (rage::engine::get_session_info_from_gs(&session, gs.c_str())) {
				rage::network::game_invite* invite = new rage::network::game_invite();
				invite->h = network::spoofing::rid::vars::m_vars.m_spoofing_rid;
				invite->h2 = 3;
				invite->if_ = -1;
				invite->it = -1;
				invite->f = 0xA000;
				invite->gm = 0;
				invite->cc = network::spoofing::rid::vars::m_vars.m_spoofing_rid;
				invite->cc2 = 3;
				invite->l = 0; // 0
				invite->p = 0;
				invite->cr = 0;
				invite->u = 0;
				invite->d = 889455970;
				invite->jq = 0;
				strcpy(invite->s, gs.c_str());
				strcpy(invite->c, "");
				strcpy(invite->mid, "");
				strcpy(invite->n, util::create_random_string(10).c_str());

				memcpy(&invite->gssession_start, &session, sizeof(session));

				memory::write_vector(global::vars::g_hack_patches["JOINP"].m_address, global::vars::g_hack_patches["JOINP"].m_patch);

				char* x2 = new char[500];
				memset(x2, 0, 500);

				if (global::vars::g_network_base_config) {
					rage::network::network_base_config* real_config = global::vars::g_network_base_config;
					if (global::vars::g_steam) {
						real_config = (rage::network::network_base_config*)((uint64_t)global::vars::g_network_base_config + 0x70);
					}

					real_config->set_network_session_was_invited(false);
				}

				caller::call<void>(global::vars::g_create_game_invite_presence, x2, global::vars::g_send_game_invite_presence_table);
				caller::call<void>(global::vars::g_send_game_invite_presence, invite, x2);

				memory::write_vector(global::vars::g_hack_patches["JOINP"].m_address, global::vars::g_hack_patches["JOINP"].m_bytes);

				delete invite;
				delete[] x2;
			}
		} });

		native::clear_gamer_task_data();
		rage::engine::send_session_info_request(identifier, 1);
		delete identifier;
	}
}

void network_player_search_selected_menu::load() {
	set_parent<network_player_search_menu>();

	add_option(button_option("Show Profile")
		.add_translate()
		.add_click([] {
			rage::network::network_handle handle;
			native::network_handle_from_user_id(std::to_string(m_vars.m_selected->m_rockstar_id).c_str(), &handle.m_handle, sizeof(handle) / 4);
			native::network_show_profile_ui(&handle.m_handle);
		}));

	add_option(button_option("Send Friend Request")
		.add_translate()
		.add_click([] { rage::engine::send_friend_request(m_vars.m_selected->m_rockstar_id); }));

	add_option(button_option("Invite to Session")
		.add_translate()
		.add_click([] { rage::engine::invite_player(m_vars.m_selected->m_rockstar_id); }));

	add_option(button_option("Join Player")
		.add_translate()
		.add_click([] { join_player(m_vars.m_selected->m_rockstar_id); }));

	add_string("Failed to find a session for that player, they may be offline");
}

void network_player_search_selected_menu::update() {}

void network_player_search_selected_menu::update_once() {
	set_name(m_vars.m_selected->m_name, false, false);
}

void network_player_search_selected_menu::feature_update() {
	if (!global::vars::g_gs_info_requests.empty()) {
		for (std::size_t i = 0; i < global::vars::g_gs_info_requests.size(); i++) {
			if (global::vars::g_gs_info_requests[i].m_type == 2) {
				if (global::vars::g_gs_info_requests[i].m_finished) {
					global::vars::g_gs_info_requests.erase(global::vars::g_gs_info_requests.begin() + i);
					continue;
				}

				if (global::vars::g_gs_info_requests[i].m_expiry < GetTickCount()) {
					menu::notify::stacked(get_name().get(), get_string("Failed to find a session for that player, they may be offline"), global::ui::g_error);
					global::vars::g_gs_info_requests.erase(global::vars::g_gs_info_requests.begin() + i);
				}
			}
		}
	}
}

network_player_search_selected_menu* g_instance;
network_player_search_selected_menu* network_player_search_selected_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_player_search_selected_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}