#include "misc_radio.h"
#include "menu/base/submenu_handler.h"
#include "../misc.h"
#include "menu/base/util/panels.h"

using namespace misc::radio::vars;

namespace misc::radio::vars {
	variables m_vars;
}

void radio_menu::load() {
	set_name("Radio");
	set_parent<misc_menu>();

	add_option(toggle_option("Mobile Radio")
		.add_translate().add_hotkey()
		.add_toggle(m_vars.m_mobile_radio)
		.add_click([] {
			native::set_mobile_radio_enabled_during_gameplay(m_vars.m_mobile_radio);
			native::set_mobile_phone_radio_state(m_vars.m_mobile_radio);
		}).add_savable(get_submenu_name_stack()));

	add_option(button_option("Skip Radio Track")
		.add_translate().add_hotkey()
		.add_click([] { native::skip_radio_forward(); }));

	add_option(break_option("Radio Stations")
		.add_translate());

	add_string("Change to");
}

void radio_menu::update() {}

void radio_menu::update_once() {
	menu::panels::toggle_panel_render("PANEL_RADIO", true);

	clear_options(3);

	m_vars.m_context.reset();
	m_vars.m_context.m_selected = 0;

	std::vector<std::shared_ptr<radio_option>> temp_options;

	for (int i = 0; i < native::max_radio_station_index(); i++) {
		temp_options.push_back(add_option(radio_option(util::va::va("%s %s", get_string("Change to").c_str(), native::get_label_text(native::get_radio_station_name(i))))
			.add_radio(m_vars.m_context)
			.add_click([=] { native::set_radio_to_station_index(i); })));
	}

	int index = native::get_player_radio_station_index();
	if (index >= 0 && index < native::max_radio_station_index()) {
		temp_options[index]->update_selected();
	} else {
		m_vars.m_context.m_toggles[m_vars.m_context.m_selected] = false;
		m_vars.m_context.m_selected = 99;
		m_vars.m_context.m_toggles[99] = true;
	}
}

void radio_menu::feature_update() {}

radio_menu* g_instance;
radio_menu* radio_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new radio_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}
