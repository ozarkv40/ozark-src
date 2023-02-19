#include "network_global_chat_ozark.h"
#include "menu/base/submenu_handler.h"
#include "../network_global_chat.h"

using namespace network::gchat::ozark::vars;

namespace network::gchat::ozark::vars {
	variables m_vars;

	scroll_struct<int> colors[] = {
		{ localization("White", true), HUD_COLOUR_WHITE },
		{ localization("Black", true), HUD_COLOUR_BLACK },
		{ localization("Grey", true), HUD_COLOUR_GREY },
		{ localization("Red", true), HUD_COLOUR_RED },
		{ localization("Blue", true), HUD_COLOUR_BLUE },
		{ localization("Yellow", true), HUD_COLOUR_YELLOW },
		{ localization("Orange", true), HUD_COLOUR_ORANGE },
		{ localization("Green", true), HUD_COLOUR_GREEN },
		{ localization("Purple", true), HUD_COLOUR_PURPLE },
		{ localization("Pink", true), HUD_COLOUR_PINK },
	};
}

void network_global_chat_ozark_menu::load() {
	set_name("Ozark Chat");
	set_parent<network_global_chat_menu>();

	add_option(toggle_option("Toggle Ozark Chat")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_enabled).add_savable(get_submenu_name_stack()));

	add_option(button_option("Input Prefix")
		.add_translate().add_hotkey()
		.add_keyboard("Input prefix", 30, [this](button_option* option, const char* result) {
			m_vars.m_prefix = result;
			util::config::write_string(get_submenu_name_stack(), "Prefix", m_vars.m_prefix);
		})
		.add_update([](button_option* option) { option->add_side_text(m_vars.m_prefix); })
		.add_tooltip("The prefix you have to type in chat before your message.\nExample: !oz hey"));
	
	add_option(scroll_option<int>(SCROLL, "Chat Color")
		.add_translate()
		.add_scroll(m_vars.m_color, 0, NUMOF(colors), colors).add_savable(get_submenu_name_stack()));

	m_vars.m_prefix = util::config::read_string(get_submenu_name_stack(), "Prefix", m_vars.m_prefix);
}

void network_global_chat_ozark_menu::update() {}

void network_global_chat_ozark_menu::update_once() {}

void network_global_chat_ozark_menu::feature_update() {}

network_global_chat_ozark_menu* g_instance;
network_global_chat_ozark_menu* network_global_chat_ozark_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_global_chat_ozark_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}