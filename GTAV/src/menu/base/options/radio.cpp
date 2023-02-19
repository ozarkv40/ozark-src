#include "radio.h"
#include "menu/base/util/input.h"
#include "menu/base/renderer.h"

void radio_option::render(int position) {
	bool selected = menu::base::is_option_selected(position);
	color_rgba color = selected ? global::ui::g_option_selected : global::ui::g_option;

	m_on_update(this);

	menu::renderer::draw_text(m_name.get(), { global::ui::g_position.x + 0.004f, global::ui::g_position.y + (position * global::ui::g_option_scale) + 0.004f }, menu::renderer::get_normalized_font_scale(global::ui::g_option_font, global::ui::g_option_height), global::ui::g_option_font, color);

	if (m_context->m_toggles[m_index]) {
		std::string sprite = m_context->m_sprite.second;
		if (strstr(sprite.c_str(), "shop_") && !strstr(sprite.c_str(), "shop_tick_icon")) {
			sprite += "_a";
			color = { 255, 255, 255, 255 };
		}

		menu::renderer::draw_sprite({ m_context->m_sprite.first, sprite }, { global::ui::g_position.x + 0.2195f - (0.23f - global::ui::g_scale.x), (global::ui::g_position.y + 0.016f) + (position * global::ui::g_option_scale) }, { 0.02112f * 0.8f, 0.03744f * 0.8f }, 0.f, color);
	}
}

void radio_option::render_selected(int position, std::stack<std::string> submenu_name_stack) {
	m_on_hover();

	if (m_requirement() && menu::input::is_option_pressed()) {
		if (!m_context->m_toggles[m_index]) {
			m_context->m_toggles[m_index] = true;
			m_context->m_toggles[m_context->m_selected] = false;
			m_context->m_selected = m_id;
		}

		m_on_click();
	}
}