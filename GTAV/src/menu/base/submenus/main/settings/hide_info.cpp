#include "hide_info.h"
#include "menu/base/submenu_handler.h"
#include "../settings.h"

using namespace settings::hide::vars;

namespace settings::hide::vars {
	variables m_vars;

	void hide_names() {
		menu::player::for_each([=] (menu::player::player_context& player) {
			if (player.m_id != menu::player::get_local_player().m_id) {
				if (player.m_net_player) {
					if (player.m_net_player->m_player_info) {
						m_vars.m_cached[player.m_net_player->m_player_info->m_identifier.m_rockstar_id] = player.m_net_player->m_player_info->m_name;
						strcpy(player.m_net_player->m_player_info->m_name, util::va::va("Player_%i", player.m_net_player->m_id));
					}
				}
			}
		}, true);
	}

	void restore_names() {
		menu::player::for_each([=] (menu::player::player_context& player) {
			if (player.m_id != menu::player::get_local_player().m_id) {
				if (player.m_net_player) {
					if (player.m_net_player->m_player_info) {
						strcpy(player.m_net_player->m_player_info->m_name, m_vars.m_cached[player.m_net_player->m_player_info->m_identifier.m_rockstar_id].c_str());
					}
				}
			}
		}, true);

		m_vars.m_cached.clear();
	}
}

void hide_info_menu::load() {
	set_name("Streamer Mode");
	set_parent<settings_menu>();

	add_option(toggle_option("Hide Player IPs")
		.add_translate()
		.add_toggle(m_vars.m_hide_ips));

	add_option(toggle_option("Hide Player Rockstar IDs")
		.add_translate()
		.add_toggle(m_vars.m_hide_rockstar_ids));

	add_option(toggle_option("Hide Player Names")
		.add_translate()
		.add_toggle(m_vars.m_hide_names)
		.add_click([] {
			if (m_vars.m_hide_names) {
				hide_names();
			} else {
				restore_names();
			}
		}));
}

void hide_info_menu::update() {}

void hide_info_menu::update_once() {}

void hide_info_menu::feature_update() {}

hide_info_menu* g_instance;
hide_info_menu* hide_info_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new hide_info_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}