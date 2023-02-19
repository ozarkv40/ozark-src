#include "network_account_outfits_edit_name.h"
#include "menu/base/submenu_handler.h"
#include "network_account_outfits_edit.h"
#include "../network_account_outfits.h"
#include "../../spoofing/network_spoofing_name.h"
#include "util/util.h"

using namespace network::account::outfits::edit::name::vars;

namespace network::account::outfits::edit::name::vars {
	variables m_vars;

	scroll_struct<const char*> text_settings[] = {
		{ localization("Normal", true), "" },
		{ localization("Bold", true), "~h~" },
		{ localization("Italic", true), "~italic~" },
	};

	scroll_struct<const char*> special_icons[] = {
		{ localization("Normal", true), "" },
		{ localization("Wanted Star", true), "~ws~" },
		{ localization("Rockstar Verified", true), "\xC2\xA6" },
		{ localization("Rockstar", true), "\xE2\x88\x91" },
	};

	void change_outfit_name() {
		char* name = network::account::outfits::vars::get_outfit_slot_name_ptr(network::account::outfits::edit::vars::m_vars.m_slot);
		snprintf(name, 64, "%s%s%s%s", text_settings[m_vars.m_style].m_result, special_icons[m_vars.m_icon].m_result, network::spoofing::name::vars::text_colors[m_vars.m_color].m_result, m_vars.m_temp_name.c_str());
	}
}

void network_account_outfits_edit_name_menu::load() {
	set_name("Name");
	set_parent<network_account_outfits_edit_menu>();

	add_option(button_option("Input Name")
		.add_translate()
		.add_keyboard("Enter name", 64, [](button_option* option, const char* name) { m_vars.m_temp_name = std::string(name); }));

	add_option(break_option("Text Settings")
		.add_translate());

	add_option(scroll_option<const char*>(SCROLL, "Special Icons")
		.add_translate()
		.add_scroll(m_vars.m_icon, 0, NUMOF(special_icons), special_icons));

	add_option(scroll_option<const char*>(SCROLL, "Style")
		.add_translate()
		.add_scroll(m_vars.m_style, 0, NUMOF(text_settings), text_settings));

	add_option(scroll_option<const char*>(SCROLL, "Color")
		.add_translate()
		.add_scroll(m_vars.m_color, 0, NUMOF(network::spoofing::name::vars::text_colors), network::spoofing::name::vars::text_colors));

	m_vars.m_preview_button = add_option(button_option("")
		.add_click(change_outfit_name));
}

void network_account_outfits_edit_name_menu::update() {
	snprintf(m_vars.m_preview_name, 50, "Apply: %s%s%s%s", text_settings[m_vars.m_style].m_result, special_icons[m_vars.m_icon].m_result, network::spoofing::name::vars::text_colors[m_vars.m_color].m_result, m_vars.m_temp_name.c_str());
	m_vars.m_preview_button->set_name(m_vars.m_preview_name);
}

void network_account_outfits_edit_name_menu::update_once() {
	char* local_name = network::account::outfits::vars::get_outfit_slot_name_ptr(network::account::outfits::edit::vars::m_vars.m_slot);
	if (!local_name || native::is_string_null_or_empty(local_name)) {
		return;
	}

	std::string name = std::string(local_name);

	for (int i = 1; i < NUMOF(text_settings); i++) {
		if (strstr(name.c_str(), text_settings[i].m_result)) {
			m_vars.m_style = i;
			util::replace_string(name, text_settings[i].m_result, "");
			break;
		}
	}

	for (int i = 1; i < NUMOF(special_icons); i++) {
		if (strstr(name.c_str(), special_icons[i].m_result)) {
			m_vars.m_icon = i;
			util::replace_string(name, special_icons[i].m_result, "");
			break;
		}
	}

	for (int i = 1; i < NUMOF(network::spoofing::name::vars::text_colors); i++) {
		if (strstr(name.c_str(), network::spoofing::name::vars::text_colors[i].m_result)) {
			m_vars.m_color = i;
			util::replace_string(name, network::spoofing::name::vars::text_colors[i].m_result, "");
		}
	}

	m_vars.m_temp_name = name;
}

void network_account_outfits_edit_name_menu::feature_update() {}

network_account_outfits_edit_name_menu* g_instance;
network_account_outfits_edit_name_menu* network_account_outfits_edit_name_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new network_account_outfits_edit_name_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}