#include "color_option.h"
#include "menu/base/renderer.h"
#include "menu/base/util/instructionals.h"
#include "menu/base/util/input.h"
#include "menu/base/util/menu_input.h"

void color_option::render(int position) {
	bool selected = menu::base::is_option_selected(position);
	color_rgba color = selected ? global::ui::g_option_selected : global::ui::g_option;

	m_on_update(this);
	m_on_update_this(this, position);

	menu::renderer::draw_text(m_name.get(), { global::ui::g_position.x + 0.004f, global::ui::g_position.y + (position * global::ui::g_option_scale) + 0.004f }, menu::renderer::get_normalized_font_scale(global::ui::g_option_font, global::ui::g_option_height), global::ui::g_option_font, color);
	menu::renderer::draw_rect({ global::ui::g_position.x + 0.2145f - (0.23f - global::ui::g_scale.x), global::ui::g_position.y + (position * global::ui::g_option_scale) + 0.0055f }, { 0.01f, 0.02f }, *m_color);
}

void color_option::render_selected(int position, std::stack<std::string> submenu_name_stack) {
	m_on_hover();

	if (m_instructionals.size()) {
		instructionals::setup();

		for (std::tuple<std::string, int, bool>& instructional : m_instructionals) {
			if (std::get<2>(instructional)) {
				instructionals::add_instructional(std::get<0>(instructional), (eControls)std::get<1>(instructional));
			} else {
				instructionals::add_instructional(std::get<0>(instructional), (eScaleformButtons)std::get<1>(instructional));
			}
		}

		instructionals::close();
	}

	if (m_requirement() && menu::input::is_option_pressed()) {
		m_on_click();
		m_on_click_this(this);

		menu::input::push([this] {
			menu::input::color(m_color);
		});
	}

	if (m_savable) {
		if (m_color) {
			if (m_color->r != m_color_cache.r || m_color->g != m_color_cache.g || m_color->b != m_color_cache.b || m_color->a != m_color_cache.a) {
				m_color_cache = *m_color;
				util::config::write_color(submenu_name_stack, m_name.get_original(), m_color_cache, { "Color" });
			}
		}
	}
}