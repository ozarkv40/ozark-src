#include "network_spoofing_intervals.h"
#include "menu/base/submenu_handler.h"
#include "../network_spoofing.h"
#include "menu/base/util/timers.h"

using namespace network::spoofing::intervals::vars;

namespace network::spoofing::intervals::vars {
	variables m_vars;

	scroll_struct<int> intervals[] = {
		{ localization("Very Low", true), 0, },
		{ localization("Low", true), 1, },
		{ localization("Medium", true), 2, },
		{ localization("High", true), 3, },
		{ localization("Very High", true), 4, },
	};
}

void network_spoofing_intervals_menu::load() {
	set_name("Sync Intervals");
	set_parent<network_spoofing_menu>();
}

void network_spoofing_intervals_menu::update() {
	static int timer = 0;

	menu::timers::run_timed(&timer, 250, [this] {
		clear_options(0);

		menu::player::for_each([this](menu::player::player_context& player) {
			if (player.m_name.empty()) return;

			if (!player.m_sync_interval_toggle) {
				if (menu::player::get_local_player().m_ped_ptr && menu::player::get_local_player().m_ped_ptr->get_net_obj()) {
					player.m_sync_interval = menu::player::get_local_player().m_ped_ptr->get_net_obj()->m_player_sync_intervals[player.m_id];
				} else {
					player.m_sync_interval = 0;
				}
			}

			if (player.m_sync_interval > 4 || player.m_sync_interval < 0) player.m_sync_interval = 0;

			add_option(scroll_option<int>(TOGGLE, player.m_name)
				.add_toggle(player.m_sync_interval_toggle)
				.add_scroll(player.m_sync_interval, 0, NUMOF(intervals), intervals));
		}, false, true);
	});

	if (menu::base::get_current_option() >= get_options().size()) {
		menu::base::set_current_option((int)get_options().size() - 1);
	}
}

void network_spoofing_intervals_menu::update_once() {}

void network_spoofing_intervals_menu::feature_update() {
	menu::player::for_each([this](menu::player::player_context& player) {
		if (player.m_sync_interval_toggle) {
			if (menu::player::get_local_player().m_ped_ptr && menu::player::get_local_player().m_ped_ptr->get_net_obj()) {
				menu::player::get_local_player().m_ped_ptr->get_net_obj()->m_player_sync_intervals[player.m_id] = player.m_sync_interval;
			}
		}
	}, false, true);
}

network_spoofing_intervals_menu* g_instance;
network_spoofing_intervals_menu* network_spoofing_intervals_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_spoofing_intervals_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}