#include "network_spoofing_name.h"
#include "menu/base/submenu_handler.h"
#include "../network_spoofing.h"
#include "rage/engine.h"
#include "util/util.h"

using namespace network::spoofing::name::vars;

namespace network::spoofing::name::vars {
	variables m_vars;

	scroll_struct<const char*> text_settings[] = {
		{ localization("Normal", true), "" },
		{ localization("Bold", true), "~h~" },
		{ localization("Italic", true), "~italic~" },
	};

	scroll_struct<const char*> text_colors[] = {
		{ localization("Default", true), "" },
		{ localization("~v~Black", true), "~v~" },
		{ localization("~b~Blue", true), "~b~" },
		{ localization("~y~Gold", true), "~y~" },
		{ localization("~g~Green", true), "~g~" },
		{ localization("~c~Grey", true), "~c~" },
		{ localization("~f~Light Blue", true), "~f~" },
		{ localization("~o~Orange", true), "~o~" },
		{ localization("~p~Purple", true), "~p~" },
		{ localization("~r~Red", true), "~r~" }
	};

	scroll_struct<const char*> text_icons[] = {
		{ localization("None", true), "" },
		{ localization("Wanted Star", true), "~ws~" },
		{ localization("Rockstar Verified", true), "~¦~" },
		{ localization("Rockstar", true), "~÷~" },
	};

	void spoof(bool reset, const char* name) {
		network_spoofing_name_menu* _this = network_spoofing_name_menu::get();

		if (reset) {
			m_vars.m_spoofed_name = std::string(m_vars.m_original_name);
		} else {
			if (!name) return;

			char tmp[0x14];
			snprintf(tmp, 0x14, "%s%s%s%s", text_settings[m_vars.m_style].m_result, text_colors[m_vars.m_color].m_result, text_icons[m_vars.m_icon].m_result, name);
			m_vars.m_spoofed_name = std::string(tmp);
		}

		if (menu::player::get_local_player().m_ped_ptr) {
			if (menu::player::get_local_player().m_ped_ptr->m_player_info) {
				strncpy(menu::player::get_local_player().m_ped_ptr->m_player_info->m_name, m_vars.m_spoofed_name.c_str(), 0x14);
			}
		}

		if (menu::player::get_local_player().m_net_player) {
			if (menu::player::get_local_player().m_net_player->m_player_info) {
				strncpy(menu::player::get_local_player().m_net_player->m_player_info->m_name, m_vars.m_spoofed_name.c_str(), 0x14);
			}
		}

		if (m_vars.m_save_to_config) {
			util::config::write_string(_this->get_submenu_name_stack(), "Name", m_vars.m_spoofed_name);
		}

		uint64_t chat_info = *(uint64_t*)global::vars::g_chat_info;
		if (chat_info) {
			strcpy((char*)(chat_info + 0x84), m_vars.m_spoofed_name.c_str());
		}

		if (!reset) {
			menu::notify::stacked(_this->get_name().get(), _this->get_string("Spoofing name to") + " " + m_vars.m_spoofed_name);
		}
	}
}

void network_spoofing_name_menu::load() {
	set_name("Name");
	set_parent<network_spoofing_menu>();

	// TODO: Presets, Save and Load

	const char* name = rage::engine::sc_get_string("gtag");
	if (name) {
		strncpy(m_vars.m_original_name, name, 20);
		m_vars.m_spoofed_name = m_vars.m_original_name;
		m_vars.m_temp_name = m_vars.m_original_name;
	}

	add_option(button_option("Input Name")
		.add_translate()
		.add_keyboard("Enter name to spoof to", 20, [](button_option* _this, const char* name) { m_vars.m_temp_name = std::string(name); }));

	add_option(button_option("Reset to Default")
		.add_translate().add_hotkey()
		.add_sprite({ "ozarktextures", "spinner.png" })
		.add_sprite_scale({ 0.01232f, 0.02184f })
		.add_sprite_rotation()
		.add_click([] { spoof(true); }));

	add_option(toggle_option("Save to Config")
		.add_translate()
		.add_toggle(m_vars.m_save_to_config).add_savable(get_submenu_name_stack())
		.add_tooltip("Saves to the config when applied"));

	add_option(break_option("Text Settings")
		.add_translate());

	add_option(scroll_option<const char*>(SCROLL, "Color")
		.add_translate()
		.add_scroll(m_vars.m_color, 0, NUMOF(text_colors), text_colors));

	add_option(scroll_option<const char*>(SCROLL, "Style")
		.add_translate()
		.add_scroll(m_vars.m_style, 0, NUMOF(text_settings), text_settings));

	add_option(scroll_option<const char*>(SCROLL, "Icon")
		.add_translate()
		.add_scroll(m_vars.m_icon, 0, NUMOF(text_icons), text_icons)
		.add_tooltip("Added to the start of the spoofed name"));

	m_vars.m_preview_button = add_option(button_option("")
		.add_click([] { spoof(false, m_vars.m_temp_name.c_str()); }));

	if (m_vars.m_save_to_config) {
		m_vars.m_spoofed_name = util::config::read_string(get_submenu_name_stack(), "Name", m_vars.m_spoofed_name);

		for (int i = 1; i < NUMOF(text_settings); i++) {
			if (strstr(m_vars.m_spoofed_name.c_str(), text_settings[i].m_result)) {
				m_vars.m_style = i;
				util::replace_string(m_vars.m_spoofed_name, text_settings[i].m_result, "");
				break;
			}
		}

		for (int i = 1; i < NUMOF(text_colors); i++) {
			if (strstr(m_vars.m_spoofed_name.c_str(), text_colors[i].m_result)) {
				m_vars.m_color = i;
				util::replace_string(m_vars.m_spoofed_name, text_colors[i].m_result, "");
				break;
			}
		}

		for (int i = 1; i < NUMOF(text_icons); i++) {
			if (strstr(m_vars.m_spoofed_name.c_str(), text_icons[i].m_result)) {
				m_vars.m_icon = i;
				util::replace_string(m_vars.m_spoofed_name, text_icons[i].m_result, "");
				break;
			}
		}

		m_vars.m_temp_name = m_vars.m_spoofed_name;
		spoof(false, m_vars.m_temp_name.c_str());
	}

	add_string("Spoofing name to");
}

void network_spoofing_name_menu::update() {
	snprintf(m_vars.m_preview_name, 50, "Apply: %s%s%s%s", text_settings[m_vars.m_style].m_result, text_colors[m_vars.m_color].m_result, text_icons[m_vars.m_icon].m_result, m_vars.m_temp_name.c_str());
	m_vars.m_preview_button->set_name(m_vars.m_preview_name);
}

void network_spoofing_name_menu::update_once() {}

void network_spoofing_name_menu::feature_update() {}

network_spoofing_name_menu* g_instance;
network_spoofing_name_menu* network_spoofing_name_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_spoofing_name_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}