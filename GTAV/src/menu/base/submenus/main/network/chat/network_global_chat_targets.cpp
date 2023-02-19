#include "network_global_chat_targets.h"
#include "menu/base/submenu_handler.h"
#include "../network_global_chat.h"
#include "menu/base/util/timers.h"

using namespace network::gchat::targets::vars;

namespace network::gchat::targets::vars {
	variables m_vars;
}

void network_global_chat_targets_menu::load() {
	set_name("Modify Targets");
	set_parent<network_global_chat_menu>();

	add_option(toggle_option("Toggle Targeted Messages")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_enabled));

	add_option(break_option("Players")
		.add_translate());
}

void network_global_chat_targets_menu::update() {
	static int timer = 0;
	
	menu::timers::run_timed(&timer, 250, [this] {
		clear_options(2);

		menu::player::for_each([this](menu::player::player_context& player) {
			add_option(toggle_option(player.m_name)
				.add_toggle(player.m_chat_target));
		}, false, true);
	});
}

void network_global_chat_targets_menu::update_once() {}

void network_global_chat_targets_menu::feature_update() {}

network_global_chat_targets_menu* g_instance;
network_global_chat_targets_menu* network_global_chat_targets_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_global_chat_targets_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}