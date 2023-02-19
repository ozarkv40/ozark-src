#include "break.h"
#include "menu/base/renderer.h"
#include "menu/base/submenu_handler.h"
#include "menu/base/util/input.h"

void break_option::render(int position) {
	m_on_update(this);

	menu::renderer::draw_text("~italic~" + m_name.get(), { global::ui::g_position.x + 0.004f + ((global::ui::g_scale.x - (0.004f * 2.f)) / 2.f), global::ui::g_position.y + (position * global::ui::g_option_scale) + 0.004f }, menu::renderer::get_normalized_font_scale(global::ui::g_option_font, global::ui::g_option_height), global::ui::g_option_font, global::ui::g_break, JUSTIFY_CENTER);
}

void break_option::render_selected(int position, std::stack<std::string> submenu_name_stack) {
	switch (menu::base::get_break_scroll()) {
		case 1: // up
			if (menu::base::get_scroll_offset() > 0 && menu::base::get_current_option() - menu::base::get_scroll_offset() == 0) {
				menu::base::set_scroll_offset(menu::base::get_scroll_offset() - 1);
			}

			if (menu::base::get_current_option() - 1 < 0) {
				menu::input::scroll_bottom();
			} else {
				menu::base::set_current_option(menu::base::get_current_option() - 1);
			}

			break;

		case 2: // down
			if (menu::base::get_scroll_offset() < menu::submenu::handler::get_total_options() - menu::base::get_max_options() && menu::base::get_current_option() + 1 - menu::base::get_scroll_offset() == menu::base::get_max_options()) {
				menu::base::set_scroll_offset(menu::base::get_scroll_offset() + 1);
			}

			if (menu::base::get_current_option() + 1 >= menu::submenu::handler::get_total_options()) {
				menu::input::scroll_top();
			} else {
				menu::base::set_current_option(menu::base::get_current_option() + 1);
			}

			break;

		case 3: // bottom
			if (menu::base::get_scroll_offset() > 0 && menu::base::get_current_option() - menu::base::get_scroll_offset() == 1) {
				menu::base::set_scroll_offset(menu::base::get_scroll_offset() - 1);
			}

			menu::base::set_current_option(menu::base::get_current_option() - 1);
			break;

		case 4: // top
			if (menu::base::get_scroll_offset() < menu::submenu::handler::get_total_options() - menu::base::get_max_options() && menu::submenu::handler::get_total_options() >= menu::base::get_max_options() && menu::base::get_current_option() - menu::base::get_scroll_offset() == menu::base::get_max_options()) {
				menu::base::set_scroll_offset(menu::base::get_scroll_offset() + 1);
			}

			menu::base::set_current_option(menu::base::get_current_option() + 1);
			break;

	}
}