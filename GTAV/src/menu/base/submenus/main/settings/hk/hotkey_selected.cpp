#include "hotkey_selected.h"
#include "menu/base/submenu_handler.h"
#include "../settings_hotkey.h"
#include "menu/base/util/menu_input.h"
#include "menu/base/util/hotkeys.h"

using namespace settings::hotkey::vars;

namespace settings::hotkey::vars {
	variables m_vars;

	scroll_struct<int> types[] = {
		{ localization("Release", true), 0 },
		{ localization("Press", true), 0 },
		{ localization("Hold", true), 0 }
	};
}

void hotkey_selected_menu::load() {
	set_name("Hotkey");
	set_parent<hotkey_menu>();

	add_string("Rebind");
	add_string("Delete");
}

void hotkey_selected_menu::update() {}

void hotkey_selected_menu::update_once() {
	clear_options(0);

	add_option(button_option(get_string("Rebind"))
		.add_click([=] {
			menu::input::push([] {
				menu::input::hotkey(((menu::hotkey::hotkey_context*)m_vars.m_hotkey)->m_parent->get_name().get(), ((menu::hotkey::hotkey_context*)m_vars.m_hotkey)->m_parent);
			});
		}));

	add_option(button_option(get_string("Delete"))
		.add_click([] {
			menu::hotkey::unregister_hotkey(((menu::hotkey::hotkey_context*)m_vars.m_hotkey)->m_parent);
			menu::submenu::handler::set_submenu_previous(true);
		}));

	add_option(scroll_option<int>(SCROLL, "Event")
		.add_scroll(m_vars.m_event, 0, NUMOF(types), types)
		.add_click([=] { menu::hotkey::change_type(m_vars.m_event, ((menu::hotkey::hotkey_context*)m_vars.m_hotkey)->m_parent); }));
}

void hotkey_selected_menu::feature_update() {}

hotkey_selected_menu* g_instance;
hotkey_selected_menu* hotkey_selected_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new hotkey_selected_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}