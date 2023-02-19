#include "network_global_chat_presets.h"
#include "menu/base/submenu_handler.h"
#include "../network_global_chat.h"

using namespace network::gchat::presets::vars;

namespace network::gchat::presets::vars {
	variables m_vars;

	std::string presets[] = {
		"buy Ozark at ozark.gg", "money drop at the airport", "i love penis",
		"i'm actually retarded", "i don't get any action in bed", "fuck everyone here",
		"everyone here sucks", "crash me if you can losers", "spare some coochie?",
		"i need love and attention", "i have no fwends :(", "someone PLEASE send me feet pics"
	};
}

void network_global_chat_presets_menu::load() {
	set_name("Presets");
	set_parent<network_global_chat_menu>();

	for (std::string& str : presets) {
		add_string(str);
	}

	add_option(toggle_option("Send Translated Preset")
		.add_translate()
		.add_hotkey()
		.add_toggle(m_vars.m_send_tanslated)
		.add_tooltip("Send the translated version of the presets"));

	add_option(toggle_option("Show Locally")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_show_locally)
		.add_tooltip("Show the message you send for you too"));

	add_option(number_option<int>(SCROLL, "Amount to Send")
		.add_translate()
		.add_number(m_vars.m_count, "%i", 1).add_min(1).add_max(100));

	add_option(break_option("Presets")
		.add_translate());
}

void network_global_chat_presets_menu::update() {}

void network_global_chat_presets_menu::update_once() {
	clear_options(4);

	for (std::string str : presets) {
		add_option(button_option(get_string(str))
			.add_hotkey()
			.add_click([=] { network::gchat::vars::send_message(m_vars.m_send_tanslated ? get_string(str) : str, m_vars.m_count, m_vars.m_show_locally); }));
	}
}

void network_global_chat_presets_menu::feature_update() {}

network_global_chat_presets_menu* g_instance;
network_global_chat_presets_menu* network_global_chat_presets_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_global_chat_presets_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}