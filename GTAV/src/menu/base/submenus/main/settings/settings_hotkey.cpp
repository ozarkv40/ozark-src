#include "settings_hotkey.h"
#include "menu/base/submenu_handler.h"
#include "../settings.h"
#include "menu/base/util/hotkeys.h"
#include "hk/hotkey_selected.h"

void hotkey_menu::load() {
	set_name("Hotkeys");
	set_parent<settings_menu>();

	hotkey_selected_menu::get();
	add_string("~m~None");
}

void hotkey_menu::update() {}

void hotkey_menu::update_once() {
	clear_options(0);

	if (menu::hotkey::get_hotkeys().size()) {
		for (menu::hotkey::hotkey_context& hotkey : menu::hotkey::get_hotkeys()) {
			add_option(submenu_option(util::va::va("[%s] %s", menu::input::g_key_names[hotkey.m_key], hotkey.m_parent->get_name().get().c_str()))
				.add_submenu<hotkey_selected_menu>()
				.add_click([=] {
					settings::hotkey::vars::m_vars.m_hotkey = (void*)&hotkey;
					settings::hotkey::vars::m_vars.m_event = hotkey.m_type;
				}));
		}
	} else {
		add_option(button_option(get_string("~m~None")).ref());
	}
}

void hotkey_menu::feature_update() {}

hotkey_menu* g_instance;
hotkey_menu* hotkey_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new hotkey_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}