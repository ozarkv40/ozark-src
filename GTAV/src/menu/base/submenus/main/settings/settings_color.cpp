#include "settings_color.h"
#include "menu/base/submenu_handler.h"
#include "../settings.h"
#include "../helper/helper_color.h"

namespace settings::color::vars {
	scroll_struct<color_rgba*> colors[] = {
		{ localization("Header", true), &global::ui::g_main_header },
		{ localization("Header Text", true), &global::ui::g_title },
		{ localization("Background", true), &global::ui::g_background },
		{ localization("Scroller", true), &global::ui::g_scroller },
		{ localization("Footer", true), &global::ui::g_footer },
		{ localization("Footer Text", true), &global::ui::g_sub_header_text },
		{ localization("Open Tooltip", true), &global::ui::g_open_tooltip },
		{ localization("Tooltip Background", true), &global::ui::g_tooltip },
		{ localization("Option", true), &global::ui::g_option },
		{ localization("Option Selected", true), &global::ui::g_option_selected },
		{ localization("Toggle On", true), &global::ui::g_toggle_on },
		{ localization("Toggle Off", true), &global::ui::g_toggle_off },
		{ localization("Breaker", true), &global::ui::g_break },
		{ localization("Notify Success", true), &global::ui::g_success },
		{ localization("Notify Error", true), &global::ui::g_error },
		{ localization("Notify Bar", true), &global::ui::g_notify_bar },
		{ localization("Notify Background", true), &global::ui::g_notify_background },
		{ localization("Submenu Arrow", true), &global::ui::g_submenu_bar },
		{ localization("Clear Area Range", true), &global::ui::g_clear_area_range },
		{ localization("Hotkey Bar", true), &global::ui::g_hotkey_bar },
		{ localization("Hotkey Background", true), &global::ui::g_hotkey_background },
		{ localization("Hotkey Input", true), &global::ui::g_hotkey_input },
		{ localization("Panel Bar", true), &global::ui::g_panel_bar },
		{ localization("Panel Background", true), &global::ui::g_panel_background },
		{ localization("Stacked Display Bar", true), &global::ui::g_stacked_display_bar },
		{ localization("Stacked Display Background", true), &global::ui::g_stacked_display_background },
		{ localization("Instructional Background", true), &global::ui::g_instructional_background },
		{ localization("Globe", true), &global::ui::g_globe },
		{ localization("Color Grid Bar", true), &global::ui::g_color_grid_bar },
		{ localization("Color Grid Background", true), &global::ui::g_color_grid_background },
	};
}

void color_menu::load() {
	set_name("Colors");
	set_parent<settings_menu>();
}

void color_menu::update() {}

void color_menu::update_once() {
	clear_options(0);

	for (int i = 0; i < NUMOF(settings::color::vars::colors); i++) {
		add_option(submenu_option(settings::color::vars::colors[i].m_name.get())
			.add_submenu<helper_color_menu>()
			.add_click([=] {
				helper_color_menu::get()->set_name(settings::color::vars::colors[i].m_name.get(), false, false);
				helper_color_menu::get()->set_parent<color_menu>();
				helper::color::vars::m_vars.m_color = settings::color::vars::colors[i].m_result;
				helper::color::vars::m_vars.m_callback = [] {};
			})
			.add_icon_override({ "randomha", "lol" }, { 0.2145f, 0.0055f }, { 0.011f, 0.02f }, settings::color::vars::colors[i].m_result));
	}
}

void color_menu::feature_update() {}

color_menu* g_instance;
color_menu* color_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new color_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}