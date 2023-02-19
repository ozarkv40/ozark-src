#include "settings_fonts.h"
#include "menu/base/submenu_handler.h"
#include "../settings.h"
#include "menu/base/util/fonts.h"
#include "menu/base/util/notify.h"

using namespace settings::font::vars;

namespace settings::font::vars {
	variables m_vars;

	scroll_struct<int> fonts[] = {
		{ localization("Chalet London", true), 0, },
		{ localization("House", true), 1, },
		{ localization("Mono Space", true), 2, },
		{ localization("Chalet Comprime", true), 4, },
		{ localization("Pricedown", true), 7 }
	};
}

void fonts_menu::load() {
	set_name("Fonts");
	set_parent<settings_menu>();

	menu::fonts::update();

	add_option(scroll_option<int>(SCROLL, "Header")
		.add_translate()
		.add_scroll(m_vars.m_header.m_var, 0, (int)menu::fonts::get_list().size() + 5, fonts)
		.add_update([](scroll_option<int>* option, int position) {
			option->add_scroll(m_vars.m_header.m_var, 0, (int)menu::fonts::get_list().size() + 5, fonts);
		})
		.add_click([] {
			if (m_vars.m_header.m_var > 4) {
				m_vars.m_header.m_selected = fonts[m_vars.m_header.m_var].m_name.get_original();
			} else {
				m_vars.m_header.m_selected.clear();
			}

			global::ui::g_header_font = fonts[m_vars.m_header.m_var].m_result;
		}));

	add_option(scroll_option<int>(SCROLL, "Footer")
		.add_translate()
		.add_scroll(m_vars.m_sub_header.m_var, 0, (int)menu::fonts::get_list().size() + 5, fonts)
		.add_update([](scroll_option<int>* option, int position) {
			option->add_scroll(m_vars.m_sub_header.m_var, 0, (int)menu::fonts::get_list().size() + 5, fonts);
		})
		.add_click([] {
			if (m_vars.m_sub_header.m_var > 4) {
				m_vars.m_sub_header.m_selected = fonts[m_vars.m_sub_header.m_var].m_name.get_original();
			} else {
				m_vars.m_sub_header.m_selected.clear();
			}

			global::ui::g_sub_header_font = fonts[m_vars.m_sub_header.m_var].m_result;
		}));

	add_option(scroll_option<int>(SCROLL, "Option")
		.add_translate()
		.add_scroll(m_vars.m_option.m_var, 0, (int)menu::fonts::get_list().size() + 5, fonts)
		.add_update([](scroll_option<int>* option, int position) {
			option->add_scroll(m_vars.m_option.m_var, 0, (int)menu::fonts::get_list().size() + 5, fonts);
		})
		.add_click([] {
			if (m_vars.m_option.m_var > 4) {
				m_vars.m_option.m_selected = fonts[m_vars.m_option.m_var].m_name.get_original();
			} else {
				m_vars.m_option.m_selected.clear();
			}

			global::ui::g_option_font = fonts[m_vars.m_option.m_var].m_result;
		}));

	add_option(scroll_option<int>(SCROLL, "Open Tooltip")
		.add_translate()
		.add_scroll(m_vars.m_open_tooltip.m_var, 0, (int)menu::fonts::get_list().size() + 5, fonts)
		.add_update([](scroll_option<int>* option, int position) {
			option->add_scroll(m_vars.m_open_tooltip.m_var, 0, (int)menu::fonts::get_list().size() + 5, fonts);
		})
		.add_click([] {
			if (m_vars.m_open_tooltip.m_var > 4) {
				m_vars.m_open_tooltip.m_selected = fonts[m_vars.m_open_tooltip.m_var].m_name.get_original();
			} else {
				m_vars.m_open_tooltip.m_selected.clear();
			}

			global::ui::g_open_tooltip_font = fonts[m_vars.m_open_tooltip.m_var].m_result;
		}));

	add_option(scroll_option<int>(SCROLL, "Tooltip")
		.add_translate()
		.add_scroll(m_vars.m_tooltip.m_var, 0, (int)menu::fonts::get_list().size() + 5, fonts)
		.add_update([](scroll_option<int>* option, int position) {
			option->add_scroll(m_vars.m_tooltip.m_var, 0, (int)menu::fonts::get_list().size() + 5, fonts);
		})
		.add_click([] {
			if (m_vars.m_tooltip.m_var > 4) {
				m_vars.m_tooltip.m_selected = fonts[m_vars.m_tooltip.m_var].m_name.get_original();
			} else {
				m_vars.m_tooltip.m_selected.clear();
			}

			global::ui::g_tooltip_font = fonts[m_vars.m_tooltip.m_var].m_result;
		}));

	add_option(scroll_option<int>(SCROLL, "Stacked Display")
		.add_translate()
		.add_scroll(m_vars.m_stacked_display.m_var, 0, (int)menu::fonts::get_list().size() + 5, fonts)
		.add_update([](scroll_option<int>* option, int position) {
			option->add_scroll(m_vars.m_stacked_display.m_var, 0, (int)menu::fonts::get_list().size() + 5, fonts);
		})
		.add_click([] {
			if (m_vars.m_stacked_display.m_var > 4) {
				m_vars.m_stacked_display.m_selected = fonts[m_vars.m_stacked_display.m_var].m_name.get_original();
			} else {
				m_vars.m_stacked_display.m_selected.clear();
			}

			global::ui::g_stacked_display_font = fonts[m_vars.m_stacked_display.m_var].m_result;
		}));

	add_option(scroll_option<int>(SCROLL, "Notify Title")
		.add_translate()
		.add_scroll(m_vars.m_notify_title.m_var, 0, (int)menu::fonts::get_list().size() + 5, fonts)
		.add_update([](scroll_option<int>* option, int position) {
			option->add_scroll(m_vars.m_notify_title.m_var, 0, (int)menu::fonts::get_list().size() + 5, fonts);
		})
		.add_click([] {
			if (m_vars.m_notify_title.m_var > 4) {
				m_vars.m_notify_title.m_selected = fonts[m_vars.m_notify_title.m_var].m_name.get_original();
			} else {
				m_vars.m_notify_title.m_selected.clear();
			}

			global::ui::g_notify_title_font = fonts[m_vars.m_notify_title.m_var].m_result;
		}));

	add_option(scroll_option<int>(SCROLL, "Notify Body")
		.add_translate()
		.add_scroll(m_vars.m_notify_body.m_var, 0, (int)menu::fonts::get_list().size() + 5, fonts)
		.add_update([](scroll_option<int>* option, int position) {
			option->add_scroll(m_vars.m_notify_body.m_var, 0, (int)menu::fonts::get_list().size() + 5, fonts);
		})
		.add_click([] {
			if (m_vars.m_notify_body.m_var > 4) {
				m_vars.m_notify_body.m_selected = fonts[m_vars.m_notify_body.m_var].m_name.get_original();
			} else {
				m_vars.m_notify_body.m_selected.clear();
			}

			global::ui::g_notify_body_font = fonts[m_vars.m_notify_body.m_var].m_result;
		}));

	add_option(scroll_option<int>(SCROLL, "Panel")
		.add_translate()
		.add_scroll(m_vars.m_panel.m_var, 0, (int)menu::fonts::get_list().size() + 5, fonts)
		.add_update([](scroll_option<int>* option, int position) {
			option->add_scroll(m_vars.m_panel.m_var, 0, (int)menu::fonts::get_list().size() + 5, fonts);
		})
		.add_click([] {
			if (m_vars.m_panel.m_var > 4) {
				m_vars.m_panel.m_selected = fonts[m_vars.m_panel.m_var].m_name.get_original();
			} else {
				m_vars.m_panel.m_selected.clear();
			}

			global::ui::g_panel_font = fonts[m_vars.m_panel.m_var].m_result;
		}));

	add_string("Fonts");
	add_string("Convert fonts with the Ozark Launcher, or download our favourite fonts in the Resources on the Launcher");

	for (std::size_t i = 5; i < 200; i++) {
		fonts[i].m_result = -1;
	}

	menu::fonts::update();

	for (std::size_t i = 0; i < menu::fonts::get_list().size(); i++) {
		if (i == 200) break;
		fonts[i + 5].m_name = menu::fonts::get_list()[i].m_font_name;
		fonts[i + 5].m_result = menu::fonts::get_list()[i].m_font_id;
	}

	for (int i = 0; i < NUMOF(fonts); i++) {
		scroll_struct<int> font = fonts[i];

		if (global::ui::g_header_font == font.m_result) m_vars.m_header.m_var = i;
		if (global::ui::g_sub_header_font == font.m_result) m_vars.m_sub_header.m_var = i;
		if (global::ui::g_option_font == font.m_result) m_vars.m_option.m_var = i;
		if (global::ui::g_open_tooltip_font == font.m_result) m_vars.m_open_tooltip.m_var = i;
		if (global::ui::g_stacked_display_font == font.m_result) m_vars.m_stacked_display.m_var = i;
		if (global::ui::g_notify_title_font == font.m_result) m_vars.m_notify_title.m_var = i;
		if (global::ui::g_notify_body_font == font.m_result) m_vars.m_notify_body.m_var = i;
		if (global::ui::g_panel_font == font.m_result) m_vars.m_panel.m_var = i;
		if (global::ui::g_tooltip_font == font.m_result) m_vars.m_tooltip.m_var = i;
	}
}

void fonts_menu::update() {}

void fonts_menu::update_once() {
	menu::fonts::update();
	// menu::notify::stacked(get_string("Fonts"), get_string("Convert fonts with the Ozark Launcher, or download our favourite fonts in the Resources on the Launcher"));

	for (std::size_t i = 5; i < 200; i++) {
		fonts[i].m_result = -1;
	}

	for (std::size_t i = 0; i < menu::fonts::get_list().size(); i++) {
		if (i == 200) break;
		fonts[i + 5].m_name = menu::fonts::get_list()[i].m_font_name;
		fonts[i + 5].m_result = menu::fonts::get_list()[i].m_font_id;
	}

	for (int i = 0; i < NUMOF(fonts); i++) {
		scroll_struct<int> font = fonts[i];

		if (global::ui::g_header_font == font.m_result) m_vars.m_header.m_var = i;
		if (global::ui::g_sub_header_font == font.m_result) m_vars.m_sub_header.m_var = i;
		if (global::ui::g_option_font == font.m_result) m_vars.m_option.m_var = i;
		if (global::ui::g_open_tooltip_font == font.m_result) m_vars.m_open_tooltip.m_var = i;
		if (global::ui::g_stacked_display_font == font.m_result) m_vars.m_stacked_display.m_var = i;
		if (global::ui::g_notify_title_font == font.m_result) m_vars.m_notify_title.m_var = i;
		if (global::ui::g_notify_body_font == font.m_result) m_vars.m_notify_body.m_var = i;
		if (global::ui::g_panel_font == font.m_result) m_vars.m_panel.m_var = i;
		if (global::ui::g_tooltip_font == font.m_result) m_vars.m_tooltip.m_var = i;
	}
}

void fonts_menu::feature_update() {}

fonts_menu* g_instance;
fonts_menu* fonts_menu::get() {
	if (g_instance == nullptr) {
		g_instance = new fonts_menu();
		g_instance->load();
		menu::submenu::handler::add_submenu(g_instance);
	}

	return g_instance;
}