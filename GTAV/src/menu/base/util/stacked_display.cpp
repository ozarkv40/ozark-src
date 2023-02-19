#include "stacked_display.h"
#include "menu/base/renderer.h"
#include "rage/invoker/natives.h"
#include <chrono>
#include <algorithm>

namespace menu::display {
	void stacked_display::render() {
		int draw_index = 0;
		int draw_count = 0;

		for (stacked_display_context item : m_messages) {
			std::string str_key = item.m_key;
			std::string str_value = item.m_value;

			if (item.m_rendering && !str_key.empty() && !str_value.empty()) {
				draw_count++;
			}
		}

		if (draw_count > 0) {
			float x = global::ui::g_stacked_display_position.x;
			float y = global::ui::g_stacked_display_position.y;
			float w = global::ui::g_stacked_display_scale.x;
			float h = global::ui::g_stacked_display_scale.y;
			float bezzel = 0.007875f / 2.f;

			// header
			std::pair<std::string, std::string> texture = menu::renderer::get_texture(global::ui::m_stacked_display_bar);
			menu::renderer::draw_sprite_aligned(texture, { x, y }, { w, bezzel }, 0.f, global::ui::g_stacked_display_bar);

			// bg
			texture = menu::renderer::get_texture(global::ui::m_stacked_display_background);
			menu::renderer::draw_sprite_aligned(texture, { x, y + bezzel }, { w, (h * draw_count) + 0.0065f }, 0.f, global::ui::g_stacked_display_background);

			std::sort(begin(m_messages), end(m_messages), [](stacked_display_context left, stacked_display_context right) { return left.m_add_time < right.m_add_time; });

			for (stacked_display_context item : m_messages) {
				std::string str_key = item.m_key;
				std::string str_value = item.m_value;

				if (item.m_rendering && !str_key.empty() && !str_value.empty()) {
					native::hide_hud_component_this_frame(1);
					native::hide_hud_component_this_frame(2);
					native::hide_hud_component_this_frame(3);
					native::hide_hud_component_this_frame(4);

					menu::renderer::draw_text(item.m_key, { x + 0.002f, y + (draw_index * h) + bezzel + 0.003f }, menu::renderer::get_normalized_font_scale(global::ui::g_stacked_display_font, 0.20f), global::ui::g_stacked_display_font, { 255, 255, 255, 255 });
					menu::renderer::draw_text(item.m_value, { 0.f, y + (draw_index * h) + bezzel + 0.003f }, menu::renderer::get_normalized_font_scale(global::ui::g_stacked_display_font, 0.20f), global::ui::g_stacked_display_font, { 255, 255, 255, 255 }, JUSTIFY_RIGHT, { 0.f, x + w - 0.002f });
					draw_index++;
				}
			}
		}
	}

	void stacked_display::update(std::string id, std::string key, std::string value) {
		auto& vit = std::find_if(begin(m_messages), end(m_messages), [=](stacked_display_context& element) { return element.m_id == id; });
		if (vit == end(m_messages)) {
			stacked_display_context add;
			add.m_rendering = true;
			add.m_add_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			add.m_id = id;
			add.m_key = key;
			add.m_value = value;

			m_messages.push_back(add);
			vit = std::find_if(begin(m_messages), end(m_messages), [=](stacked_display_context& element) { return element.m_id == id; });
		}
		
		if (vit != end(m_messages)) {
			vit->m_rendering = true;
			vit->m_key = key;
			vit->m_value = value;
		}
	}

	void stacked_display::disable(std::string id) {
		auto vit = std::find_if(begin(m_messages), end(m_messages), [=](stacked_display_context& element) { return element.m_id == id; });
		if (vit != end(m_messages)) {
			vit->m_rendering = false;
			vit->m_key = "";
			vit->m_value = "";
		}
	}

	stacked_display* get_stacked_display() {
		static stacked_display instance;
		return &instance;
	}
}