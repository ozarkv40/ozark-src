#include "teleport_stores.h"
#include "menu/base/submenu_handler.h"
#include "../teleport.h"
#include "stores/teleport_stores_selected.h"

using namespace teleport::stores::vars;

namespace teleport::stores::vars {
	variables m_vars;

	scroll_struct<int> categories[] = {
		{ localization("Ammunation", true), 0 },
		{ localization("Barber Shop", true), 1 },
		{ localization("Binco", true), 2 },
		{ localization("Discount", true), 3 },
		{ localization("Los Santos Customs", true), 4 },
		{ localization("Ponsonbys", true), 5 },
		{ localization("Suburban", true), 6 },
		{ localization("Tattoo", true), 7 },
		{ localization("Other", true), 8 }
	};
}

void teleport_stores_menu::load() {
	set_name("Stores");
	set_parent<teleport_menu>();

	teleport_stores_selected_menu::get();
}

void teleport_stores_menu::update() {}

void teleport_stores_menu::update_once() {
	clear_options(0);

	for (scroll_struct<int>& category : categories) {
		add_option(submenu_option(category.m_name.get())
			.add_submenu<teleport_stores_selected_menu>()
			.add_click([=] {
				teleport::stores::selected::vars::m_vars.m_selected = category.m_result;
			}));
	}
}

void teleport_stores_menu::feature_update() {}

teleport_stores_menu* g_instance;
teleport_stores_menu* teleport_stores_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new teleport_stores_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}